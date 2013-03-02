#include <unistd.h>
#include "headers/cliente.h"
#include "headers/mail.h"
#include <stdio.h>
#include <string.h>

void procesarDELE (int fd_cliente, Usuario usuario, char *argumento, Lista lista)
{
	pMail mail = lista;
	int cantMails, escrito;
	char respuesta[256];

	memset (respuesta, 0, sizeof respuesta);

	cantMails = recuperarCantidadMails(lista);

	if ((strcmp(argumento, "NULL")) != 0)
	{
		if (atoi(argumento) > cantMails || atoi(argumento) == 0)
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
			
			// Se marca el mensaje para borrar
			if (mail->deleteFlag == 0)
			{
				mail->deleteFlag = 1;
				escrito = sprintf (respuesta, "+OK Mensaje %d eliminado\r\n", cantMails);
			}
			else
				escrito = sprintf (respuesta, "-ERR %d eliminado\r\n", cantMails);
			
			write (fd_cliente, respuesta, escrito);
		}
	}
	else
		write (fd_cliente, "-ERR Indique numero Mensaje\r\n", 29);
}

