#ifndef _ORDEN_H_
	#define _ORDEN_H_

	#include "cliente.h"
	#include "mail.h"
	
	typedef struct ORDEN {
		char comando[10];
		char arg1[10];
		char arg2[10];
	} Orden;

	Orden parsearOrden (char *);
	int procesarUSER (int, char *, Usuario *);
	int procesarPASS (int, Usuario *, char *, int);
	void procesarLIST (int, Usuario, char *,  Lista);
	void procesarSTAT (int, Usuario, Lista);
	void procesarRETR (int, Usuario, char *, Lista);
	void procesarNOOP (int, Usuario);
	void procesarDELE (int, Usuario, char *, Lista);
	void procesarRSET (int, Usuario, Lista);
	void procesarQUIT (int, Usuario, Lista);

#endif	
