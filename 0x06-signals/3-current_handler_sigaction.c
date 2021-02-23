#include "signals.h"

/**
 * current_handler_sigaction - entry
 *
 * Return: Handler of signal
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction curr;

	if (sigaction(SIGINT, NULL, &curr) < 0)
		return (NULL);
	return (curr.sa_handler);
}
