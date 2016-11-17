#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "fonctionsSocket.h"

#define LEN 100

int main(int argc, char *argv[]) {
  int sock; /* descipteur de socket locale */
  int err;  /* code d'erreur */

  char buffer[LEN]; /* buffer de reception */

  if (argc != 2) {
    printf("Usage : %s no_port\n", argv[0]);
    exit(1);
  }

  /* Creation de la socket, protocole UDP */
  sock = socketUDP_EAD(atoi(argv[1]));
  if (sock < 0) {
    printf("serveur : erreur socketUDP\n");
    exit(2);
  }

  /* Reception et affichage du message en provenance du client */
  err = recvfrom(sock, buffer, LEN, 0, NULL, NULL);
  if (err < 0) {
    perror("Erreur dans la reception");
    exit(6);
  }
  printf("Voila le premier message recu: \"%s\"\n", buffer);

  /* Reception et affichage du message en provenance du client */
  /* Reception et affichage du message en provenance du client */
  err = recvfrom(sock, buffer, LEN, 0, NULL, NULL);
  if (err < 0) {
    perror("Erreur dans la reception");
    exit(6);
  }
  printf("Voila le deuxieme message recu: \"%s\"\n", buffer);

  /* Fermeture de la socket */
  close(sock);

  return 0;
}
