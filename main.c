#include <stdio.h>
#include <stdlib.h>

#include "wiimote_funcs.h"

int main (int argc, char const *argv[])
{
	printf("Hello, time to test out wiiuse\n");
	findWiimote();
	
	return 0;
}

