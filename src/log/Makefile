TARGETS = ../../bin/log
CC = gcc

log: main.o escribirEnLog.o
	$(CC) -o ../../bin/$@ $^ -lpthread -lrt

clean: 
	rm -fv $(TARGETS) *.o *~
