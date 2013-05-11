#ifndef _CLIENTE_H_
  #define _CLIENTE_H_

  #include <string.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <errno.h>
  #include <semaphore.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <signal.h>
  #include <sys/socket.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <netdb.h>
  #include <pthread.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>

  int generarMontaje();

#endif
