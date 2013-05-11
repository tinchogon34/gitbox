#include "headers/cliente.h"
#include "headers/util.h"

int generarMontaje(){
  pid_t pid = fork();

  if(pid == 0){
    char *command[] = {"sshfs","localhost:gitbox/","gitbox","-o","follow_symlinks",NULL};
    execvp(command[0],command);
    return -1;
  }
  else{
    waitpid(pid, NULL, 0);  
  }  

  return 0;

}