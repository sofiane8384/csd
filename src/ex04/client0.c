#include <stdio.h>
#include <stdlib.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  
  /* Mettre le code du client ici  */

   int desc_sock;
   desc_sock = socketClient_EAD("localhost",2612);

   if(desc_sock <0){
    printf("Erreur Creaction socket\n");
  }

  return 0;
}
