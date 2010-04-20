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
	//find_wiimote(1);
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
	
	//Now to pull the wiimote and the buffer togehter in an updater thread
	callback cb;
	register_print(&cb, &printf);
	pthread_t updater_thread;
	int rc = pthread_create(&updater_thread, NULL, start_updating, &cb);
	if(rc){
		fprintf(stderr, "Error in making the updater thread, Error#:%d\n", rc);
		exit(-1);
	}
	sleep(10);
	
	return 0;
}

