#include "hls.h"

/**
 * main - Entry Point
 * @argc: number of elements in argv
 * @argv: elements passed as arguments to program
 * Description: Prints directories passed to argv)?
 * Return: 0 (SUCCESS)
 */

int main(int argc, char *argv[])
{
	int length = 0, dash = 1, exit_status = 0;
	ops *list;
	char *token;

	list = malloc(sizeof(ops));
	list->fileNames = 0, list->newLine_each_file = 0, list->dot = 0;
	list->longFormat = 0, list->DashExists = 0, list->spacing = 0;

	if (argc < 2)
	{
		print_info(list, ".");
		printf("\n");
		free(list);
		return (exit_status);
	}
	while (dash != argc)
	{
		if (strncmp(argv[dash], "-", 1) == 0)
		{
			list->DashExists = 1;
			break;
		}
		dash += 1;
	}
	if (list->DashExists != 0)
	{
		token = _strtok(argv[dash], "");
		set_options(list, token);
	}
	if ((list->DashExists == 0 && argc >= 3) ||
	    (list->DashExists == 1 && argc >= 4))
	{
		list->fileNames = 1;
		list->spacing = 1;
	}
	length += 1;
	print(length, argc, list, argv, dash);
	return (exit_status);
}


/**
 * print - decide info to print
 * @length: current position of arg
 * @argc: numbers of arguments passed
 * @list: options to pass to print
 * @argv: arguments passed to main
 * @dash: location of dash to avoid in args
 *
 * Description: Decides whethe to print locally or from argv)?
 */
void print(int length, int argc, ops *list, char *argv[], int dash)
{
	while (length != argc)
	{
		if (list->DashExists == 1 && argc == 2)
		{
			print_info(list, ".");
			printf("\n");
		}
		else if (length != dash)
		{
			if (length + 1 == dash)
				list->spacing = 0;
			print_info(list, argv[length]);
			printf("\n");
		}
		length += 1;
	}
	free(list);
}

/**
 * print_info - print data
 * @list: list to format output
 * @line: Current direcotry to open
 *
 * Description: Prints the info passed to open in argv formatted by list)?
 * Return: 0 (SUCCESS)
 */

int print_info(ops *list, char *line)
{
	struct dirent *read;
	DIR *dir;
	char *str;
	int first_run = 0;
	int errnum;

	dir = opendir(line);
	if (dir == NULL)
	{
		errnum = errno;
		if (errnum == 2)
			str = "cannot access";
		else
			str = "cannot open";
		fprintf(stderr, "hls: %s %s: %s", str, line, _str_error(errnum));
		return (1);
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (first_run == 0 && list->fileNames == 1)
			printf("%s:\n", line);
		if (strncmp(read->d_name, ".", 1) == 0 && list->dot == 1)
			printf("%s ", read->d_name);
		else if (strncmp(read->d_name, ".", 1) != 0)
			printf("%s ", read->d_name);
		if (list->newLine_each_file == 1)
			printf("\n");
		first_run += 1;
	}
	if (list->spacing == 1)
		printf("\n");
	closedir(dir);
	return (0);
}

/**
 * set_options - set output formatting
 * @list: data struct to set
 * @line: check options via argv
 *
 * Description: Sets the data in list defined the parameters passed in argv)?
 */
void set_options(ops *list, char *line)
{
	/* line that has - split with strtok*/
	size_t i = 1;

	for (i = 1; i < strlen(line); i++)
	{
		if (line[i] == '1')
		{
			list->newLine_each_file = 1;
		}
		if (line[i] == 'a')
		{
			list->dot = 1;
		}
		if (line[i] == 'A')
		{
			list->dot = 0;
		}
		if (line[i] == 'l')
		{
			list->longFormat = 1;
		}
	}
}

char *_str_error(int errnum)
{
	switch (errnum)
	{
	case 1:
		return ("Operation not permitted");
	case 2:
		return ("No such file or directory");
	case 3:
		return ("No such process");
	case 4:
		return ("Interrupted system call");
	case 5:
		return ("I/O error");
	case 6:
		return ("No such device or address");
	case 7:
		return ("Argument list too long");
	case 8:
		return ("Exec format error");
	case 9:
		return ("No child processes");
	case 10:
		return ("Try again");
	case 11:
		return ("Out of memory");
	case 12:
		return ("Out of memory");
	case 13:
		return ("Permission denied");
	default:
		return ("");
	}
}
