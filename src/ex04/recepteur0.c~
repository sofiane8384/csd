#include <stdio.h>
#include <stdlib.h>
#include "fonctionsCommunication.h"

int main(int argc, char *argv[]) {

  /* Mettre le code du recepteur ici  */

  int descripteur_socket;
  int val;
  int recus;
  descripteur_socket = socketUDP_EAD(2611);

   if(descripteur_socket < 0){
      printf("Erreur %d a la creation de la socket receptrice\n", descripteur_socket);
}
    

  recus = recvfrom(descripteur_socket,&val,sizeof(int),0,NULL,NULL);

  printf("J'ai recu la valeur : %d\n",val);

  close(descripteur_socket);

  return 0;
}
