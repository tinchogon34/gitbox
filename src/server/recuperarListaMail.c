#include <unistd.h>
#include "headers/mail.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include "headers/cliente.h"
#include <fcntl.h>
#include <stdlib.h>

Lista recuperarListaMail (Usuario usuario)
{
	char ruta[256];
	DIR *dir;
	struct dirent *ent;
	int fd;
	Lista lista = NULL;

	memset (ruta, 0, sizeof ruta);
	sprintf (ruta, "../maildir/%s", usuario.id);
	dir = opendir (ruta);
	
	if (dir == NULL)
		perror ("dir()\n");
	else
	{
		// Iterar el directorio
		while ((ent = readdir (dir)) != NULL)
		{
			// Verificar que la variable ent es un archivo
			if (isdigit (ent->d_name[0]))
			{
				Mail mail;
				sprintf (ruta, "../maildir/%s/%s", usuario.id, ent->d_name);
				fd = open (ruta, O_RDONLY);
				memset (ruta, 0, sizeof ruta);
				mail.size = (long) lseek (fd, 0, SEEK_END);
				strcpy (mail.id, ent->d_name);
				insertar (&lista, mail);
				close (fd);
			}
		}
		closedir (dir);
	}
	
	return lista;
}

void insertar (Lista *lista, Mail mail)
{
	pMail nuevo, auxiliar;

	// Creamos un nodo nuevo
	nuevo = (pMail)malloc(sizeof(Mail));

	if (nuevo != NULL)
	{
		strcpy(nuevo->id, mail.id);
		nuevo->size = mail.size;
		nuevo->siguiente = NULL;

		if (*lista == NULL)
			*lista = nuevo;
		else
		{
			auxiliar = *lista;
			
			while (auxiliar->siguiente != NULL)
				auxiliar = (Mail *)auxiliar->siguiente;

			auxiliar->siguiente = nuevo;			
		}	
	}
}

