TARGETS = ../../bin/cliente/clienteGit
CC = gcc

clienteGit: main.o generarMontaje.o util.o
	$(CC) -o ../../bin/cliente/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
