#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "headers/log.h"

void escribirEnLog (char *mensaje)
{
	int fd;

	if ((fd = open ("logFile", O_RDWR)) == -1)
		perror ("open()\n");
	else
	{
		// Posiciona el cursor al final
		lseek(fd, 0, SEEK_END);

		// Escribe en el archivo
		write (fd, mensaje, strlen(mensaje));

		// Cierra el archivo
		close (fd);
	}	
}

