#ifndef _LS_H_
#define _LS_H_

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/**
 * struct options - data struct
 * @fileNames: If two directories are present in argv
 * @newLine_each_file: If to print a new line each file
 * @dot: 1 to print dot files
 * @longFormat: If -l is prent in arg
 * @DashExists: 1 if Dash is present in argv
 * @spacing: if spacing is needed after each set of files
 *
 * Description: Keeps track of how to print the output)?
 */

typedef struct options
{
	/* Print single line = 0, multiple = 1*/
	int fileNames;
	int newLine_each_file;
	/* Prints hidden dot files if dot == 1*/
	int dot;
	int longFormat;
	/* location of args for length to skip */
	int DashExists;
	int spacing;
	/* EXIT value here? */
} ops;

void print(int length, int argc, ops *list, char *argv[], int dash);
int print_info(ops *list, char *line);
void set_options(ops *list, char *line);
char *_strtok(char *s, char *delim);
char *_strpbrk(char *s, char *delims);
unsigned int _strspn(char *s, char *accept);
char *_strchr(char *s, char c);
int _strlen(char *s);
char *_str_error(int errnum);

#endif
