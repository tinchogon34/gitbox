#include <stdio.h>
#include <unistd.h>
#include "headers/cliente.h"
#include "headers/mail.h"
#include <string.h>

void procesarQUIT (int fd_cliente, Usuario usuario, Lista lista)
{
	if (strcmp(usuario.fase, "transaccion") == 0)
	{
		strcpy (usuario.fase, "actualizacion");
		pMail mail = lista;
		char ruta[256];
		memset (ruta, 0, sizeof ruta);
	
		// Borrar los mensajes marcados
		while (mail != NULL)
		{
			if (mail->deleteFlag == 1)
			{
				sprintf (ruta, "../maildir/%s/%s", usuario.id, mail->id);
				if ((unlink (ruta)) == -1)
					perror ("unlink()\n");
			}
			mail = (Mail *)mail->siguiente;
		}
		
		write (fd_cliente, "+OK Hasta Luego!\r\n", 18);
		close (fd_cliente);
	}
	else if (strcmp(usuario.fase, "autorizacion") == 0)
	{
		write (fd_cliente, "+OK Hasta Luego!\r\n", 18);
		close (fd_cliente);
	}
}

