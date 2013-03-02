#include "headers/servidor.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int iniciarServidor (char *puerto)
{
  int fd, opc = 1, sfd;
  struct addrinfo Direccion,*res;

  bzero(&Direccion,sizeof (struct addrinfo));
  Direccion.ai_family = AF_UNSPEC; 
  Direccion.ai_socktype= SOCK_STREAM; 
  Direccion.ai_flags = AI_PASSIVE; 

  if((getaddrinfo(NULL,puerto,&Direccion,&res))!=0){
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

