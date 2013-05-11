#include "headers/servidor.h"

int validarUsuarioMensaje(char *mensaje, DatosUsuario * datosUsuario, DatosConfig *configuracion){
  int i = 0, valido = 0, fd = 0, linea = 0, lineaActual = 0;
  char * comando = strtok(mensaje, " ");
  char * usuarioMensaje = strtok(NULL, " ");
  char * passwordMensaje = strtok(NULL, " ");
  char *token, *usuario, *password;
  char lineas[100][100];  
  char buffer[512];

  /********INICIALIZAR*****/
  memset(lineas, 0, sizeof lineas);
  memset(buffer, 0, sizeof buffer);
  /************************/

  trimwhitespace(passwordMensaje);
  downcase(usuarioMensaje);
  downcase(comando);
  
  /*********CERRAR CONEXION SI EL COMANDO NO EXISTE*********/
  if(strcmp(comando, "pull") != 0 && strcmp(comando, "status") != 0){
    return -1;
  }
  
  /*************ARMAR UN ARRAY CON CADA LINEA DEL ARCHIVO CFG***********/
  char * aux = (char *)malloc(strlen(configuracion->dbUsuarios) * sizeof(char));
  memset(aux, 0, strlen(configuracion->dbUsuarios)* sizeof(char));

  strcpy(aux, configuracion->dbUsuarios);

  if((token = strtok(aux, "\n")) == NULL){
    write(1,"Error archivo de configuracion\n",31);
    return -1;
  }

  strcpy(lineas[lineaActual], token);
  
  while((token = strtok(NULL,"\n")) != NULL){
    lineaActual++;
    strcpy(lineas[lineaActual], token);
  }

  /*************BUSCAR COINCIDENCIA DE USUARIO - PASSWORD***************/
  //DEBERIAN ESTAR ENCRIPTADOS

  for(i = 0; i<=lineaActual;i++){
    usuario = strtok(lineas[i], ":");
    password = strtok(NULL,":"); //desencriptarla..

    if((strcmp(usuarioMensaje, usuario) == 0) && (strcmp(passwordMensaje, password)) == 0){
      valido = 1;
      strcpy(datosUsuario->username, usuario);
      strcpy(datosUsuario->password, password);
      strcpy(datosUsuario->usernameGit, strtok(NULL,":"));
      strcpy(datosUsuario->passwordGit, strtok(NULL,":"));
      break;
    }
  }

  if(!valido) // CERRAR CONEXION SI NO ES CORRECTO EL USUARIO O LA PASS
    return -1;

  int status = procesarComandos(comando, datosUsuario, configuracion);
  
  if(status == -1){
    return -1;
  }

  return 0;
}
