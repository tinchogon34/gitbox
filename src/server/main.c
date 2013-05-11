#include "headers/servidor.h"
#include "headers/config.h"

#define CANT_HIJOS 1

int main (int argc, char * const argv[])
{
	int fd = 0, fd_cliente = 0, longitud_cliente = 0, puerto = 0, 
	cpid = 0, i = 0, file_fd = 0;
	off_t fileSize;
	unsigned long long fileSizeL;
	struct sockaddr cliente;
	DatosConfig configuracion; 
	pthread_t tid;
	char * dbUsuarios;

	/********INICIALIZAR*****/
	memset(&cliente,0, sizeof (struct sockaddr));
  /************************/
 
 	/*************** CARGAR TODO EL ARCHIVO DE USUARIOS EN DB **************/
	if ((file_fd = open ("user_config.cfg", O_RDONLY)) < 0)
	{
		perror("open:");
		return -1;
	}

	fileSize = lseek(file_fd , 0L , SEEK_END);
	lseek(file_fd,0L, SEEK_SET);
	fileSizeL=(unsigned long long) fileSize;

	dbUsuarios = (char *) malloc(sizeof(char) * (fileSizeL+1) );

	read (file_fd, dbUsuarios, fileSizeL+1); //Este +1 que ondita??
	configuracion.dbUsuarios = dbUsuarios;
	/**********************************************************************/

//**********Todo el archivo de usuarios queda en dbUsuarios*******************/

	//strncpy(configuracion.backupPath,"backups/",strlen("backups/"));
	

	// Recuperar argumentos de configuracion y tratar argumentos de ayuda
	if (recuperarParametros(argc, argv, &configuracion) != 0)
		return -1;


	// Iniciar servidor con el puerto indicado
	fd = iniciarServidor(configuracion.puerto);

	/* Preforkear un par */
	for (i = 0; i < CANT_HIJOS; i++) {
		cpid = fork();
		if (cpid == -1) {
			die("No se pudo forkear");
		}

		if (cpid == 0) { // Si estamos en el hijo
			for (;;) {

				longitud_cliente = sizeof cliente;

				fd_cliente = accept(fd, &cliente, &longitud_cliente);

				if (fd_cliente == -1) {
					die("No se pudo aceptar la conexion");
				}

				/*****Codigo importante del hijo*********/
				atenderCliente(fd_cliente, &configuracion);
				
				/* Cerrar el socket */
				if(close(fd_cliente) == -1){
					die("No se pudo cerrar el socket");
				}
				
	    	/****************************************/
			}
		}
	}

	 /* El padre espera a todos los hijos antes de cerrarse */
	while (waitpid(-1, NULL, 0) > 0);

   /* Cerrar el socket una vez que todos los hijos terminaron */
	close(fd);

	return 0;
}


