#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

int clientesConectados = 0;

int atenderCliente(int fd_cliente)
{	
	int bytesLeidos = 0;
	char mensaje[50], strAux[300];
	DatosUsuario datosUsuario;

	/********INICIALIZAR*****/
	memset(mensaje, 0, sizeof mensaje);
	memset(strAux, 0, sizeof strAux);
	memset(&datosUsuario, 0, sizeof (struct DATOSUSUARIO));
	/************************/
	
	if((write(fd_cliente,"Bienvenido a GitBox\n", 20))==-1){
		perror("Write: \n");
		return -1;
	}
	
	clientesConectados++;	
	printf ("Clientes Conectados: %d\n", clientesConectados);
	
	//RECIBE EL COMANDO, LO PROCESA Y DESCONECTA -- PREGUNTAR AL PROFE
	bytesLeidos = read (fd_cliente, mensaje, sizeof mensaje);
	
	if(validarUsuarioMensaje(mensaje, &datosUsuario) == -1){
		return -1;
	}

	/*****ENTRAR A LA CARPETA DEL USUARIO Y HACER GIT PULL****/
	

	 //Que lo lea del archivo de config	
	char *prog[] = { "git", "pull", "origin", "master", NULL };
	if(fork() == 0){
		char path[20] = "backups";
		strcat(path,"/");
		strcat(path,datosUsuario.username);
		chdir(path);
		execvp(prog[0],prog);
	}


	return 0;
}

