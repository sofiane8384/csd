#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

// include des fonctions
#include "fonctionsSocket.h"

/* taille du buffeur de reception */
#define LEN 100

int main(int argc, char *argv[]) {
  int sock_cont;
  int sock_trans1; /* descipteurs des sockets locales */
  int sock_trans2; /* descipteurs des sockets locales */
  int err; /* code d'erreur */

  char buffer[LEN]; /* buffer de reception */
  fd_set read_set; /* ens de desc pour select */

  /* Verification des arguments */
  if (argc != 2) {
    printf("usage : serveur no_port\n");
    exit(1);
  }

  sock_cont = socketServeur_EAD(atoi(argv[1]));
  if (sock_cont < 0) {
    printf("serveurSelect: erreur socketServeur_EAD\n");
    exit(2);
  }

  /* Attente des connexions */
  sock_trans1 = accept(sock_cont, NULL, NULL);
  if (sock_trans1 < 0) {
    perror("serveurSelect:  erreur sur accept 1");
    exit(3);
  }

  sock_trans2 = accept(sock_cont, NULL, NULL);
  if (sock_trans2 < 0) {
    perror("serveurSelect :  erreur sur accept 2");
    exit(4);
  }

  FD_ZERO(&read_set);

  FD_SET(sock_trans1, &read_set);
  FD_SET(sock_trans2, &read_set);

  printf("serveurSelect : avant le select\n");

  err = select(FD_SETSIZE, &read_set, NULL, NULL, NULL);
  if (err<0) {
    perror("serveurSelect : erreur dans select");
    exit(5);
  }

  if (FD_ISSET(sock_trans1, &read_set) != 0) {
    /* Reception du message */
    err = recv(sock_trans1, buffer, LEN, 0);
    if (err < 0) {
      perror("serveurSelect : Erreur dans le recv 1");
      exit(6);
    }
  } else if (FD_ISSET(sock_trans2, &read_set) != 0) {
    /* Reception du message */
    err = recv(sock_trans2, buffer, LEN, 0);
    if (err < 0) {
      perror("serveurSelect : Erreur dans le recv 2");
      exit(7);
    }
  }

  /* Affichage de la chaine */
  printf("serveur : voila le message recu: \"%s\"\n", buffer);

  /* Arret de la connexion et fermeture */
  shutdown(sock_trans1, 2);
  shutdown(sock_trans2, 2);
  close(sock_trans1);
  close(sock_trans2);
  close(sock_cont);

  return 0;
}
