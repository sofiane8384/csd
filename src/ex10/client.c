#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  char chaine[100];
  int sock; /* descripteur de la socket locale */
  int err;  /* code d'erreur */


  /* Verification des arguments */
  if (argc != 3) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }

  sock = socketClient_EAD(argv[1], atoi(argv[2]));
  if (sock  < 0) {
    printf("client: erreur socketClient_EAD\n");
    exit(2);
  }
 
  /* Saisie de la chaine */
  printf("client: donner une chaine : ");
  scanf("%s", chaine );
  printf("client: envoi de \"%s\"\n", chaine);
 
  /* Envoi de la chaine */
  size_t len = strlen(chaine) + 1;
  err = send(sock, chaine, len, 0);
  if (err != len) {
    perror("client: erreur sur le send");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi realise\n");

  /* Fermeture de la connexion et de la socket */
  shutdown(sock, 2);
  close(sock);
  
  return 0;
}
