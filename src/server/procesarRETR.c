#include <unistd.h>
#include "headers/cliente.h"
#include <stdio.h>
#include "headers/mail.h"
#include <string.h>
#include <fcntl.h>

void procesarRETR (int fd_cliente, Usuario usuario, char *argumento, Lista lista)
{
	pMail mail = lista;
	int cantMails = 0, escrito, fd, leido;
	char respuesta[256], buffer[256], ruta[256];

	memset (respuesta, 0, sizeof respuesta);
	memset (buffer, 0, sizeof buffer);
	memset (ruta, 0, sizeof ruta);
	
	while (mail != NULL)
	{
		if (mail->deleteFlag == 0)
			cantMails++;
		mail = (Mail *)mail->siguiente;
	}	

	if ((strcmp(argumento, "NULL")) != 0)
	{
		if (atoi(argumento) > recuperarCantidadMails(lista) || atoi(argumento) == 0)
			write (fd_cliente, "-ERR No existe mensaje\r\n", 24);
		else
		{
			cantMails = 1;
			mail = lista;
	
			while (cantMails != atoi(argumento))
			{
				cantMails++;
				mail = (Mail *)mail->siguiente;
			}

			if (mail->deleteFlag == 0)
			{		
				sprintf (ruta, "../maildir/%s/%s", usuario.id, mail->id);	
				if ((fd = open (ruta, O_RDONLY)) == -1)
					perror ("open()\n");
				else
				{
					write (fd_cliente, "+OK Mensaje:\r\n", 14);
					while ((leido = read (fd, buffer, sizeof buffer)) > 0)
					{
						write (fd_cliente, buffer, leido);
						memset (buffer, 0, sizeof buffer);
					}
					close (fd);
					write (fd_cliente, "\r\n.\r\n", 5);
				}
			}
			else if (mail->deleteFlag == 1)
			{
				escrito = sprintf (respuesta, "-ERR %d eliminado\r\n", cantMails);
				write (fd_cliente, respuesta, escrito);
			}
		}
	}
	else
		write (fd_cliente, "-ERR Indique numero Mensaje\r\n", 29);
}

