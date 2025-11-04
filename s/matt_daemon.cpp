#include "matt_daemon.h"

Tintin_reporter logger;

int	main(void)
{
	if (getuid())
	{
		dprintf(STDERR_FILENO, "not enough permissions...\n");
		return (EXIT_FAILURE);
	}
	logger.print_log("[INFO]", "Started.");
	if (is_locked())
	{
		logger.print_log("[ERROR]", "Error file locked.");
		return (EXIT_FAILURE);
	}
	
	create_lock();
	delete_lock_at_exit();
	listen_server();

	return (EXIT_SUCCESS);
}
