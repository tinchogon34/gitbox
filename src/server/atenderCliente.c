#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

int clientesConectados = 0;

void* atenderCliente(void *fd)
{	
	int fd_cliente = (int)(int*)fd;
	int bytesLeidos = 0;
	char mensaje[50], strAux[300];
	DatosUsuario datosUsuario;

	/********INICIALIZAR*****/
	bzero(mensaje, sizeof mensaje);
	bzero(strAux, sizeof strAux);
	bzero(&datosUsuario, sizeof (struct DATOSUSUARIO));
	/************************/
	
	if((write(fd_cliente,"Bienvenido a GitBox\n", 20))==-1){
		perror("Write: \n");
		pthread_exit(NULL);
		return NULL;
	}
	
	clientesConectados++;	
	printf ("Clientes Conectados: %d\n", clientesConectados);
	
	//ACA ESTA EL PROBLEMON
	//FIX MAGICO	
	while((bytesLeidos = read (fd_cliente, mensaje, sizeof mensaje)) > 0)
	{
		if(validarUsuarioMensaje(mensaje, &datosUsuario) == -1){
			pthread_exit(NULL);
			return NULL;
		}

		/*****ENTRAR A LA CARPETA DEL USUARIO Y HACER GIT PULL****/
		strcpy(strAux,"cd backups/");
		strcat(strAux,datosUsuario.username);
		strcat(strAux,";git pull origin master;");
		system(strAux);

	}

}

