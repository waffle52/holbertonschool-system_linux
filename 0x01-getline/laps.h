#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * struct car_s - a list of a racecar info
 * @laps: laps of the car
 * @id: current car ID
 * @next: next node
 */
typedef struct car_s
{
	int id;
	int laps;
	struct car_s *next;
} car_t;

void race_state(int *id, size_t size);

#endif
