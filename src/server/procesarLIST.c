#include <unistd.h>
#include "headers/cliente.h"
#include <stdio.h>
#include "headers/mail.h"
#include <string.h>

void procesarLIST (int fd_cliente, Usuario usuario, char *argumento, Lista lista)
{
	pMail mail = lista;	
	int cantMails = 0, escrito, contadorMails = 1;
	char respuesta[256];

	memset (respuesta, 0, sizeof respuesta);
		
	while (mail != NULL)
	{
		if (mail->deleteFlag == 0)
			cantMails++;
		mail = (Mail *)mail->siguiente;
	}
	
	// Si se envia argumento, el cliente esta solicitando 1 mail
	if ((strcmp(argumento, "NULL")) != 0)
	{
		if (atoi(argumento) > recuperarCantidadMails(lista) || atoi(argumento) == 0)
			write (fd_cliente, "-ERR No existe mensaje\r\n", 24);
		else
		{
			cantMails = 1;
			mail = lista;

			// Recuperamos el mail solicitado
			while (cantMails != atoi(argumento))
			{
				cantMails++;
				mail = (Mail *)mail->siguiente;
			}
		
			if (mail->deleteFlag == 0)	
				escrito = sprintf (respuesta, "+OK %d %lu\r\n", cantMails, mail->size);
			else if (mail->deleteFlag == 1)
				escrito = sprintf (respuesta, "-ERR %d eliminado\r\n", cantMails);

			write (fd_cliente, respuesta, escrito);
			memset (respuesta, 0, sizeof respuesta);
		}
	}
	else // Si la orden se envia sin argumento, mandamos todos los mails
	{
		mail = lista;
		escrito = sprintf (respuesta, "+OK %d Mensajes\r\n", cantMails);
		write (fd_cliente, respuesta, escrito);
		memset (respuesta, 0, sizeof respuesta);

		// Iteramos la lista de mails
		while (mail != NULL)
		{
			if (mail->deleteFlag == 0)
			{
				escrito = sprintf (respuesta, "%d %lu\r\n", contadorMails, mail->size);
				write (fd_cliente, respuesta, escrito);
			}
			contadorMails++;
			mail = (Mail *)mail->siguiente;
		}
		write (fd_cliente, ".\r\n", 3);
	}	
}

