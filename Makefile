all: main.o wiimote_funcs.o buffer.o updater.o
	clang -lm -lwiiuse -pthread -g main.o wiimote_funcs.o buffer.o updater.o -o wiiuse-basic

# Main
main.o: main.c
	clang -pthread -std=c99 -Wall -g -c main.c -o main.o

# The wiimote wrapper functions
wiimote_funcs.o: wiimote_funcs.c
	clang -std=c99 -Wall -g -c wiimote_funcs.c -o wiimote_funcs.o	

# The low-latency buffer
buffer.o: buffer.h buffer.c
	clang -std=c99 -Wall -g -c buffer.c -o buffer.o

# The updater
updater.o: updater.h updater.c
	clang -std=c99 -Wall -pthread -g -c updater.c -o updater.o


# Runs make on the VM on my machine
remote:
	ssh -p 2222 localhost 'cd /mnt/hgfs/CS350/wiiuse-basic/; make all'

# Remote clean
rclean:
	ssh -p 2222 localhost 'cd /mnt/hgfs/CS350/wiiuse-basic/; make clean'


#Optimize the hell out of this
fast:
	gcc -std=c99 -O3 -lm -lwiiuse -pthread main.c wiimote_funcs.c buffer.c updater.c -o wiiuse-fast

# Clean up
clean:
	rm *.o
	rm wiiuse-basic
