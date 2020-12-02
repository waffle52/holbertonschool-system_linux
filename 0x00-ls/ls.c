#include "ls.h"

/**
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
	ops *list;
	struct dirent *read = NULL;

	list = malloc(sizeof(ops));
	(void)list;

	if (argc < 2)
	{
		dir = opendir(".");
		if (dir == NULL)
		{
			perror("hls");
			return (-1);
		}
		while ((read = readdir(dir)) != NULL)
		{
			if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, "..") != 0)
				printf("%s ", read->d_name);
		}
		printf("\n");
		closedir(dir);
		return (0);
	}
	else if (argc >= 2)
	{
		/* with options */
		/* Check for - and then test options set length to next set of */
		/* Directories to print or don't set and go on to print each directory */
		/* Set custom data sturcture with options set */
		/* Check options and set them in struct options / list */
		/* SET dir to first file that doesnt start with - so probably not argv[1] */
		/* Call strtok, find element with -, parse that info and see how many args are left, save dash-location of arg to ops */
		length += 1;
	}

	while (length != argc)
	{
		/* if (length != list->locationOfDash) { } */
		dir = opendir(argv[length]);
		if (dir == NULL)
		{
			perror("hls");
		}
		while ((read = readdir(dir)) != NULL)
		{
			if (strcmp(read->d_name, ".") != 0 && strcmp(read->d_name, "..") != 0)
			{
				printf("%s ", read->d_name);
				print += 1;
			}
		}
		if (print != 0)
			printf("\n");

		/* dir = opendir(argv[length]);*/
		/* call print function with options in ops data structure that is seperated */
		length += 1;
	}
	closedir(dir);

	return (0);
}

/**
	 * Step 1: check for arguments....
	 *      -1      (The numeric digit ``one''.)
	 Force output to be one entry per line.
	 This is the default when output is not to a terminal.
	 *      -a      Include directory entries whose names begin with a dot (.)
	 *      -A      List all entries except for . and ...
	 Always set for the super-user.
	 *      -l      (The lowercase letter ``ell''.)  List in long format.
	 (See below.)  A total sum for all the file sizes is output on a
	 line before the long listing.

	 * Step 2: open/dir/files and locations. stat any files if not
	 * Step 3: Call functions with formatted output.
	 * Step 4: Free self created structure for info
*/

int print(void)
{
	return (0);
}
int set_options(ops *list)
{
	(void)list;
	return (0);
}
