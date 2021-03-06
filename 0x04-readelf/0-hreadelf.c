#include "helf.h"

/**
 * main - entry point
 * @argc: length of argv
 * @argv: passed paramters to program
 * Return: (0) SUCCESS
 */
int main(int argc, char **argv)
{
	FILE *fp;
	int exit;

	fp = parse(argc, argv);
	if (!fp)
		return (1);
	exit = printelfh(fp, *argv);
	return (exit);
}
