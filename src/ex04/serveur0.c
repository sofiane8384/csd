#include <stdio.h>
#include <stdlib.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  /* Mettre le code du serveur ici  */
  int communication_sock;

  int desc_sock = socketServeur_EAD(2612);
  
 communication_sock = accept(desck_sock,NULL,NULL);
 if(communication_sock == -1)
    {
      printf("Erreur connexion socket\n");
   }
  return 0;
}
