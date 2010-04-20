#include "updater.h"

void start_updating(callback *c){
	
	//alerts us that we're in business, and that the print handle is set correctly
	(*(c->handle_print))("Started update \n\n");
	
	//make a buffer
	queue *q = init_buffer(40);

	//turn on motion sensing
	enable_motion(c->wm_arg.wm, c->wm_arg.num_wm);
	

	//Start polling the wiimotes for data
	pthread_t wiimote_polling_thread;
	//set up arguments to poll_wiimote
	poll_wiimote_arg wm_arg;
	wm_arg.q = q;
	wm_arg.num_wm = c -> wm_arg.num_wm;
	wm_arg.wm = c -> wm_arg.wm;
	
	//set upt the thread attributes
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//make the thread
	int rc = pthread_create(&wiimote_polling_thread, &attr, poll_wiimote, (void*) &wm_arg);
	if(rc){
		fprintf(stderr, "Error in making the wiimote polling thread, Error#:%d\n", rc);
		exit(-1);
	}
	
	//wait a bit, then stop the thread
	//sleep(15);
	//run_polling = 0;
	
	//clear the attribute and wait
	pthread_attr_destroy(&attr);
	pthread_join(wiimote_polling_thread, NULL);
	
	//print the buffer
	print_buffer(q);
}



void register_print(callback *c, int (*h_p)(const char*, ...)){
	c->handle_print = h_p;
}
