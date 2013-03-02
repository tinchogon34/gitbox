#ifndef _CLIENTE_H_
	#define _CLIENTE_H_

	#include <sys/socket.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <netdb.h>
	#include <pthread.h>

	typedef struct DATOSUSUARIO {
		char username[30];
		char password[30];
    char usernameGit[30];
    char passwordGit[30];
	} DatosUsuario;

	void * atenderCliente (void *);	

  int validarUsuarioMensaje (char *, DatosUsuario *);
#endif
