/* Servidor Pop3 - Final Computacion II
Alumnos: Mermoz, Juan Pedro
	 Pecora, Emanuel */

#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include "headers/servidor.h"
#include "headers/cliente.h"
#include "headers/config.h"
#include <string.h>
#include <stdlib.h>

int main (int argc, char * const argv[])
{
	int fd = 0, fd_cliente = 0, longitud_cliente = 0, puerto = 0;
	struct sockaddr cliente;
	pthread_t tid;

	/********INICIALIZAR*****/
  bzero(&cliente,sizeof (struct sockaddr));
  /************************/

	// Recuperar argumentos de configuracion y tratar argumentos de ayuda
	if ((puerto = recuperarParametros(argc, argv)) == -1)
		return -1;

	// Iniciar servidor con el puerto indicado
	fd = iniciarServidor(puerto);

	// Aceptar conexiones entrantes, lanzar un hilo por conexion
	while ((fd_cliente = accept (fd, &cliente, &longitud_cliente)) > 0)
	{
		printf ("Cliente conectado\n");
		pthread_create (&tid, NULL, atenderCliente, (void *)fd_cliente);
	}
}


