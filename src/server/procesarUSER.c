#include "headers/orden.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "headers/cliente.h"
#include <fcntl.h>

int procesarUSER (int fd_cliente, char *nombreUsuario, Usuario *usuario)
{
	int fd_archivo, i = 0, j = 0, usuarioEncontrado = 0;
	char *linea, contenido[256], user[20], pass[20], logStatus[20];
	
	memset (contenido, 0, sizeof contenido);
	memset (user, 0, sizeof user);
	memset (pass, 0, sizeof pass);
	memset (logStatus, 0, sizeof logStatus);
		
	// Verificar si se ingreso un argumento despues de USER
	if ((strcmp (nombreUsuario, "NULL")) == 0)
		write (fd_cliente, "-ERR Ingrese usuario seguido de orden USER\r\n", 44);
	else
	{
		if ((fd_archivo = open ("usuarios", O_RDONLY)) < 0)
			perror ("Open(): \n");
		else
		{
			// Leer todo el contenido del archivo
			read (fd_archivo, contenido, sizeof contenido);
			close (fd_archivo);

			// Leemos linea por linea hasta el fin del archivo
			linea = strtok (contenido, "\n");

			while (linea != NULL)
			{
				i=0;
				j=0;

				while (linea[i] != ':')
				{
					user[j] = linea[i];
					i++;
					j++;
				}

				i++;
				j=0;
				
				while (isalnum(linea[i]))
				{
					pass[j] = linea[i];
					i++;
					j++;
				}

				i++;
				j=0;

				while (isalnum(linea[i]))
				{
					logStatus[j] = linea[i];
					i++;
					j++;
				}

				// Verificar si existe el usuario
				if ((strcmp (user, nombreUsuario)) == 0)
				{
					write (fd_cliente, "+OK Ingrese pass\r\n", 18);
					strcpy (usuario->id, user);
					strcpy (usuario->password, pass);
					usuarioEncontrado = 1;

					// Guardar tipo de Log
					if (strcmp(logStatus, "simple"))
						usuario->logStatus = 1;
					else if (strcmp(logStatus, "full"))
						usuario->logStatus = 2;
				}

				linea = strtok (NULL, "\n");
			}
			
			if (usuarioEncontrado == 0)
			{
				write (fd_cliente, "-ERR Usuario no encontrado\n", 27);
				return -1;
			}
			else
				return 0;
		}
	}

	return -1;
}
