#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  /* descripteur de la socket de connexion */
  int desc_sock_conn;

  /* descripteur de la socket de transmission */
  int desc_sock_trans; 

  int val;
  int recus;

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
  recus = recv(desc_sock_trans, &val, sizeof(int), 0);

  if (recus == -1) {
    printf("Erreur a la reception\n");
  }

  printf("J'ai recu : %d\n", val);
  close(desc_sock_trans);

  return 0;
}
