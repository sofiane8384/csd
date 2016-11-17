#include <stdio.h>
#include <stdlib.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  /* Mettre le code de l'emetteur ici  */

   int descripteur_socket;
   int valeur  = 42;
   int envoyes;

   descripteur_socket = socketUDP_EAD(2610);

   if(descripteur_socket < 0){
      printf("Erreur %d a la creation de la socket emetteuse\n", descripteur_socket);
   }
    
   envoyes = sendto(descripteur_socket,&valeur,sizeof(int),0,socketAddr_EAD("localhost",2611),tailleAddr_EAD());

   if(envoyes == -1){
     printf("Erreur a l'envoi\n");
   }
   
  return 0;
}
