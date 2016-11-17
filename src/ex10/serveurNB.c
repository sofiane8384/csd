#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/ioctl.h>

#include "fonctionsSocket.h"

/* taille du buffeur de reception */
#define LEN 100

int main(int argc, char *argv[]) {
  int sock_cont;
  int sock_trans1; /* descipteurs des sockets */
  int sock_trans2; /*   locales */
  int recu; /* pour savoir si on a recu */
  int on; /* position non bloquante */
  int err; /* code d'erreur */

  char buffer[LEN]; /* buffer de reception */

  /* Verification des arguments */
  if (argc != 2) {
    printf("Usage: serveurNB no_port\n");
    exit(1);
  }

  sock_cont = socketServeur_EAD(atoi(argv[1]));
  if (sock_cont < 0) {
    printf("serveurNB: erreur socketServeur_EAD\n" );
    exit(2);
  }

  /* Attente de deux connexions */
  sock_trans1 = accept(sock_cont, NULL, NULL);
  if (sock_trans1 < 0) {
    perror("serveurNB:  erreur sur accept 1");
    exit(3);
  }

  sock_trans2 = accept(sock_cont, NULL, NULL);
  if (sock_trans1 < 0) {
    perror("serveurNB:  erreur sur accept 2");
    exit(4);
  }

  /* Les sockets sont rendues non bloquantes */
  on = 1;

  err = ioctl(sock_trans1, FIONBIO, &on);
  if (err < 0) {
    perror("serveurNB: erreur ioctl 1");
    exit(5);
  }

  err = ioctl( sock_trans2, FIONBIO, &on);
  if (err < 0) {
    perror("serveurNB: erreur ioctl 2");
    exit(6);
  }

  printf("serveurNB: serveur pret\n");

  /* Attente de la reception */
  recu = 0;
  while (recu == 0) {
    /* Reception et affichage du premier message en provenance du client */
    err = recv(sock_trans1, buffer, LEN, 0);
    if (err > 0) {
      perror("serveurNB");
      recu = 1;
      break;
    } else if ((err < 0) && (errno != EWOULDBLOCK)) {
      perror("serveurNB: erreur dans la reception 1");
      shutdown(sock_trans1, 2);
      exit(7);
    }

    /* Reception et affichage du deuxieme message en provenance du client */
    err = recv(sock_trans2, buffer, LEN, 0);
    if (err > 0) {
      recu = 1;
      break;
    } else if ((err < 0) && (errno != EWOULDBLOCK)) {
      perror("serveurNB: erreur dans la reception 2");
      shutdown(sock_trans2, 2);
      exit(8);
    }
  }

  printf("serveurNB: voila le message recu: \"%s\"\n", buffer);

  /* Arret de la connexion et fermeture des sockets */
  shutdown(sock_trans1, 2);
  shutdown(sock_trans2, 2);
  close(sock_trans1);
  close(sock_trans2);
  close(sock_cont);

  return 0;
}
