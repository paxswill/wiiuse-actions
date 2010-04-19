#include "queue.h"

/*
ok, so 30 times per second, so one sample every 0.033 seconds
rapidly swapping between malloc and free would hammer the 
performance of the program, so we're using a fixed length queue
that uses a preallocated bank of memory
*/ 

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

queue* init(int c){
	queue* to_return;
	//allocate the memory
	to_return -> queue_mem = (cell*)malloc(sizeof(cell) * capacity);
	//check to make sure it was allocated (malloc returns NULL when it fails)
	if(to_return -> queue_mem == NULL){
		//failure
		fprintf(stderr, "malloc failed to allocate memory for the queue\n");
		return NULL;
	}
	
	to_return -> capacity = c;
	to_return -> curr_offset = 0;
	
	return to_return;
}

cell* pop(queue *q){
	
}

void push(cell *c, queue *q){
	
}

cell* peek(queue *q){
}

cell peek_b(queue *q, int back_num){
	
}
