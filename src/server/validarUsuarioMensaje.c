#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

int validarUsuarioMensaje(char *mensaje, DatosUsuario * datos){
  char buffer[100];
  char *token;
  char *lineas[100];
  char usernameLocal[30], passwordLocal[30];
  int i = 0, fd, linea = 0;

  token = strtok(mensaje, " ");
  if(strcmp(token, "PULL") != 0){
    return -1;
  }

  token = strtok(NULL, " ");
  strcpy(datos->username, token);

  token = strtok(NULL, " ");
  strcpy(datos->password, token);

  if ((fd = open ("user_config.cfg", O_RDONLY)) > 0)
  {
    read (fd, buffer, sizeof buffer);
    close (fd);

    token = strtok(mensaje, "\n");
    strcpy(lineas[linea], token);
    
    while(token = strtok(NULL, "\n")){
      linea++;
      strcpy(lineas[linea], token);
    }

    for(i=0;i<sizeof(lineas);i++){
      
      strcpy(usernameLocal, strtok(lineas[i], ":"));
      strcpy(passwordLocal, strtok(NULL, ":"));

      if((strcmp(datos->username,usernameLocal) != 0) || (strcmp(datos->password,passwordLocal) != 0)){
        return -1;
      }

      strcpy(datos->usernameGit,strtok(NULL, ":"));
      strcpy(datos->passwordGit,strtok(NULL, ":"));

    }

  }

  return 0;
}
