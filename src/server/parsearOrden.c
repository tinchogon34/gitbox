#include "headers/orden.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

Orden parsearOrden (char *mensaje)
{
	Orden orden;
	int i = 0, j = 0;

	memset (orden.comando, 0, sizeof orden.comando);
	memset (orden.arg1, 0, sizeof orden.arg1);
	memset (orden.arg2, 0, sizeof orden.arg2);

	// Se separa el mensaje en orden y argumentos
	if (isalnum (mensaje[i]))
	{
		// Captura comando
		while (isalnum (mensaje[i]))
		{
			orden.comando[j] = mensaje[i];
			i++;
			j++;
		}

		i++;
		j=0;

		// Captura primer argumento
		if (isalnum (mensaje[i]))
		{
			while (isalnum (mensaje[i]))
			{
				orden.arg1[j] = mensaje[i];
				i++;
				j++;
			}

			i++;
			j=0;
			
			if (isalnum (mensaje[i]))
			{
				while (isalnum (mensaje[i]))
				{
					orden.arg2[j] = mensaje[i];
					i++;
					j++;
				}
			}
			else
				strcpy (orden.arg2, "NULL");			
		}
		else
			strcpy (orden.arg1, "NULL");
	}
	else
		strcpy (orden.comando, "NULL");

	return orden;
}

