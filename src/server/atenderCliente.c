#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

int clientesConectados = 0;
pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

void* atenderCliente(void *fd)
{	
	int fd_cliente = (int)(int*)fd;
	char mensaje[50], strAux[300];
	int bytesLeidos, valor, flag;
//	Orden orden;

	DatosUsuario datosUsuario;
	memset(mensaje, 0, sizeof mensaje);
	memset(strAux, 0, sizeof strAux);
	


	if((write(fd_cliente,"Ola qase\n", 9))==-1){
		perror("Write: \n");
		pthread_exit(NULL);
		return NULL;
	}
	else
	{
		clientesConectados++;	
		printf ("Clientes Conectados: %d\n", clientesConectados);
	}
	 //ACA ESTA EL PROBLEMON
	 //FIX MAGICO
	while((bytesLeidos = read (fd_cliente, mensaje, sizeof mensaje)) > 0)
	{
		if(validarUsuarioMensaje(mensaje, &datosUsuario) == -1){
			pthread_exit(NULL);
			return NULL;
		}

		strcpy(strAux,"cd backups/");
		strcat(strAux,datosUsuario.username);
		strcat(strAux,";git pull origin master;");
		system(strAux);

	}

}

