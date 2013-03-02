#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "headers/mail.h"
#include "headers/cliente.h"

void procesarRSET (int fd_cliente, Usuario usuario, Lista lista)
{
	pMail mail = lista;
	int cantMails = 0, escrito;
	char respuesta[256];

	memset (respuesta, 0, sizeof respuesta);
	
	while (mail != NULL)
	{
		mail->deleteFlag = 0;
		mail = (Mail *)mail->siguiente;
		cantMails++;
	}

	escrito = sprintf (respuesta, "+OK %d Mensajes en Total\r\n", cantMails);
	write (fd_cliente, respuesta, escrito);
}

