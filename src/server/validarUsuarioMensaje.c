#include "headers/cliente.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

int validarUsuarioMensaje(char *mensaje, DatosUsuario * datos){
  int i = 0, fd = 0, linea = 0, cantidadLineas = 0;
  char * comando = strtok(mensaje, " ");
  char * usuarioMensaje = strtok(NULL, " ");
  char * passwordMensaje = strtok(NULL, " ");
  char *token, *usuario, *password;
  char lineas[100][100];  
  char buffer[512];

  /********INICIALIZAR*****/
  bzero(lineas, sizeof lineas);
  bzero(buffer, sizeof buffer);
  /************************/

  trimwhitespace(passwordMensaje);
  
  /*********TODO LISTA DE COMANDOS*********/
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

  /*************ARMAR UN ARRAY CON CADA LINEA DEL ARCHIVO CFG***********/
  if((token = strtok(buffer, "\n")) == NULL){
    write(1,"Error archivo de configuracion\n",31);
    return -1;
  }
  
  strcpy(lineas[0], token);
  i++;
  
  while((token = strtok(NULL,"\n")) != NULL){
    i++;
    strcpy(lineas[i], token);
  }

  cantidadLineas=i;

  /*************BUSCAR COINCIDENCIA DE USUARIO - PASSWORD***************/
  //DEBERIAN ESTAR ENCRIPTADOS

  for(i = 0; i<cantidadLineas;i++){
    usuario = strtok(lineas[i], ":");
    password = strtok(NULL,":");

    if((strcmp(usuarioMensaje, usuario) == 0) && (strcmp(passwordMensaje, password)) == 0){
      write(1,"se valido",strlen("se valido"));

      strcpy(datos->username, usuario);
      strcpy(datos->password, password);
      strcpy(datos->usernameGit, strtok(NULL,":"));
      strcpy(datos->passwordGit, strtok(NULL,":"));

      return 0;
    }

  }

  return -1;
}
