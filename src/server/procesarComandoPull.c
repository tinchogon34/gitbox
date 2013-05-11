#include "headers/servidor.h"

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
  //char *prog[] = { "sleep", "5", NULL };
  pid = fork();
 
  if (pid < 0) {     /* fork a child process           */
      printf("*** ERROR: forking child process failed\n");
      exit(1);
  }

  else if (pid == 0) {          /* for the child process:         */
      printf( "%d belongs to process group %d\n", getpid(), getpgrp() );
      strcat(path,datosUsuario->username);
      chdir(path);
      execvp(prog[0], prog);
      printf("*** ERROR: exec failed\n");
      exit(1);

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


  //recuperar el estado del git pull y devolverlo
}