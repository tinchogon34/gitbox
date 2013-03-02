TARGETS = ../../bin/serverGit
CC = gcc

serverGit: iniciarServidor.o main.o parsearOrden.o atenderCliente.o verificarOrden.o procesarUSER.o procesarPASS.o procesarLIST.o recuperarListaMail.o procesarSTAT.o procesarRETR.o procesarNOOP.o procesarDELE.o recuperarCantidadMails.o procesarRSET.o procesarQUIT.o recuperarFecha.o procesarTransaccion.o crearCola.o escribirEnCola.o recuperarParametros.o
	$(CC) -o ../../bin/$@ $^ -lpthread -lrt

clean:
	rm -fv $(TARGETS) *.o *~
