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

typedef struct options {
	/* Print single line = 0, multiple = 1*/
	int newLine;
	/* Prints hidden dot files if dot == 1*/
	int dot;
	int longFormat;
	/* location of args for length to skip */
	int locationOfDash;
} ops;

int print(void);
int set_options(ops *list);

#endif
