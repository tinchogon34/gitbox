#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include "headers/servidor.h"
#include "headers/cliente.h"
#include "headers/config.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define CANT_HIJOS 2

int main (int argc, char * const argv[])
{
	int fd = 0, fd_cliente = 0, longitud_cliente = 0, puerto = 0, 
	cpid = 0, i = 0, file_fd = 0;
	off_t fileSize;
	unsigned long long fileSizeL;
	struct sockaddr cliente;
	pthread_t tid;
	char * dbUsuarios;

	/********INICIALIZAR*****/
	memset(&cliente,0, sizeof (struct sockaddr));
  /************************/

	if ((file_fd = open ("user_config.cfg", O_RDONLY)) < 0)
	{
		perror("open:");
		return -1;
	}

	fileSize = lseek(file_fd , 0L , SEEK_END);
	lseek(file_fd,0L, SEEK_SET);
	fileSizeL=(unsigned long long) fileSize;

	dbUsuarios = (char *) malloc(sizeof(char) * (fileSizeL+1) );

	read (file_fd, dbUsuarios, fileSizeL+1);

	write(1,dbUsuarios,fileSizeL+1);

//**********Todo el archivo de usuarios queda en dbUsuarios*******************//
	
	// Recuperar argumentos de configuracion y tratar argumentos de ayuda
	if ((puerto = recuperarParametros(argc, argv)) == -1)
		return -1;

	// Iniciar servidor con el puerto indicado
	fd = iniciarServidor(puerto);

	/* Preforkear un par */
	for (i = 0; i < CANT_HIJOS; i++) {
		cpid = fork();
		if (cpid == -1) {
			die("No se pudo forkear");
		}

		if (cpid == 0) { // Si estamos en el hijo
			for (;;) {

				longitud_cliente = sizeof cliente;

				fd_cliente = accept(fd, &cliente, &longitud_cliente);

				if (fd_cliente == -1) {
					die("No se pudo aceptar la conexion");
				}

				
				/*****Codigo importante del hijo*********/
				atenderCliente(fd_cliente);

				/* Cerrar el socket */
				close(fd_cliente);
	    	/****************************************/
			}
		}
	}

	 /* El padre espera a todos los hijos antes de cerrarse */
	while (waitpid(-1, NULL, 0) > 0);

   /* Cerrar el socket una vez que todos los hijos terminaron */
	close(fd);

	return 0;
}


