#include "updater.h"

void start_updating(callback *c){
	
	//alerts us that we're in business, and that the print handle is set correctly
	(*(c->handle_print))("Started update \n\n");
	
	//make a buffer
	queue *q = init_buffer(400);
	
	
}


void register_print(callback *c, int (*h_p)(const char*, ...)){
	c->handle_print = h_p;
}
