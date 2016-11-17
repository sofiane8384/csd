#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

#define TAILLE_MAX 1024

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */

  int tab[TAILLE_MAX];
  
  int envoyes;

  int taille;
  int i;
  
  for(i = 0; i < TAILLE_MAX; ++i) {
    tab[i] = i;
  }
  taille = TAILLE_MAX;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  envoyes = send(desc_sock, &taille, sizeof(int), 0);

  if (envoyes == -1) {
    printf("Erreur a l'envoi\n");
    shutdown(desc_sock, 2);
    close(desc_sock);
    return 3;
  }

  envoyes = send(desc_sock, tab, TAILLE_MAX * sizeof(int), 0);

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
