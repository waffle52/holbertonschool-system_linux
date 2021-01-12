#ifndef __GETLINE_H_
#define __GETLINE_H_

#define READ_SIZE 4
#define BUFF_SIZE 512

/**
 * struct listfd_s - linked list for fd text
 * @fd: The file descriptor associated
 * @text: The buffer static associated to fd
 * @next: The pointer to the next node
 */
typedef struct listfd_s
{
	int fd;
	char text[BUFF_SIZE];
	struct listfd_s *next;
} listfd_t;

char *_getline(const int fd);

char *search(char *str, int c);
size_t _strlen(char *str);
listfd_t *nodelist(int fd);
void findnull(char *str, size_t len, char ope);

#endif
