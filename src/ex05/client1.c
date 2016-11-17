#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */

  char buf[20];
  
  int envoyes;
  int recus;

  int taille;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  recus = recv(desc_sock, buf, sizeof(buf), 0);

  if (recus == -1) {
    printf("Erreur a la reception\n");
    shutdown(desc_sock, 2);
    close(desc_sock);
    return 2;
  }

  printf("J'ai recu : %s\n", buf);
  
  taille = strlen(buf);
  
  envoyes = send(desc_sock, &taille, sizeof(int), 0);
  
  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
    shutdown(desc_sock, 2);
    close(desc_sock);
    return 3;
  }
  
  shutdown(desc_sock, 2);
  close(desc_sock);

  return 0;
}
