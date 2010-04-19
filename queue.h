#ifndef GESTURE_QUEUE
#define GESTURE_QUEUE

#include <stdlib.h>
#include <stdio.h>

typedef struct cell_t{
	double x_accel;
	double y_accel;
	double z_accel;
} cell;

typedef struct queue_t{
	cell *queue_mem;
	int curr_offset;
	int capacity;	
} queue;

//initialization function
queue* init(int capacity);
//add stuff
cell* pop();
//get stuff
void push(cell *c);

#endif /* end of include guard: GESTURE_QUEUE */
