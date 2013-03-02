#include <unistd.h>
#include "headers/cliente.h"
#include <stdio.h>
#include "headers/orden.h"

void procesarNOOP (int fd_cliente, Usuario usuario)
{
	write (fd_cliente, "+OK\r\n", 5);
}

