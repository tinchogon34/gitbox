#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

int validarUsuarioMensaje(char *mensaje, DatosUsuario * datos){
  char * comando = strtok(mensaje, " ");
  char * usuarioMensaje = strtok(NULL, " ");
  char * passwordMensaje = strtok(NULL, " ");
  char lineas[100][100];
  char *token, *usuario, *password;
  char buffer[200];
  int i = 0, fd, linea = 0;
  int maxI = 0;
  char itoaAux[20];

  trimwhitespace(passwordMensaje);
  
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

  //porq hay pocos usuarios alcanza sin while

  token = strtok(buffer, "\n");
  strcpy(lineas[0], token);
  while((token = strtok(NULL,"\n")) != NULL){
    i++;
    strcpy(lineas[i], token);
  }

  maxI=i;

  for(i = 0; i<=maxI;i++){

    usuario = strtok(lineas[i], ":");
    password = strtok(NULL,":");

    if((strcmp(usuarioMensaje, usuario) == 0) && (strcmp(passwordMensaje, password)) == 0){
      write(1,"se valido",strlen("se valido"));

      //El segmentation fault puede estar aca en la estructura o en los strtok, revisar maniana
      strcpy(datos->username, usuario);
      strcpy(datos->password, password);
      strcpy(datos->usernameGit, strtok(NULL,":"));
      strcpy(datos->passwordGit, strtok(NULL,":"));

      /*sprintf(itoaAux,"%d",i);
      write(1, itoaAux, strlen(itoaAux));
      write(1, "\n", 1);*/

      return 0;
    }

   // return 0;
  }
  return -1;
}
