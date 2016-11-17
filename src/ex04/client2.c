#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */
  int val = 42;
  int envoyes;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
  }

  /* envoi des donnees */
  envoyes = send(desc_sock, &val, sizeof(int), 0);

  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
  }

  close(desc_sock);

  return 0;
}
