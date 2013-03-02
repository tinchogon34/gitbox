#ifndef _MAIL_H_
	#define _MAIL_H_

	typedef struct MAIL {
		char id[10];
		long size;
		int deleteFlag;
		struct Mail *siguiente;
	} Mail;

	typedef Mail *pMail;
	typedef Mail *Lista;

	Lista recuperarListaMail(Usuario);
	int recuperarCantidadMails(Lista);
	void insertar(Lista *, Mail);

#endif	
