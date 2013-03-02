#include "headers/cliente.h"
#include "headers/orden.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "headers/mail.h"
#include "headers/cola.h"
#include <pthread.h>

int clientesConectados = 0;
pthread_mutex_t mute = PTHREAD_MUTEX_INITIALIZER;

void* atenderCliente(void *fd)
{	
	int fd_cliente = (int)(int*)fd;
	char mensaje[256];
	int bytesLeidos, valor, flag;
	Orden orden;
	Usuario usuario;
	Lista lista = NULL;

	memset(usuario.id, 0, sizeof usuario.id);
	memset(mensaje, 0, sizeof mensaje);
	memset(orden.comando, 0, sizeof orden.comando);
	memset(orden.arg1, 0, sizeof orden.arg1);
	memset(orden.arg2, 0, sizeof orden.arg2);
	
	if((write(fd_cliente,"+OK Servidor POP Listo!\n", 24))==-1){

		perror("Write: \n");
		pthread_exit(NULL);
		return NULL;
	}
	else
	{
		// El usuario esta en fase de autorizacion
		strcpy (usuario.fase, "autorizacion");

		// Se incrementa la cantidad de clientes conectados
		pthread_mutex_lock (&mute);
		clientesConectados++;
		pthread_mutex_unlock (&mute);	
		printf ("Clientes Conectados: %d\n", clientesConectados);
	}

	while((bytesLeidos = read (fd_cliente, mensaje, sizeof mensaje)) > 0)
	{
		write (1, mensaje, bytesLeidos);
		orden = parsearOrden(mensaje);

		int valor = verificarOrden (orden.comando);

		memset (orden.comando, 0, sizeof orden.comando);
	
		switch (valor)
		{
			case 0:
				flag = procesarUSER (fd_cliente, orden.arg1, &usuario);
				escribirEnCola((char *)procesarTransaccion(usuario.id, "user"));
				break;
			case 1:
				if ((procesarPASS (fd_cliente, &usuario, orden.arg1, flag)) == 0)
				{
					lista = recuperarListaMail(usuario);
					escribirEnCola((char *)procesarTransaccion(usuario.id, "pass"));
				}
				break;
			case 2:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{
					procesarLIST (fd_cliente, usuario, orden.arg1, lista);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "list"));
				}	
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 3:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{	
					procesarSTAT (fd_cliente, usuario, lista);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "stat"));
				}	
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 4:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{
					procesarRETR (fd_cliente, usuario, orden.arg1, lista);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "retr"));
				}
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 5:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{
					procesarDELE (fd_cliente, usuario, orden.arg1, lista);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "dele"));
				}
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 6:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{
					procesarNOOP (fd_cliente, usuario);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "noop"));
				}
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 7:
				if (strcmp(usuario.fase, "transaccion") == 0)
				{
					procesarRSET (fd_cliente, usuario, lista);
					if (usuario.logStatus == 1)
						escribirEnCola((char *)procesarTransaccion(usuario.id, "rset"));
				}
				else
					write (fd_cliente, "-ERR Inicie sesion\r\n", 20);
				break;
			case 8:
				procesarQUIT (fd_cliente, usuario, lista);
				escribirEnCola((char *)procesarTransaccion(usuario.id, "quit"));
				// Se decrementa la cantidad de clientes conectados
				pthread_mutex_lock (&mute);
				clientesConectados--;
				pthread_mutex_unlock (&mute);
				printf ("Clientes Conectados: %d\n", clientesConectados);
				pthread_exit(NULL);
				return NULL;
				break;
			default:		
				write(fd_cliente, "-ERR Orden Invalida \r\n", 22);
				memset (orden.arg1, 0, sizeof orden.arg1);

		}
	}	
}

