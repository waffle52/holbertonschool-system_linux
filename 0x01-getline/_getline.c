#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "_getline.h"

/**
 * _getline - Basic getline
 * @fd: File Descriptor
 * Return: Returns a null-terminated string that does not include the newline
 * character, or NULL if there is a reading failure or reach EOF.
 */
char *_getline(const int fd)
{
	char *str;
	char *s = NULL, *buffer, buf[READ_SIZE + 1];
	ssize_t track;
	size_t i = 0;
	listfd_t *node;

	while ((node = nodelist(fd)) == NULL)
		return (NULL);

	str = node->text;
	buffer = malloc((BUFF_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	strcpy(buffer, str), str[0] = '\0', s = search(buffer, 10);
	if (s != NULL)
	{	*s = '\0', s++;
		strcpy(str, s);
		return (buffer);
	}
	i = _strlen(buffer);

	while ((track = read(fd, (void *)buf, READ_SIZE)) > 0)
	{
		buf[track] = '\0', findnull(buf, track, 1), s = search(buf, 10);
		if (s == NULL)
			strcpy((buffer + i), buf), i += track;
		else
		{	*s = '\0', s++;
			strcpy((buffer + i), buf);
			strcpy(str, s);
			break;
		}
	}
	if ((track == -1 || track == 0) && _strlen(buffer) == 0)
	{
		free(buffer);
		return (NULL);
	}
	findnull(buffer, _strlen(buffer), 0);
	return (buffer);
}

/**
 * search - Pointer to the first occurence of c char in string str
 * @str: The string
 * @c: The char
 * Return: A pointer to the position or NULL
 */
char *search(char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}

	return (NULL);
}

/**
 * _strlen - Returns the length of the string str
 * @str: The string
 * Return: The length of str
 */
size_t _strlen(char *str)
{
	size_t i = 0;

	while (*str != '\0')
		str++, i++;
	return (i);
}

/**
 * nodelist - Put or Get a node from a linked list
 * @fd: The file descriptor
 * Return: A pointer to a node from listfd_s or NULL
 */
listfd_t *nodelist(int fd)
{
	static listfd_t *head;
	listfd_t *node, *curr, *prev;

	if (fd == -1)
	{
		curr = head;
		while (curr != NULL)
			node = curr, curr = curr->next, free(node);
		head = NULL;
		return (NULL);
	}
	node = malloc(sizeof(listfd_t));
	if (node == NULL)
		return (NULL);
	node->fd = fd, node->text[0] = '\0', node->next = NULL;
	if (head == NULL)
	{
		head = node;
		return (head);
	}
	curr = head;
	while (curr != NULL)
	{
		if (curr->fd != fd)
			prev = curr, curr = curr->next;
		else
			break;
	}
	if (curr != NULL)
	{
		free(node);
		return (curr);
	}
	prev->next = node;
	return (node);
}

/**
 * findnull - Mark the null char
 * @str: the string to format
 * @len: the length to process
 * @ope: the operator
 */
void findnull(char *str, size_t len, char ope)
{
	size_t iter = 0;

	for (iter = 0; iter < len; iter++)
	{
		if (ope == 0)
		{
			if (str[iter] == '\0')
				str[iter] = '\r';
		}
		else
		{
			if (str[iter] == '\r')
				str[iter] = '\0';
		}
	}
}
