#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

#define NB 5

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */

  int tailles[NB];
  char* chaines[NB] = {
    "Ceci est la première chaîne !",
    "Mais attention, il y en a une deuxième...",
    "Et une troisième...",
    "Mais quand cela finira-t-il ?",
    "Peut-être après celle-ci, oui c'est certain !"
  };

  int envoyes;
  int recus;
  int i;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  for(i = 0; i < NB; ++i) {

    envoyes = send(desc_sock, chaines[i], strlen(chaines[i]) + 1, 0);

    if (envoyes == -1) {
      printf("Erreur a l'envoi\n");
      shutdown(desc_sock, 2);
      close(desc_sock);
      return 3;
    }

    /* On fait attendre le client pour que le serveur ne recoive pas
      tout en un seul morceau */
    sleep(1);
  }

  recus = recv(desc_sock, &tailles, NB * sizeof(int), 0);

  if (recus == -1) {
    printf("Erreur a la reception\n");
    shutdown(desc_sock, 2);
    close(desc_sock);
    return 4;
  }

  printf("Taille des chaines: %i %i %i %i %i\n", tailles[0], tailles[1], tailles[2], tailles[3], tailles[4]);
  
  shutdown(desc_sock, 2);
  close(desc_sock);

  return 0;
}
