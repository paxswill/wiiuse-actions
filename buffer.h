#ifndef GESTURE_BUFFER
#define GESTURE_BUFFER

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
cell* pop(queue *q);
//get stuff
void push(cell *c, queue *q);

cell* pop(queue *q);

cell* peek(queue *q);

cell peek_b(queue *q, int back_num);


#endif /* end of include guard: GESTURE_BUFFER */
