#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char * const argv[])
{
	mqd_t cola;
	struct mq_attr atributos;
	int prioridad = 1;
	char buffer[100];

	memset (buffer, 0, sizeof buffer);

	// Abre la cola de mensajes para leer
	if ((cola = mq_open ("/log", O_RDONLY, 0666, NULL)) == -1)
	{
		perror ("mq_open()\n");
		return -1;
	}
	else
	{
		// Recupera los atributos de la cola
		mq_getattr (cola, &atributos);
		
		while ((mq_receive (cola, buffer, atributos.mq_msgsize, &prioridad)) > 0)
		{
			// Escribe cada transaccion en el Log
			escribirEnLog(buffer);
			memset (buffer, 0, sizeof buffer);
		}
	}

	return 0;
}

