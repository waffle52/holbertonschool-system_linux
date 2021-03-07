#ifndef __GETLINE_H_
#define __GETLINE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define READ_SIZE 4
#define BUFF_SIZE 512

/**
 * struct reader_s - linked list for fd text
 * @fd: The file descriptor associated
 * @buf: The buffer static associated to fd
 * @bytes: info
 * @next: The pointer to the next node
 */
typedef struct reader_s
{
	int fd;
	char *buf;
	int bytes;
	struct reader_s *next;
} reader_t;

char *_getline(const int fd);
char *find_line(reader_t *rd);

#endif
