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

