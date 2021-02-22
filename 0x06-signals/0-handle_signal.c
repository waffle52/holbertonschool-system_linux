#include "signals.h"

/**
 * handle_signal - entry
 * Return: 0 (SUCCESS) -1 fail
 */
int handle_signal(void)
{
	if (signal(SIGINT, handle) == SIG_ERR)
	{
		return (-1);
	}
	return (0);
}

/**
 * handle - handle sig
 * @signum: number of signal caught
 */
void handle(int signum)
{
	printf("Gotcha! [%i]\n", signum);
}
