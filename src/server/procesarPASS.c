#include "headers/orden.h"
#include "headers/cliente.h"
#include <unistd.h>
#include <string.h>

int procesarPASS (int fd_cliente, Usuario *user, char *password, int flag)
{	
	if (strcmp(password, "NULL"))
	{	
		if (flag==0)
		{
			if((strcmp(user->password, password))==0)
			{
				write (fd_cliente, "+OK Bienvenido!\r\n", 17 );
				strcpy (user->fase, "transaccion");
				return 0;
			}
			else
			{
				write(fd_cliente, "-ERR Password Incorrecto\r\n", 26);
				return -1;
			}
		}
	}
	else
	{
		write (fd_cliente, "-ERR Ingrese password seguido de orden PASS\r\n", 45);
		return -1;
	}
}

