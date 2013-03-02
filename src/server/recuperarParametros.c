#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "headers/config.h"
#include <fcntl.h>

int recuperarParametros(int argc, char * const argv[])
{
	int fd, opcion, i=0, j=0;
	char buffer[100];
	char puerto[10];
	memset (puerto, 0, sizeof puerto);
	memset (buffer, 0, sizeof buffer);
	
	if ((opcion = getopt (argc, argv, "h")) != -1)
	{
		switch (opcion)
		{
			case 'h':
				printf ("Uso: %s\n", argv[0]);
				printf ("-h Muestra esta ayuda\n");
				printf ("Indique puerto de escucha en archivo: pop3server.conf\n");
				return -1;
				break;
		}
	}
	else
	{
		/* Puerto=3000
		// Abre el archivo de configuracion y recupera puerto y maildir
		if ((fd = open ("pop3server.conf", O_RDONLY)) > 0)
		{
			read (fd, buffer, sizeof buffer);
			close (fd);
	
			for (i=0; buffer[i] != '\n'; i++)
			{
				if (isdigit(buffer[i]))
				{
					puerto[j] = buffer[i];
					j++;
				}
			}
	*/
		return 3000;

	}
}


