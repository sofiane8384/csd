/**
 * @author Laurent Philippe, Julien Bernard
 * @date 25 Jun 2006, modified 12 Jul 2010
 */

#include "fonctionsCommunication.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fonctionsSocket.h"

static int sock_conn = -1;
static int sock_trans = -1;

static const char *Host = "localhost";
static const unsigned short Port = 2609;

static enum { YES, NO } connected = NO;


char *recevoir(void) {
  int err;      /* code d'erreur systeme */
  size_t taille;   /* taille des donnees recues dans la socket */
  char* chaine; /* adresse de la chaine de caractere recue */

  struct sockaddr_in addr;
  socklen_t size_addr;

  if (connected == NO) {
    sock_conn = socketServeur_EAD(Port);

    /* En cas d'erreur on arrete le programme */
    if (sock_conn < 0 ) {
      perror("recevoir: ne peut creer un serveur");
      exit(-1);
    }

    /*
     * Attente de connexion
     */
    size_addr = sizeof(struct sockaddr_in);
    sock_trans = accept(sock_conn, (struct sockaddr *)&addr, &size_addr);
    if (sock_trans < 0) {
      perror("recevoir: erreur sur accept");
      exit(-2);
    }

    connected = YES;
  }
  
  err = recv(sock_trans, &taille, sizeof(size_t), 0);
  if (err < 0) {
    perror("recevoir: erreur de reception de la taille");
    exit(-3);
  }  

  /* allocation de la memoire */
  chaine = malloc(taille);
  if (chaine == NULL) {
    perror("recevoir: erreur malloc");
    exit(-4);
  }

  err = recv(sock_trans, chaine, taille, 0);
  if (err < 0) {
    perror("recevoir: erreur de reception des donnees");
    exit(-5);
  }

  return chaine;
}




void envoyer(const char *chaine) {
  int err;       /* erreur systeme */
  size_t taille; /* taille de la chaine */

  if (connected == NO) {
    sock_trans = socketClient_EAD(Host, Port);

    /* En cas d'erreur on arrete le programme */
    if (sock_trans < 0 ) {
      perror("envoyer: ne peut creer un client");
      exit(-1);
    }

    connected = YES;
  }
  
  /* taille de la chaine + 1 cause \0 */
  taille = strlen(chaine) + 1;

  /* envoie la taille pour faire la reservation memoire */
  err = send(sock_trans, &taille, sizeof(size_t), 0);
  if (err < 0) {
    perror("envoyer: erreur d'envoi de la taille");
    exit(-2);
  }

  err = send(sock_trans, chaine, taille, 0);
  if (err < 0) {
    perror("envoyer: erreur d'envoi des donnees");
    exit(2);
  }
}

void fin_communication(void) {
  if (sock_trans >= 0) {
    shutdown(sock_trans, 0);
    close(sock_trans);
  }
  
  if (sock_conn >= 0) {
    shutdown(sock_conn, 0);
    close(sock_conn);
  }
}
