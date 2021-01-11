#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * struct Node - a list of a racecar info
 * @laps: laps of the car
 * @car: current car ID
 * @prev: previous node
 * @next: next node
 */
typedef struct Node
{
	int laps;
	int car;
	struct Node *prev;
	struct Node *next;
} node;

void traverse(node *head, int *id, size_t size);
void race_state(int *id, size_t size);
void free_list(node *head);
node *new_node(node *head, int id);
void print_race(node *head);

#endif
