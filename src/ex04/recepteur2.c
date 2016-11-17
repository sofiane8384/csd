#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  int desc_sock; /* descripteur de socket */
  char buf[20];
  int recus;

  desc_sock = socketUDP_EAD(2610);
  if (desc_sock < 0) {
    printf("Erreur %d a la creation socket\n", desc_sock);
  }

  /* reception des donnees */
  recus = recvfrom(desc_sock, buf, sizeof(buf), 0, NULL, NULL);

  if (recus == -1) {
    printf("Erreur a la reception\n");
  }

  printf("J'ai recu : %s\n", buf);
 
  close(desc_sock);


  return 0;
}
