#ifndef GESTURE_BUFFER
#define GESTURE_BUFFER

#include <stdlib.h>
#include <stdio.h>

typedef struct cell_t{
	double x_accel;
	double y_accel;
	double z_accel;
	short buttons;
	/*
	The above variable is a packed representation of the state of 
	all 11 buttons on a wiimote. In order:
	0x0001	Up
	0x0002	Left
	0x0004	Down
	0x0008	Right
	0x0010	A
	0x0020	B
	0x0040	Minus
	0x0080	Home
	0x0100	Plus
	0x0200	1
	0x0400	2
	*/
} cell;

typedef struct queue_t{
	cell *queue_mem;
	int curr_offset;
	int capacity;	
} queue;

//initialization function
queue* init_buffer(int capacity);
//get stuff
void push(cell *c, queue *q);

cell* pop(queue *q);

cell* peek(queue *q);

cell* peek_b(queue *q, int back_num);

void print_buffer(queue *q);

#endif /* end of include guard: GESTURE_BUFFER */
