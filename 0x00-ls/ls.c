#include "ls.h"

/**.
 * main - Entry Point
 * @argc:
 * @argv:
 * Description: )?
 * Return:
 */

int main(int argc, char *argv[])
{
	DIR *dir;
	int length = 0;
	int print = 0;
	int errnum = 0;
	int exit_status = 0;
	int dash = 1;
	ops *list;
	char *token;
	struct dirent *read = NULL;

	list = malloc(sizeof(ops));
	list->DashExists = 0;

	if (argc < 2)
	{
		dir = opendir(".");
		if (dir == NULL)
		{
			perror("hls");
			return (2);
		}
		while ((read = readdir(dir)) != NULL)
		{
			/* SET option to not print . amd .. */
			print_info(list, read);
				/* printf("%s ", read->d_name); */
		}
		printf("\n");
		closedir(dir);
		free(list);
		return (exit_status);
	}
	else if (argc >= 2)
	{
		/* Search only length of argc */
		/* ERROR what if nly dash and no file EX: ls -la */
		while (dash != argc)
		{
			if (strncmp(argv[dash], "-", 1) == 0)
				break;
			dash += 1;
		}
		if (strncmp(argv[dash], "-", 1) == 0)
			list->DashExists = 1;
		if (list->DashExists != 0)
		{
			token = strtok(argv[dash], "");
			set_options(list, token);
		}
		length += 1;
	}

	while (length != argc)
	{
		if (length != dash)
		{
			dir = opendir(argv[length]);
			if (dir == NULL)
			{
				errnum = errno;
				fprintf(stderr, "hls: cannot open directory '%s': %s\n", argv[length], strerror(errnum));
				exit_status = 2;
				break;
			}
			while ((read = readdir(dir)) != NULL)
			{
				
					/*printf("%s ", read->d_name);*/
				print_info(list, read);
					print += 1;
				
			}
			/*if (print != 0)
			  printf("\n");*/
			closedir(dir);
		}
		length += 1;
	}
	free(list);
	return (exit_status);
}

void print_info(ops *list, struct dirent *read)
{
	while (){
		if (list->dot == 1)
		{
			
		}
		if (list->newLine == 1)
			printf("\n");
	}

}
void set_options(ops *list, char *line)
{
	/* line that has - split with strtok*/
	size_t i = 1;

	for (i = 1; i < strlen(line); i++)
	{
		if (line[i] == '1')
		{
			list->newLine = 1;
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
