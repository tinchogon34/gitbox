TARGETS = ../../bin/serverGit
CC = gcc

serverGit: iniciarServidor.o procesarComandos.o procesarComandoPull.o main.o atenderCliente.o validarUsuarioMensaje.o recuperarParametros.o util.o
	$(CC) -o ../../bin/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
