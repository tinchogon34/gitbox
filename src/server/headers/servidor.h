#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

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
    int puerto;
  } DatosConfig;

  int atenderCliente (int, DatosConfig *);  

  int validarUsuarioMensaje (char *, DatosUsuario *, DatosConfig *);

  int procesarComandoPull (DatosUsuario *, char *);

  int procesarComandos (char *, DatosUsuario *, DatosConfig *);

#endif
