#include "signals.h"

/**
 * handle_sigaction - entry
 *
 * Return: 0 (SUCCESS) -1 FAIL
 */
int handle_sigaction(void)
{
	struct sigaction tmp;

	tmp.sa_handler = empty_handle;
	sigemptyset(&tmp.sa_mask);
	tmp.sa_flags = SA_RESTART;

	return (sigaction(SIGINT, &tmp, NULL));
}

/**
 * empty_handle - handler
 * @signum: signal number
 */
void empty_handle(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}
