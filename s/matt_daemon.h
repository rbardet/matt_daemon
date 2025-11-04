#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
// SHIT
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

#define LOCKLOC "/var/lock/matt_daemon.lock"

#ifndef LOGIN
# define LOGIN "cgodard"
#endif

#define PORT 4242
#define CONCURRENT_USERS 3

#define PROMPT "\x1b[1m> \x1b[0m"
#define HELP "?      show help\n"\
			 "shell  spawn a remote shell on 4242\n"
#define SHELL_MSG "spawning a shell...\n(press enter)\n"
#define UNKNOWN_CMD_MSG  "unknown command\n"
#define PASSWORD_PROMPT "password: "
#define INVALID_PASSWORD_MSG "wrong\n(press enter)\n"
#define TOO_MANY_USERS "too many users!\n"

#define BACKLOG 1024

#define LOG_FILE "/var/log/matt_daemon/matt_daemon.log"
#define LOG_DIR "/var/log/matt_daemon"

class Tintin_reporter
{
private:
	std::ofstream log;
public:
	Tintin_reporter();
	~Tintin_reporter();

	void print_log(const std::string level, const std::string message);
	void print_pid(const std::string level);
};

extern Tintin_reporter logger;
extern char **environ;

// lock.c
int		is_locked(void);
void	create_lock(void);
void	delete_lock_at_exit(void);

// socket.c
void	listen_server(void);
void	exit_client(int epfd, int fd);

// commands.c
void	handle_command(int epfd, int cfd);
void	quit();

// signals.c
void	setup_signals();