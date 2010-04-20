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
	if(q->curr_offset >= q->capacity){
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
		back = q->capacity - q->curr_offset;
	}
	return &(q->queue_mem[back]);
	
	
}

void print_buffer(queue *q){
	//run through the buffer, printing the values
	printf("(x, y, z)\n");
	for(int i = 0; i < q->capacity; ++i){
		printf("(%f, %f, %f)\n", q->queue_mem[i].x_accel, q->queue_mem[i].y_accel, q->queue_mem[i].z_accel);
	}
	printf("\n\n");
}

int did_jump(queue* q){
	//see if the last 5's avg is a significant jump over the previous to that's 5
	//avg the first 5 back
	//set the stage
	cell recent_5;
	recent_5.x_accel = 0;
	recent_5.y_accel = 0;
	recent_5.z_accel = 0;
	
	for(int i = 0; i < 5; ++i){
		cell *c = peek_b(q, i);
		recent_5.x_accel += c->x_accel;
		recent_5.y_accel += c->y_accel;
		recent_5.z_accel += c->z_accel;
	}
	recent_5.x_accel /= 5;
	recent_5.y_accel /= 5;
	recent_5.z_accel /= 5;
	
	cell older_5;
	older_5.x_accel = 0;
	older_5.y_accel = 0;
	older_5.z_accel = 0;
	
	for(int i = 5; i < 10; ++i){
		cell *c = peek_b(q, i);
		older_5.x_accel += c->x_accel;
		older_5.y_accel += c->y_accel;
		older_5.z_accel += c->z_accel;
	}
	older_5.x_accel /= 5;
	older_5.y_accel /= 5;
	older_5.z_accel /= 5;
	
	//now to compare. It it's a greater than 1g jump in any direction, 
	//trigger the curve fitter
	cell diff;
	diff.x_accel = fabs(recent_5.x_accel - older_5.x_accel);
	diff.y_accel = fabs(recent_5.y_accel - older_5.y_accel);
	diff.z_accel = fabs(recent_5.z_accel - older_5.z_accel);
	double threshold = 0.5;
	if(diff.x_accel > threshold || diff.y_accel > threshold || diff.z_accel > threshold){
		printf("Big Jump!\t(%f, %f, %f)\n", diff.x_accel, diff.y_accel, diff.z_accel);
		return 1;
	}
	return 0;
}