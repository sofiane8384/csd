/**
 * @author Laurent Philippe, Julien Bernard
 * @date 25 Jan 2006, modified 29 Jun 2010
 */
#include "fonctionsSocket.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

int socketServeur_EAD(unsigned short port) {
  int sock; /* descripteur de la socket */
  int err;	/* code d'erreur */

  struct sockaddr_in nom;	/* adresse de la sochet */

  /* Creation de la socket, protocole TCP */
  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0) {
    perror("Erreur a la creation de la socket");
    return ERR_SOCKET;
  }

  /* Initialisation de l'adresse de la socket */
  nom.sin_family = AF_INET;
  nom.sin_port = htons(port);
  nom.sin_addr.s_addr = INADDR_ANY;
  memset(nom.sin_zero, 0, 8);

  /* Attribution de l'adresse a la socket */
  err = bind(sock, (struct sockaddr *)&nom, sizeof(struct sockaddr_in));
  if (err < 0) {
    perror("Erreur sur le bind");
    return ERR_BIND;
  }

  /* Utilisation en socket de controle, puis attente de demandes de connexion. */
  err = listen(sock, 1);
  if (err < 0) {
    perror("Erreur dans listen");
    return ERR_LISTEN;
  }

  /* Retourne le descripteur de socket */
  return sock;
}

int socketClient_EAD(const char *nom_machine, unsigned short port) {

  int sock; /* descripteur de la socket */
  int err;  /* code d'erreur */

  struct hostent *host;     /* description de la machine serveur */
  struct sockaddr_in addr;  /* adresse de la sochet du serveur */

  /* Creation d'une socket, domaine AF_INET, protocole TCP */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Erreur a la creation de la socket");
    return ERR_SOCKET;
  }

  /* Initialisation de l'adresse de la socket */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  /* Recherche de l'adresse de la machine */
  host = gethostbyname(nom_machine);
  if (host == NULL) {
    printf("Erreur dans la recherche de l'adresse de la machine (gethostbyname)");
    return ERR_GETHOST;
  }

  /* Recopie de l'adresse IP */
  addr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;

  /* Connection au serveur */
  err = connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (err < 0) {
    perror("Erreur la connexion de la socket");
    return ERR_CONNECT;
  }
 
  /* On retourne le descripteur de socket */
  return sock;
}
 

int socketUDP_EAD(unsigned short port) {
  int sock; /* descipteur de la socket */
  int err;	/* code d'erreur */

  struct sockaddr_in addr; /* adresse de la sochet */

  /* Creation de la socket, protocole UDP */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("Erreur a la creation de la socket");
    return ERR_SOCKET;
  }

  /* Initialisation de l'adresse de la socket */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;

  /* Attribution de l'adresse a la socket */
  err = bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (err < 0) {
    perror("Erreur sur le bind");
    return ERR_BIND ;
  }

  /* Retourne le descripteur de socket */
  return sock;
}


struct sockaddr *socketAddr_EAD(const char *nom_machine, unsigned short port) {
  static struct sockaddr_in addr;
  struct hostent *host;
  
  /* Cherche l'adresse de la machine */
  host = gethostbyname(nom_machine);
  if (host == NULL) {
    printf("Erreur dans la recherche de l'adresse de la machine (gethostbyname)");
    return NULL;
  }

  memset(&addr, 0, sizeof(addr));

  /* Recopie de l'adresse IP */
  addr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;

  /* Initialisation de l'adresse de la socket */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);

  return (struct sockaddr *)&addr;
}

socklen_t tailleAddr_EAD(void) {
  return sizeof(struct sockaddr_in);
}
