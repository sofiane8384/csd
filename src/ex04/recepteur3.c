#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fonctionsSocket.h"

#define LEN 10


int main(int argc, char *argv[]) {

  int desc_sock; /* descripteur de socket */
  int array[LEN];
  int recus;
  int i;

  /* mise a zero */
  memset(array, 0, LEN * sizeof(int));

  desc_sock = socketUDP_EAD(2610);
  if (desc_sock < 0) {
    printf("Erreur %d a la creation socket\n", desc_sock);
  }

  /* reception des donnees */
  recus = recvfrom(desc_sock, array, LEN * sizeof(int), 0, NULL, NULL);

  if (recus == -1) {
    printf("Erreur a la reception\n");
  }

  printf("J'ai recu les valeurs :\n");
  for(i = 0; i < LEN; ++i) {
    printf("\t%d\n", array[i]);
  }
 
  close(desc_sock);


  return 0;
}
