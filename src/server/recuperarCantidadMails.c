#include <unistd.h>
#include "headers/mail.h"
#include "headers/cliente.h"
#include <stdio.h>

int recuperarCantidadMails (Lista lista)
{
	pMail mail = lista;
	int cantMails = 0;

	// Devuelve cantidad real, mails marcados y no marcados	
	while (mail != NULL)
	{
		cantMails++;
		mail = (Mail *)mail->siguiente;
	}

	return cantMails;
}

