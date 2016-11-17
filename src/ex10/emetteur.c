#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  int sock; /* descripteur de la socket locale */
  int port; /* variables de lecture */
  int err;  /* code d'erreur */

  char chaine[100];
  char nom[100]; /* nom de la machine dest */
  struct sockaddr *addr;

  if (argc != 2) {
    printf("usage : %s no_port\n", argv[0]);
    exit(1);
  }

  sock = socketUDP_EAD(atoi(argv[1]));
  if (sock < 0) {
    printf("client: erreur %d de socketUDP_EAD\n", sock);
    exit(2);
  }
 
  /* Saisie et initialisation de l'adresse du destinataire */
  printf("client: donner la machine dest : ");
  scanf("%s", nom);
  printf("client: donner le port dest : ");
  scanf("%d", &port);
  printf("client: initaddr pour %s, %d\n",  nom, port);
  addr = socketAddr_EAD(nom, port);
  if (addr == NULL) {
    printf("client: erreur adresse\n");
    exit(3);
  }

  /* Saisie et envoi de la chaine */
  printf("client: donner la chaine : ");
  scanf("%s", chaine );
  printf("client: envoi de \"%s\"\n", chaine);

  size_t len = strlen(chaine) + 1;
  err = sendto(sock, chaine, len, 0, addr, sizeof(struct sockaddr_in));
  if (err != len) {
    perror("client: erreur sur le send");
    exit(4);
  }

  printf("client : chaine envoyee\n");

  /* Fermeture de la socket */
  close(sock);
  
  return 0;
}
 

