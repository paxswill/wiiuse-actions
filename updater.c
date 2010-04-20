#include "updater.h"

void start_updating(callback *c){
	
	//alerts us that we're in business, and that the print handle is set correctly
	(*(c->handle_print))("Started update \n\n");
	
	//make a buffer
	queue *q = init_buffer(400);
	
	//set upt the thread attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	
	//wait a bit, then stop the thread
	sleep(10);
	run_polling = 0;
	
	//clear the attribute and wait
	pthread_attr_destroy(&attr);
	pthread_join(wiimote_polling_thread, NULL);
	
	//print the buffer
	print_buffer(q);
}


void register_print(callback *c, int (*h_p)(const char*, ...)){
	c->handle_print = h_p;
}
