#include "matt_daemon.h"

void quit()
{	
	logger.print_log("[INFO]", "Quitting");
	logger.~Tintin_reporter();
	exit(1);
}

void	handle_command(int epfd __attribute__((unused)), int cfd)
{
	char	buf[4096];
	ssize_t	n;

	n = read(cfd, buf, sizeof buf);
	if (n <= 0)
		return ;
	buf[n] = 0;
	if (strcmp(buf, "quit\n") == 0) {
		logger.print_log("[INFO]", "Request quit.");
		quit();
	}
	else if (strcmp(buf, "\n"))
	{
		std::string msg = "User input: ";
		char *nl = strchr(buf, '\n');
		std::string end;
		if (nl)
			*nl = 0;
		else
			end = "\n";
		logger.print_log("[LOG]", msg + buf + end);
	}
}
