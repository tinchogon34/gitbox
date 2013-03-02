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
	int fd, fd_cliente, longitud_cliente;
	struct sockaddr cliente;
	pthread_t tid;
	int puerto;

	/*// Crear proceso paralelo para ejecutar log
	if (fork() == 0)		
	{
		if ((execl("log", "", (char *)NULL)) == -1)
			perror ("execl()\n");
	}
*/

	// Recuperar argumentos de configuracion y tratar argumentos de ayuda
	if ((puerto = recuperarParametros(argc, argv)) == -1)
		return -1;

	/*// Iniciar cola de mensajes
	if (crearCola() == -1)
		printf ("Cola no creada, no se generaran logs\n");
	*/

	// Iniciar servidor con el puerto indicado
	fd = iniciarServidor(puerto);

	// Aceptar conexiones entrantes, lanzar un hilo por conexion
	while ((fd_cliente = accept (fd, &cliente, &longitud_cliente)) > 0)
	{
		printf ("Cliente conectado\n");
		pthread_create (&tid, NULL, atenderCliente, (void *)fd_cliente);
	}
}


