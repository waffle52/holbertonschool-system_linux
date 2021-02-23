#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * handler - print msg
 * @signum: number of signal
 */
void handler(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal received\n");
}

/**
 * handle - check signal
 *
 * Return: 0 (SUCCESS)
 */
int handle(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
		return (-1);
	return (0);
}

/**
 * main - entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	if (handle() < 0)
		return (EXIT_FAILURE);
	pause();
	return (EXIT_SUCCESS);
}
