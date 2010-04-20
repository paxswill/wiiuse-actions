#ifndef GESTURE_UPDATER
#define GESTURE_UPDATER

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "wiimote_funcs.h"
#include "buffer.h"

typedef struct callback_t{
	int (*handle_print)(const char*, ...);
	//TODO: add a mutex
} callback;

void start_updating(callback *c);

void register_print(callback* c, int (*handle_print)(const char*, ...));

#endif /* end of include guard: GESTURE_UPDATER */
