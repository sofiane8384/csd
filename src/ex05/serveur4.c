#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

#define TAILLE_MAX 256
#define NB 5

int main(int argc, char *argv[]) {

  /* descripteur de la socket de connexion */
  int desc_sock_conn;

  /* descripteur de la socket de transmission */
  int desc_sock_trans; 

  char buf[TAILLE_MAX];

  int recus;
  int envoyes;
  
  int tailles[NB];
  int i;

  desc_sock_conn = socketServeur_EAD(2609);
  if (desc_sock_conn < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  desc_sock_trans = accept(desc_sock_conn, NULL, NULL);
  if (desc_sock_trans == -1) {
    printf("Erreur connexion socket\n");
    close(desc_sock_conn);
    close(desc_sock_conn);
    return 2;
  }

  for(i = 0; i < 5; ++i) {
    recus = recv(desc_sock_trans, buf, sizeof(buf), 0);

    if (recus == -1) {
      printf("Erreur a la reception\n");
      shutdown(desc_sock_trans, 2);
      close(desc_sock_trans);
      close(desc_sock_conn);
      return 2;
    }

    printf("J'ai recu : %s\n", buf);
    
    tailles[i] = strlen(buf);
  }
  
  envoyes = send(desc_sock_trans, &tailles, NB * sizeof(int), 0);
  
  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
    shutdown(desc_sock_trans, 2);
    close(desc_sock_trans);
    close(desc_sock_conn);
    return 3;
  }
  

  shutdown(desc_sock_trans, 2);
  close(desc_sock_trans);
  close(desc_sock_conn);

  return 0;
}
