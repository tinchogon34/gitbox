#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "headers/config.h"

#include <fcntl.h>

int recuperarParametros(int argc, char * const argv[], DatosConfig *configuracion)
{
	int fd = 0, opcion = 0, i = 0, popt = 0;
	char puerto[5], buffer[512];
	char *pvalue, *token, *token2, *save1, *save2;

	/********INICIALIZAR*****/
	memset(puerto,0,sizeof puerto);
	memset(buffer,0,sizeof buffer);
	/************************/
	
	while((opcion = getopt (argc, argv, "hp:")) != -1){
		switch(opcion){
			case 'p':
				popt = 1;
				pvalue = optarg;
				break;
			case 'h':
			default:
				printf ("Uso: %s\n", argv[0]);
				printf ("-h Muestra esta ayuda\n");
				printf ("-p XX Sobreescribe el puerto de escucha\n");
				printf ("Indique puerto de escucha por defecto en archivo: gitbox.cfg\n");
				exit(EXIT_FAILURE);
		}
	}
	/*******SI EXISTE PARAMETRO -P RECUPERAR EL PUERTO*******/ 
	if(popt){
		strncpy(puerto,pvalue,sizeof puerto);
	}

	/********LEER ARCHIVO DE CONFIGURACION***********/	 	
	if ((fd = open ("server.cfg", O_RDONLY)) < 0)
	{
		perror("open:");
		return -1;
	}

	read(fd, buffer, sizeof buffer);
	close(fd);


	if((token = strtok_r(buffer,"\n",&save1)) == NULL){
    write(1,"Error archivo de configuracion\n",31);
    return -1;
	}

	strtok_r(token,"=",&save2);
	token2 = strtok_r(NULL,"=",&save2);

	if(!popt){
		strncpy(puerto, token2, sizeof puerto);
	}

	token = strtok_r(NULL,"\n",&save1);
	strtok_r(token,"=",&save2);
	token2 = strtok_r(NULL,"=",&save2);

	strncpy(configuracion->backupPath, token2, strlen(token2));
	configuracion->puerto = atoi(puerto);
	return 0;
	
}


