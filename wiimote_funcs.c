#include "wiimote_funcs.h"

//Various wiimote functions
wiimote** find_wiimotes(int num){
	//where to store the wiimotes
	int maxWiimotes = num;
	wiimote** wm = wiiuse_init(maxWiimotes);
	
	//find wiimotes
	int numFound = wiiuse_find(wm, maxWiimotes, 5);
	//any found?
	if(!numFound){
		printf("No wiimotes found\n");
		return NULL;
	}
	
	//connect to the wiimote(s)
	if(wiiuse_connect(wm, maxWiimotes)){
		printf("Connected to wiimote. %i found\n", numFound);
		return wm;
	}
	else{
		return NULL;
	}
}

void close_wiimotes(wiimote** wm){
	
}

void enable_motion(wiimote** wm, int num){
	for(int i = 0; i < num; ++i){
		printf("Motion tracking enabled on Wiimote %d\n", i);
		wiiuse_motion_sensing(wm[i], 1);
	}
}

void poll_wiimote(poll_wiimote_arg *wm_arg){
	printf("Polling...\n");
	while(run_polling){
		if(wiiuse_poll(wm_arg->wm, wm_arg->num_wm)){
			// Something happened, run through the wiimotes
			for(int i = 0; i < wm_arg->num_wm; ++i){
				switch(wm_arg->wm[i]->event){
					case WIIUSE_EVENT:
					{
						//this is the only one we care about
						//copy the acceleration data over
						cell *c = (cell*)malloc(sizeof(cell));
						c -> x_accel = (wm_arg->wm[i] -> gforce.x);
						c -> y_accel = (wm_arg->wm[i] -> gforce.y);
						c -> z_accel = (wm_arg->wm[i] -> gforce.z);
						push(c, wm_arg->q);
						did_jump(wm_arg->q);
						//printf("(%f, %f, %f)\n", c -> x_accel, c -> y_accel, c -> z_accel);
						break;
					}
					case WIIUSE_STATUS:
					case WIIUSE_NONE:
					case WIIUSE_DISCONNECT:
					case WIIUSE_READ_DATA:
					case WIIUSE_NUNCHUK_INSERTED:
					case WIIUSE_NUNCHUK_REMOVED:
					case WIIUSE_CLASSIC_CTRL_INSERTED:
					case WIIUSE_CLASSIC_CTRL_REMOVED:
					case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
					case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
					default:
						//screw it, we don't care
						break;
				}
			}
		}
	}
	//TODO: exit this thread
}
