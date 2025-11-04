#include "matt_daemon.h"

void signal_handler(int n __attribute__((unused)))
{
	logger.print_log("[INFO]", "Signal handler.");
	quit();
}

void setup_signals()
{
	struct sigaction siga;

	siga.sa_handler = signal_handler;
	sigaction(SIGHUP, &siga, NULL);
	sigaction(SIGINT, &siga, NULL);
	sigaction(SIGQUIT, &siga, NULL);
	sigaction(SIGILL, &siga, NULL);
	sigaction(SIGTRAP, &siga, NULL);
	sigaction(SIGABRT, &siga, NULL);
	sigaction(SIGIOT, &siga, NULL);
	sigaction(SIGBUS, &siga, NULL);
	sigaction(SIGFPE, &siga, NULL);
	sigaction(SIGKILL, &siga, NULL);
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGSEGV, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	sigaction(SIGPIPE, &siga, NULL);
	sigaction(SIGALRM, &siga, NULL);
	sigaction(SIGTERM, &siga, NULL);
	sigaction(SIGSTKFLT, &siga, NULL);
	sigaction(SIGCHLD, &siga, NULL);
	sigaction(SIGCLD, &siga, NULL);
	sigaction(SIGCONT, &siga, NULL);
	sigaction(SIGSTOP, &siga, NULL);
	sigaction(SIGTSTP, &siga, NULL);
	sigaction(SIGTTIN, &siga, NULL);
	sigaction(SIGTTOU, &siga, NULL);
	sigaction(SIGURG, &siga, NULL);
	sigaction(SIGXCPU, &siga, NULL);
	sigaction(SIGXFSZ, &siga, NULL);
	sigaction(SIGVTALRM, &siga, NULL);
	sigaction(SIGPROF, &siga, NULL);
	sigaction(SIGWINCH, &siga, NULL);
	sigaction(SIGIO, &siga, NULL);
	sigaction(SIGPOLL, &siga, NULL);
	sigaction(SIGPWR, &siga, NULL);
	sigaction(SIGSYS, &siga, NULL);
}
