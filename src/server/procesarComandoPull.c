#include "headers/servidor.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int procesarComandoPull(DatosUsuario *datosUsuario, char * path){

  char origin[130];
  pid_t pid;
  int status = 0;

  /****************** ARMAR RUTA PARA HACER PULL DEL USUARIO ****************/
  strncat(origin, "https://",8);
  strncat(origin, datosUsuario->usernameGit, strlen(datosUsuario->usernameGit));
  strncat(origin, ":",1);
  strncat(origin, datosUsuario->passwordGit, strlen(datosUsuario->passwordGit));
  strncat(origin, "@github.com",11);
  strncat(origin, "/", 1);
  strncat(origin, datosUsuario->usernameGit, strlen(datosUsuario->usernameGit));
  strncat(origin, "/", 1);
  strncat(origin, "gitbox.git",10);
  /**************************************************************************/
  
  /*****ENTRAR A LA CARPETA DEL USUARIO Y HACER GIT PULL****/
  //Que lo lea del archivo de config (la direccion de la carpetas backups), el path debe terminar con /

  char *prog[] = { "git", "pull", origin, "master", NULL };
  
  pid = fork();

  if(pid == 0){ //hijo
    //char path[20] = "backups/";
    strcat(path,datosUsuario->username);
    chdir(path);
    execvp(prog[0],prog);
  }
  else{ //padre
    waitpid(pid, &status, 0);
    switch(status){
      case 0:
        return 0;
        break;
      default:
        return status;
        break;
    }
  }

  return 0;

  //recuperar el estado del git pull y devolverlo
}