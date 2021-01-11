#include "laps.h"

/**
 * race_state - state of race
 * @id: List of car ID's
 * @size: size of list id
 */
void race_state(int *id, size_t size)
{
	static node *head;
	node *tmp = NULL;
	size_t i = 0;

	if (size == 0)
	{
		free_list(head);
		return;
	}
	if (head == NULL)
	{
		head = new_node(NULL, id[0]);
		tmp = head;
		for (i = 1; i < size; i++)
		{
			new_node(tmp, id[i]);
			tmp = tmp->next;
		}
		print_race(head);
		return;
	}
	else if (head->car != id[0])
	{
		if (id == NULL)
			return;
		traverse(head, id, size);
		return;
	}
	tmp = head;
	while (tmp)
	{
		tmp->laps += 1;
		tmp = tmp->next;
	}
	print_race(head);
}

/**
 * traverse - get around 80 line limit
 * @head: head of the tree
 * @id: new id of racecars
 * @size: size of id
 */
void traverse(node *head, int *id, size_t size)
{
	size_t i;
	node *tmp = NULL;

	for (i = 0; i < size; i++)
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->car == id[i] || tmp->next == NULL)
				break;
			tmp = tmp->next;
		}
		if (tmp != NULL && tmp->car != id[i])
			new_node(head, id[i]);
	}
	print_race(head);
}

/**
 * free_list - free list
 * @head: head of node to traverse and free
 */
void free_list(node *head)
{
	node *tmp = head;

	while (tmp)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}

	free(tmp);
}
/**
 * new_node - create new node
 * @head: head of tree
 * @id: new car id
 *
 * Return: new node
 */
node *new_node(node *head, int id)
{
	node *new_node;
	node *tmp = head;

	new_node = (node *) malloc(sizeof(node));

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->laps = 0;
	new_node->car = id;
	new_node->next = NULL;
	new_node->prev = NULL;
	printf("Car %i joined the race\n", id);

	if (head == NULL)
	{
		return (new_node);
	}
	while (tmp && tmp->next)
	{
		if (tmp->next == NULL && tmp->car < new_node->car)
			break;
		if (new_node->car > tmp->car && new_node->car < tmp->next->car)
			break;
		tmp = tmp->next;
	}
	if (tmp->next != NULL)
	{
		new_node->next = tmp->next;
		tmp->next->prev = new_node;
	}
	tmp->next = new_node;
	new_node->prev = tmp;
	return (new_node);
}
/**
 * print_race - print state of race
 * @head: head of tree to traverse
 */

void print_race(node *head)
{
	node *tmp = head;

	printf("Race state:\n");

	while (tmp)
	{
		printf("Car %i [%i laps]\n", tmp->car, tmp->laps);
		tmp = tmp->next;
	}
}
