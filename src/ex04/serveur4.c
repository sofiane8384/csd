#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fonctionsSocket.h"

/* definition des types */
#include "types4.h"

int main(int argc, char *argv[]) {

  /* descripteur de la socket de connexion */
  int desc_sock_conn;

  /* descripteur de la socket de transmission */
  int desc_sock_trans; 
  int recus;

  mon_type_t foo = 0;
  ma_structure_t bar;
  memset(&bar, 0, sizeof(ma_structure_t));
  
  desc_sock_conn = socketServeur_EAD(2609);
  if (desc_sock_conn < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  desc_sock_trans = accept(desc_sock_conn, NULL, NULL);
  if (desc_sock_trans == -1) {
    printf("Erreur connexion socket\n");
    return 2;
  }

  /* reception des donnees */
  recus = recv(desc_sock_trans, &foo, sizeof(mon_type_t), 0);

  if (recus == -1) {
    printf("Erreur a la reception\n");
  }

  printf("Type simple recu: %d\n", foo);

  /* reception des donnees */
  recus = recv(desc_sock_trans, &bar, sizeof(ma_structure_t), 0);

  if (recus == -1) {
    printf("Erreur a la reception\n");
  }

  printf("Type complexe recu:\n");
  printf("\ta = %d\n", bar.a);
  printf("\tb = %c %c %c %c %c\n", bar.b[0], bar.b[1], bar.b[2], bar.b[3], bar.b[4]);
  printf("\tc = %f\n", bar.c);

  close(desc_sock_trans);

  return 0;
}
