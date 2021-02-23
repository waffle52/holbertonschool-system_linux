#include "signals.h"

/**
 * term_handle - print msg
 * @signum: signal num
 * @info: info on signal
 * @pt: pointer to signal
 */
void term_handle(int signum, siginfo_t *info, void *pt)
{
	(void)pt;
	(void)signum;
	printf("SIGQUIT sent by %d\n", info->si_pid);
}

/**
 * trace_signal_sender - entry
 *
 * Return: handler for signal
 */
int trace_signal_sender(void)
{
	struct sigaction new, old;

	new.sa_sigaction = term_handle;
	sigemptyset(&new.sa_mask);
	new.sa_flags = 0;

	return (sigaction(SIGQUIT, &new, &old));
}
