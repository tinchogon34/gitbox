#include <stdio.h>
#include <unistd.h>
#include "headers/cliente.h"
#include "headers/mail.h"
#include <stdio.h>
#include <string.h>

void procesarSTAT (int fd_cliente, Usuario usuario, Lista lista)
{
	int escrito, cantMails = 0;
	char respuesta[256];
	int size;
	unsigned long int cantBytes = 0;
	
	memset (respuesta, 0, sizeof respuesta);

	pMail mail = lista;

	while (mail != NULL)
	{
		if (mail->deleteFlag == 0)
		{
			cantMails++;
			size = mail->size;
			cantBytes = cantBytes + (int)size;		
		}
		mail = (Mail *)mail->siguiente;
	}

	escrito = sprintf(respuesta, "+OK %d %lu\r\n", cantMails, cantBytes);
	write(fd_cliente, respuesta, escrito);
}

