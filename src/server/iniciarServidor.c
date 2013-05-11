#include "headers/servidor.h"

int iniciarServidor (int puerto)
{
  int fd = 0, opc = 1, sfd = 0;
  struct addrinfo Direccion,*res;
  char auxport[5];

  sprintf(auxport,"%d",puerto);

  /********INICIALIZAR*****/
  memset(&Direccion,0, sizeof (struct addrinfo));
  /************************/

  Direccion.ai_family = AF_UNSPEC; 
  Direccion.ai_socktype= SOCK_STREAM; 
  Direccion.ai_flags = AI_PASSIVE; 

  // TODO Harcodie el puerto MAL jaja
  if((getaddrinfo(NULL,auxport,&Direccion,&res))!=0){
    perror("getaddrinfo:");
    exit(EXIT_FAILURE);
  }
  
  do
  {
    sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if (sfd  < 0)
      continue;
    
    setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&opc,sizeof (opc));
   
    if (bind(sfd, res->ai_addr, res->ai_addrlen) != 0){
      perror("bind");
      exit(EXIT_FAILURE);
    }                 
  }while((res=res->ai_next)!=NULL);
  
  freeaddrinfo(res);
  listen(sfd,10);
  
  return sfd;
}

