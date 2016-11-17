#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  int desc_sock; /* descripteur de socket */
  char *chaine = "Hello world";
  int envoyes;

  desc_sock = socketUDP_EAD(2609);
  if (desc_sock < 0) {
    printf("Erreur %d a la creation socket\n", desc_sock);
  }

  /* envoi des donnees */
  envoyes = sendto(desc_sock, chaine, 12, 0,
    socketAddr_EAD("localhost", 2610), tailleAddr_EAD());
  
  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
  }

  close(desc_sock);

  return 0;
}
