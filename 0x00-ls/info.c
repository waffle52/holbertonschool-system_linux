#include "hls.h"

void longFormat(char *line)
{
	char str[512];
	struct stat sb;

	if (lstat(line, &sb) == -1)	/* If the path has a problem */
		return ;
	
	sprintf(str, "%c%c%c%c%c%c%c%c%c%c %*d %*s %*s %*d %s %s%s",/* The line */
		t[(sb.st_mode & S_IFMT) / 010000], r[(sb.st_mode & S_IRWXU) / 0100],
		w[(sb.st_mode & S_IRWXU) / 0100], x[(sb.st_mode & S_IRWXU) / 0100],
		r[(sb.st_mode & S_IRWXG) / 010], w[(sb.st_mode & S_IRWXG) / 010],
		x[(sb.st_mode & S_IRWXG) / 010], r[(sb.st_mode & S_IRWXO)],
		w[(sb.st_mode & S_IRWXO)], x[(sb.st_mode & S_IRWXO)], w_ln, (int)sb.st_nlink,
		-w_ur, susr, -w_gr, sgrp, w_sz, (int)sb.st_size, (time + 4), path, lpath);
}
