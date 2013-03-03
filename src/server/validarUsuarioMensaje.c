#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

int validarUsuarioMensaje(char *mensaje, DatosUsuario * datos){
  char * comando = strtok(mensaje, " ");
  char * usuarioMensaje = strtok(NULL, " ");
  char * passwordMensaje = strtok(NULL, " ");
  char lineas[100][100];
  char *token, *usuario, *password;
  char buffer[100];
  int i = 0, fd, linea = 0;

  write(1, "ee", 2);

  if(strcmp(comando, "PULL") != 0){
    return -1;
  }

  if ((fd = open ("user_config.cfg", O_RDONLY)) < 0)
  {
    perror("open:");
    return -1;
  }

  read (fd, buffer, sizeof buffer);
  close (fd);

  token = strtok(buffer, "\n");
  strcpy(lineas[0], token);
  while((token = strtok(NULL,"\n")) != NULL){
    i++;
    strcpy(lineas[i], token);
  }


  for(i = 0; i<100;i++){
    usuario = strtok(lineas[i], ":");
    password = strtok(NULL,":");
    printf(usuario);
    printf(password);
   /* if((strcmp(usuarioMensaje, usuario) == 0) && (strcmp(passwordMensaje, password)) == 0){
    /*  strcpy(datos->username, usuario);
      strcpy(datos->password, password);
      strcpy(datos->usernameGit, strtok(NULL,":"));
      strcpy(datos->passwordGit, strtok(NULL,":"));
      return 0;
    }*/

    return 0;
  //}
  }

  return -1;
}
