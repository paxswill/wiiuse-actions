#ifndef GESTURE_UPDATER
#define GESTURE_UPDATER

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "wiimote_funcs.h"
#include "buffer.h"

typedef struct callback_t{
	int (*handle_print)(const char*, ...);
	//TODO: add a mutex
	//technically not a callback, but only one arg for pthreads...
	poll_wiimote_arg wm_arg;
} callback;

typedef struct watcher_t{
	queue *q;
	callback* c
} watcher;

void start_updating(callback *c);

void register_print(callback* c, int (*handle_print)(const char*, ...));

#endif /* end of include guard: GESTURE_UPDATER */
