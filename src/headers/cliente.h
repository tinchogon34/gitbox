#ifndef _CLIENTE_H_
	#define _CLIENTE_H_

	#include <sys/socket.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <netdb.h>
	#include <pthread.h>

	typedef struct USUARIO {
		char fase[20];
		char id[20];
		char password[20];
		int logStatus;
	} Usuario;

	void * atenderCliente (void *);	

#endif
