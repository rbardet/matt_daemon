#include "matt_daemon.h"

int	n_clients = 0;

void	epoll_ctl_add(int epfd, int fd, int events)
{
	struct epoll_event	ev;

	ev.events = events;
	ev.data.fd = fd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

int	create_server(void)
{
	int					sfd;
	int					opt;
	struct sockaddr_in	addr;

	logger.print_log("[INFO]", "Creating server.");
	sfd = socket(AF_INET, SOCK_STREAM|SOCK_NONBLOCK, 0);
	if (sfd < 0)
		return (-1);
	opt = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) < 0)
		return (-1);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	if (bind(sfd, (struct sockaddr *)&addr, sizeof addr) < 0)
		return (-1);
	if (listen(sfd, BACKLOG) < 0)
		return (-1);
	logger.print_log("[INFO]", "Server created.");
	return (sfd);
}

void	exit_client(int epfd, int cfd)
{
	epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
	close(cfd);
}

void	too_many_users(int cfd)
{
	write(cfd, TOO_MANY_USERS, sizeof TOO_MANY_USERS);
	close(cfd);
}

void enter_daemon_mode()
{
	daemon(0, 0);
	logger.print_log("[INFO]", "Entering Daemon mode.");
	logger.print_pid("[INFO]");
	setup_signals();
}

void	listen_server(void)
{
	int					epfd;
	int					sfd;
	int					n;
	struct epoll_event	events[BACKLOG];
	int					cfd;

	sfd = create_server();
	if (sfd < 0)
		return ;
	epfd = epoll_create(1);
	epoll_ctl_add(epfd, sfd, EPOLLIN|EPOLLOUT);
	enter_daemon_mode();
	while (1)
	{
		n = epoll_wait(epfd, events, BACKLOG, -1);
		if (n < 0)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		while (n--)
		{
			cfd = events[n].data.fd;
			if (cfd == sfd)
			{
				if (n_clients < CONCURRENT_USERS)
				{
					cfd = accept(sfd, NULL, 0);
					epoll_ctl_add(epfd, cfd, EPOLLIN|EPOLLRDHUP);
				}
				else
				{
					cfd = accept(sfd, NULL, 0);
					too_many_users(cfd);
				}
			}
			else if (events[n].events & EPOLLIN
					&& cfd < BACKLOG)
			{
				handle_command(epfd, cfd);
			}
			if (events[n].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR))
				exit_client(epfd, cfd);
		}
	}
}
