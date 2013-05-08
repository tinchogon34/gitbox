#include "headers/servidor.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

//int clientesConectados = 0;

int atenderCliente(int fd_cliente, DatosConfig *configuracion)
{	
	int bytesLeidos = 0;
	char mensaje[50], strAux[300], origin[130];
	DatosUsuario datosUsuario;

	/********INICIALIZAR*****/
	memset(mensaje, 0, sizeof mensaje);
	memset(strAux, 0, sizeof strAux);
	memset(origin, 0, sizeof origin);
	memset(&datosUsuario, 0, sizeof (struct DATOSUSUARIO));
	//RESERVAR MEMORIA PARA LOS CAMPOS DE CONFIGURACION
	/************************/
	
	if((write(fd_cliente,"Bienvenido a GitBox\n", 20))==-1){
		perror("Write: \n");
		return -1;
	}

	
	//clientesConectados++;	
	//printf ("Clientes Conectados: %d\n", clientesConectados);
	
	//RECIBE EL COMANDO, LO PROCESA Y DESCONECTA -- PREGUNTAR AL PROFE
	bytesLeidos = read (fd_cliente, mensaje, sizeof mensaje);

	
	if(validarUsuarioMensaje(mensaje, &datosUsuario, configuracion) == -1){
		return -1;
	}

	
	return 0;
}

