#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

#define TAILLE_MAX 256

int main(int argc, char *argv[]) {
  
  int desc_sock; /* descripteur de socket */

  char chaine[TAILLE_MAX];
  
  int envoyes;
  int recus;

  int taille;

  desc_sock = socketClient_EAD("localhost", 2609);
  if (desc_sock < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  for(;;) {
    
    printf("Donnez une chaine: ");
    scanf("%s", chaine);

    envoyes = send(desc_sock, chaine, strlen(chaine) + 1, 0);

    if (envoyes == -1) {
      printf("Erreur a l'envoi\n");
      shutdown(desc_sock, 2);
      close(desc_sock);
      return 3;
    }

    if (strcmp(chaine, "fin") == 0) {
      break;

    } else {
      recus = recv(desc_sock, &taille, sizeof(int), 0);

      if (recus == -1) {
        printf("Erreur a la reception\n");
        shutdown(desc_sock, 2);
        close(desc_sock);
        return 4;
      }

      printf("Taille de la chaine: %i\n", taille);
    }

  }

  shutdown(desc_sock, 2);
  close(desc_sock);

  return 0;
}
