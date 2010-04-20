#include <stdio.h>
#include <stdlib.h>

#include "wiimote_funcs.h"
#include "buffer.h"

int main (int argc, char const *argv[])
{
	//printf("Hello, time to test out wiiuse, connecting\n");
	//findWiimote();
	
	printf("\nOk, now test the buffer\n");
	queue *q = init_buffer(5);
	for(int i = 1; i < 6; ++i){
		cell *c = (cell*)malloc(sizeof(cell));
		c->x_accel = (double)i;
		c->y_accel = (double)i;
		c->z_accel = (double)i;
		push(c, q);
	}
	print_buffer(q);
	
	return 0;
}

