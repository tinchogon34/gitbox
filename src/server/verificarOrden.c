#include <stdio.h>
#include <string.h>

int verificarOrden (char *orden)
{
	if ((strcmp(orden, "USER")) == 0 || (strcmp(orden, "user")) == 0)
		return 0;
	else if ((strcmp(orden, "PASS")) == 0 || (strcmp(orden, "pass")) == 0)
		return 1;
	else if ((strcmp(orden, "LIST")) == 0 || (strcmp(orden, "list")) == 0)
		return 2;
	else if ((strcmp(orden, "STAT")) == 0 || (strcmp(orden, "stat")) == 0)
		return 3;
	else if ((strcmp(orden, "RETR")) == 0 || (strcmp(orden, "retr")) == 0)
		return 4;
	else if ((strcmp(orden, "DELE")) == 0 || (strcmp(orden, "dele")) == 0)
		return 5;
	else if ((strcmp(orden, "NOOP")) == 0 || (strcmp(orden, "noop")) == 0)
		return 6;
	else if ((strcmp(orden, "RSET")) == 0 || (strcmp(orden, "rset")) == 0)
		return 7;
	else if ((strcmp(orden, "QUIT")) == 0 || (strcmp(orden, "quit")) == 0)
		return 8;
	else
		return -1;
}
