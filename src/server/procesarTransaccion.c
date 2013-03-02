#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "headers/cliente.h"
#include "headers/orden.h"
#include <stdlib.h>

char *procesarTransaccion (char *usuario, char *orden)
{
	char *transaccion = (char *)malloc (sizeof(char) * 100);
	memset (transaccion, 0, sizeof transaccion);

	sprintf (transaccion, "User: %s;Cmd: %s;Time: %s", 
		(char *)usuario, (char *)orden, (char *)recuperarFecha());

	return transaccion;
}

