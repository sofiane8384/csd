#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* taille du buffeur de reception */
#define TAIL_BUF 100


int main(int argc, char *argv[]) {
  int sock_cont;
  int sock_trans;
  int err; /* code d'erreur */

  struct sockaddr_in nom;	      /* adresse de la socket */

  char buffer[TAIL_BUF];	/* buffer de reception */

  /* Verification des arguments */
  if (argc != 2) {
    printf("Usage: serveur no_port\n");
    exit(1);
  }

  /* Creation de la socket, protocole TCP */
  sock_cont = socket(AF_INET, SOCK_STREAM, 0);

  if (sock_cont < 0) {
    perror("Erreur a la creation de la socket");
    exit(2);
  }

  /* Initialisation de l'adresse de la socket */
  nom.sin_family = AF_INET;
  nom.sin_port = htons(atoi(argv[1]));
  nom.sin_addr.s_addr = INADDR_ANY;
  memset(nom.sin_zero, 0, 8);

  /* Attribution de l'adresse a la socket */
  err = bind(sock_cont, (struct sockaddr *)&nom, sizeof(struct sockaddr_in));
  if (err < 0) {
    perror("Erreur sur le bind");
    exit(3);
  }

  /* Utilisation en socket de controle, puis attente de demandes de connexion. */
  err = listen(sock_cont, 1);
  if (err < 0) {
    perror("Erreur dans listen");
    exit(4);
  }

  /* Attente de connexion */
  sock_trans = accept(sock_cont, NULL, NULL);
  if (sock_trans < 0) {
    perror("Erreur sur accept");
    exit(5);
  }

  /* Reception et affichage du message en provenance du client */
  err = recv(sock_trans, buffer, TAIL_BUF, 0);
  if (err < 0) {
    perror("Erreur dans la reception");
    shutdown(sock_trans, 2);
    exit(6);
  }

  printf("serveur: voila le message recu: %s\n", buffer);
    
  /* arret de la connexion et fermeture */
  shutdown(sock_trans, 2);
  close(sock_cont);

  return 0;
}
