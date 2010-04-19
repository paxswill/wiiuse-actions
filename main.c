#include <stdio.h>
#include <stdlib.h>

#include <wiiuse.h>

wiimote** findWiimote();

int main (int argc, char const *argv[])
{
	printf("Hello, time to test out wiiuse\n");
	findWiimote();
	
	return 0;
}

wiimote** findWiimote(){
	//where to store the wiimotes
	int maxWiimotes = 1;
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
