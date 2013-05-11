TARGETS = ../../bin/clienteGit
CC = gcc

clienteGit: main.o
	$(CC) -o ../../bin/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
