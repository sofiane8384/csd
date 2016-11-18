#include <stdio.h>
#include <stdlib.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  /* Mettre le code du serveur ici  */
  int communication_sock;
  int desc_sock ;

 int valeur[4];
 int recus;

 desc_sock=socketServeur_EAD(2609);

if(desc_sock < 0)
    {
      printf("Erreur creation socket\n");
     return 1;
  }
  
  
 communication_sock = accept(desc_sock,NULL,NULL);

 if(communication_sock == -1)
    {
      printf("Erreur connexion socket\n");
     return 2;
  }
  
 recus = recv(communication_sock,valeur,4 * sizeof(int),0);
 
 if(recus == -1){
     printf("Erreur a la reception\n");
   return 1;
 }

 int i = 0;
 for(i=0;i<4;i++)
  {
   printf("%d\n",valeur[i]);
  }

 //printf("j'ai recu un tableau de : %d valeur\n", sizeof(&valeur));

 close(desc_sock);
 
  return 0;
}
