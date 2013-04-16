TARGETS = ../../bin/serverGit
CC = gcc

serverGit: iniciarServidor.o main.o atenderCliente.o validarUsuarioMensaje.o recuperarParametros.o util.o
	$(CC) -o ../../bin/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
