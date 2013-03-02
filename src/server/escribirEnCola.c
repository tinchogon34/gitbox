#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include "headers/cola.h"

void escribirEnCola (char *mensaje)
{
	mqd_t cola;
	struct mq_attr atributos;
	int prioridad = 1;
	
	if ((cola = mq_open ("/log", O_RDWR, 0666, NULL)) == -1)
		perror ("mq_open()\n");
	else
	{
		mq_getattr (cola, &atributos);

		if ((strlen(mensaje)) <= atributos.mq_msgsize)
		{
			if ((mq_send (cola, mensaje, strlen(mensaje), prioridad)) == -1)
				perror ("mq_send()\n");
		}
	}	
}

