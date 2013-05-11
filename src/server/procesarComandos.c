#include "headers/servidor.h"

int procesarComandos(char *comando, DatosUsuario *datosUsuario, DatosConfig *configuracion){
    
    if(strcmp(comando, "pull") == 0){
      int status = procesarComandoPull(datosUsuario, configuracion->backupPath);
      return status;
    }
    
    else if(strcmp(comando, "status") == 0){}
    
    return -1;
}