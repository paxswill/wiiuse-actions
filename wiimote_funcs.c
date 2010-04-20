#include "wiimote_funcs.h"

//Various wiimote functions
wiimote** find_wiimotes(int num){
	//where to store the wiimotes
	int maxWiimotes = num;
	wiimote** wm = wiiuse_init(maxWiimotes);
	
	//find wiimotes
	int numFound = wiiuse_find(wm, maxWiimotes, 5);
	
	//connect to the wiimote(s)
	if(wiiuse_connect(wm, maxWiimotes)){
		printf("Connected to wiimote. %i found\n", numFound);
		return wm;
	}
	else{
		return 0;
	}
}

void close_wiimotes(wiimote** wm){
	
}