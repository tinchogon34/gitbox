#ifndef _SERVIDOR_H_
	#define _SERVIDOR_H_

	int iniciarServidor (int);

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

  typedef struct DATOSCONFIG {
    char * dbUsuarios;
    char backupPath[30];
  } DatosConfig;

  int atenderCliente (int, DatosConfig *);  

  int validarUsuarioMensaje (char *, DatosUsuario *, DatosConfig *);

  int procesarComandoPull (DatosUsuario *, char *);

#endif
