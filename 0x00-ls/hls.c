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
			if (print_info(list, argv[length]) == 0)
				printf("\n");
		}
		length += 1;
	}
	free(list);
}

/**
 * print_info - print data
 * @list: list to format output
 * @line: Current directory to open
 *
 * Description: Prints the info passed to open in argv formatted by list)?
 * Return: 0 (SUCCESS)
 */

int print_info(ops *list, char *line)
{
	struct dirent *read;
	DIR *dir;
	char *str;
	int first_run = 1;
	int length = 0;
	int errnum;

	dir = opendir(line);
	if (dir == NULL)
	{
		errnum = errno;
		if (errnum == ENOTDIR)
		{
			printf("%s\n", line);
			return (1);
		}
		str = "cannot open directory";
		if (errnum == 2)
			str = "cannot access";
		fprintf(stderr, "hls: %s %s: %s\n", str, line, _str_error(errnum));
		return (1);
	}
	while ((read = readdir(dir)) != NULL)
	{
		length++;
	}
	if (list->dot == 0)
		length -= 2;
	closedir(dir);
	dir = opendir(line);
	read = NULL;
	while ((read = readdir(dir)) != NULL)
	{
		sec_print(first_run, length, list, line, read);
		first_run += 1;
	}
	if (list->spacing == 1)
		printf("\n");
	closedir(dir);
	return (0);
}

/**
 * sec_print - sec print func
 * @first_run: current state of loop
 * @length: length of items to print
 * @list: how to format the output
 * @line: current directory to open
 * @read: read data structure with names
 */
void sec_print(int first_run, int length, ops *list, char *line,
	       info *read)
{
	if ((list->longFormat == 1 && (strncmp(read->d_name, ".", 1) != 0)) || (list->longFormat == 1 &&
				      (strncmp(read->d_name, ".", 1) == 0)
				      && list->dot == 1))
	{
		longFormat(line);
	}
	
	if (first_run == 1 && list->fileNames == 1)
	{
		printf("%s:\n", line);
		if (list->newLine_each_file == 1)
			printf("\n");
	}
	if (strncmp(read->d_name, ".", 1) == 0 && list->dot == 1)
	{
		printf("%s ", read->d_name);
		if (list->newLine_each_file == 1 && first_run != length)
			printf("\n");
	}
	else if (strncmp(read->d_name, ".", 1) != 0)
	{
		printf("%s ", read->d_name);
		if (list->newLine_each_file == 1 && first_run != length)
		{
			printf("\n");
		}

	}
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
	unsigned int i = 1;

	for (i = 1; i < _strlen(line); i++)
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
			list->dot = 1;
		}
		if (line[i] == 'l')
		{
			list->longFormat = 1;
			list->newLine_each_file = 1;
		}
	}
}
