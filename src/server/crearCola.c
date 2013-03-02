#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "headers/cola.h"

int crearCola()
{
	mqd_t cola;
	int prioridad = 1;		
	struct mq_attr atributos;
	atributos.mq_flags = 0;
	atributos.mq_msgsize = 100;
	atributos.mq_maxmsg = 10;

	mq_setattr (cola, &atributos, NULL);
	cola = mq_open ("/log", O_CREAT | O_RDWR, 0666, &atributos);	

	if (cola == -1)
	{
		perror ("mq_open()\n");
		return -1;
	}
	else
		return 0;
}



