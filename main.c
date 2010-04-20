#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "wiimote_funcs.h"
#include "buffer.h"
#include "updater.h"

int main (int argc, char const *argv[])
{
	//printf("Hello, time to test out wiiuse, connecting\n");
	wiimote** wm;
	int num_wiimotes = 1;
	wm = find_wiimotes(num_wiimotes);
	if(wm == NULL){
		printf("Error in connecting. exiting\n");
		exit(-2);
	}
	run_polling = 1; //true
	//set up the wm_arg
	poll_wiimote_arg wm_arg;
	wm_arg.num_wm = num_wiimotes;
	wm_arg.wm = wm;
	
	//Now to pull the wiimote and the buffer together in an updater thread
	callback cb;
	cb.wm_arg = wm_arg;
	register_print(&cb, &printf);
	//start making the thread
	pthread_t updater_thread;
	//make it joinable
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	//detach the thread
	int rc = pthread_create(&updater_thread, &attr, start_updating, (void*) &cb);
	if(rc){
		fprintf(stderr, "Error in making the updater thread, Error#:%d\n", rc);
		exit(-1);
	}
	
	//clear the attribute and wait
	pthread_attr_destroy(&attr);
	pthread_join(updater_thread, NULL);
	
	return 0;
}

