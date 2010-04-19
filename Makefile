all: main.o wiimote_funcs.o buffer.o
	clang -lm -lwiiuse -g main.o wiimote_funcs.o buffer.o -o wiiuse-basic

# Main
main.o: main.c
	clang -std=c99 -Wall -g -c main.c -o main.o

# The wiimote wrapper functions
wiimote_funcs.o: wiimote_funcs.c
	clang -std=c99 -Wall -g -c wiimote_funcs.c -o wiimote_funcs.o	

# The low-latency buffer
buffer.o: buffer.h buffer.c
	clang -std=c99 -Wall -g -c buffer.c -o buffer.o

# Runs make on the VM on my machine
remote:
	ssh -p 2222 localhost 'cd /mnt/hgfs/CS350/wiiuse-basic/; make all'

# Remote clean
rclean:
	ssh -p 2222 localhost 'cd /mnt/hgfs/CS350/wiiuse-basic/; make clean'

# Clean up
clean:
	rm *.o
	rm wiiuse-basic
