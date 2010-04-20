#ifndef GESTURE_WIIMOTE
#define GESTURE_WIIMOTE

#include <wiiuse.h>

#include "buffer.h"

int run_polling;

typedef struct poll_wiimote_arg_t{
	queue *q;
	wiimote **wm;
	int num_wm;
} poll_wiimote_arg;


//find the 
wiimote** find_wiimotes(int num);

void poll_wiimote(poll_wiimote_arg *wm_arg);

void enable_motion(wiimote** wm, int num);


#endif /* end of include guard: GESTURE_WIIMOTE */
