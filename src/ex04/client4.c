#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

/* definition des types */
#include "types4.h"

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */
  int envoyes;

  mon_type_t foo = 42;
  ma_structure_t bar;

  bar.a = 10;
  bar.b[0] = 'H';
  bar.b[1] = 'e';
  bar.b[2] = 'l';
  bar.b[3] = 'l';
  bar.b[4] = 'o';
  bar.b[5] = '\0';
  bar.c = 3.14;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
  }

  /* envoi des donnees */
  envoyes = send(desc_sock, &foo, sizeof(mon_type_t), 0);

  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
  }

  printf("Type simple envoye: %d\n", foo);

  /* envoi des donnees */
  envoyes = send(desc_sock, &bar, sizeof(ma_structure_t), 0);

  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
  }

  printf("Type complexe envoye:\n");
  printf("\ta = %d\n", bar.a);
  printf("\tb = %c %c %c %c %c\n", bar.b[0], bar.b[1], bar.b[2], bar.b[3], bar.b[4]);
  printf("\tc = %f\n", bar.c);

  close(desc_sock);

  return 0;
}
