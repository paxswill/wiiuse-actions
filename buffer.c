#include "buffer.h"

/*
ok, so 30 times per second, so one sample every 0.033 seconds
rapidly swapping between malloc and free would hammer the 
performance of the program, so we're using a fixed length queue
that uses a preallocated bank of memory
*/ 

queue* init_buffer(int c){
	queue *to_return = (queue*)malloc(sizeof(queue));
	//allocate the memory
	(to_return -> queue_mem) = (cell*)malloc(sizeof(cell) * c);
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

void push(cell *c, queue *q){
	if(q->curr_offset+1 >= q->capacity){
		//loop around
		q->curr_offset = 0;
	}
	q->queue_mem[q->curr_offset++] = *c;
}

cell* peek(queue *q){
	int offset;
	if(q->curr_offset == 0){
		//loop back
		offset = 0;
	}else{
		//go back one
		offset = q->curr_offset - 1;
	}
	//offset-1 as offset points to the next memory address to erase
	return q->queue_mem + offset;
}

cell* peek_b(queue *q, int back_num){
	int back = back_num % q->capacity; //so we don't keep looping back
	if(back > q->curr_offset){
		//we loop backwards
		
	}
	
	
}

void print_buffer(queue *q){
	//run through the buffer, printing the values
	printf("(x, y, z)\n");
	for(int i = 0; i < q->capacity; ++i){
		printf("(%f, %f, %f)\n", q->queue_mem[i].x_accel, q->queue_mem[i].y_accel, q->queue_mem[i].z_accel);
	}
	printf("\n\n");
}