#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * main - entry point
 * @argc: number of args
 * @argv: args passed to program
 *
 * Return: 1 (SUCCESS)
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (kill(atoi(argv[1]), SIGINT) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
