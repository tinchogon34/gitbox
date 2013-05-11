TARGETS = ../../bin/server/serverGit
CC = gcc

serverGit: iniciarServidor.o procesarComandos.o procesarComandoPull.o main.o atenderCliente.o validarUsuarioMensaje.o recuperarParametros.o util.o
	$(CC) -o ../../bin/server/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
