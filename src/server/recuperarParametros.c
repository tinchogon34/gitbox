#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "headers/config.h"
#include <fcntl.h>

int recuperarParametros(int argc, char * const argv[])
{
	int fd = 0, opcion = 0, i = 0;
	char puerto[5];

	/********INICIALIZAR*****/
	bzero(puerto,sizeof puerto);
	/************************/
	
	if ((opcion = getopt (argc, argv, "h")) != -1)
	{
		switch (opcion)
		{
			case 'h':
				printf ("Uso: %s\n", argv[0]);
				printf ("-h Muestra esta ayuda\n");
				printf ("Indique puerto de escucha en archivo: gitbox.cfg\n");
				return -1;
				break;
		}
	}
	else
	{
		return 3000;
	}
}


