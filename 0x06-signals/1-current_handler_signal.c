#include "signals.h"

/**
 * current_handler_signal - entry
 *
 * Return: Current handler of signal
 */
void (*current_handler_signal(void))(int)
{
	void (*old_handler)(int) = NULL;

	old_handler = signal(SIGINT, print_hello);
	if (old_handler == SIG_ERR)
		return (NULL);

	return (old_handler);
}
