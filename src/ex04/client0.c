#include <stdio.h>
#include <stdlib.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  
  /* Mettre le code du client ici  */

   int desc_sock;
   char *chaine ="Hello World";
   int envoyes;

   desc_sock = socketClient_EAD("localhost", 2609);

   if(desc_sock < 0){
    printf("Erreur Creaction socket\n");
   }
   
   envoyes= send(desc_sock,chaine,12,0);
 
  if(envoyes ==-1 ) {
     printf("erreur e l'envoi\n");
  }

  close(desc_sock);

  return 0;
}
