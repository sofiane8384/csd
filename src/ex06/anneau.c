#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Lancer dans un premier terminal:
 *   $ ./anneau 3001 1
 * Lancer dans un deuxième terminal:
 *   $ ./anneau 3002 2
 *   puis choisir comme suivant l'hôte "localhost" et le port "3001"
 * Lancer dans un troisième terminal:
 *   $ ./anneau 3003 3
 *   puis choisir comme suivant l'hôte "localhost" et le port "3002"
 * Enfin, revenir sur le premier terminal
 *   puis choisir comme suivant l'hôte "localhost" et le port "3003"
 * 
 */

#include "fonctionsSocket.h"

#define TAILLE_MAX 256

int main(int argc, char *argv[]) {
  
  int desc_sock_conn;
  int desc_sock_prec = -1; 
  int desc_sock_suiv;

  char chaine[TAILLE_MAX];
  
  int envoyes;
  int recus;
  int i;

  int myself;
  int port;
  char host[256];
  

  if (argc != 3) {
    printf("usage : %s no_port no_dans_anneau\n", argv[0]);
    return 1;
  }

  port = atoi(argv[1]);
  myself = atoi(argv[2]);

  desc_sock_conn = socketServeur_EAD(port);
  if (desc_sock_conn < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }

  /* 
   * Initialisation de l'anneau
   */
  
  /* si premier, on accept avant de recevoir */
  if (myself == 1) {
    
    desc_sock_prec = accept(desc_sock_conn, NULL, NULL);
    if (desc_sock_prec == -1) {
      printf("Erreur connexion socket\n");
      close(desc_sock_conn);
      return 2;
    }
    
  }
  
  /* Saisie et initialisation de l'adresse du destinataire */
  printf("anneau(%d) : donner la machine du suivant : ", myself);
  scanf("%s", host);
  printf("anneau(%d) : donner le port du suivant : ", myself);
  scanf("%d", &port );
  printf("anneau(%d) :  %s:%d\n",  myself, host, port);
  

  desc_sock_suiv = socketClient_EAD(host, port);
  if (desc_sock_suiv < 0) {
    printf("Erreur creation socket\n");
    return 1;
  }
  
  if (myself != 1) {
    
    desc_sock_prec = accept(desc_sock_conn, NULL, NULL);
    if (desc_sock_prec == -1) {
      printf("Erreur connexion socket\n");
      close(desc_sock_conn);
      return 2;
    }
    
  }

  assert(desc_sock_prec != -1);

  /*
   * Utilisation de l'anneau
   */

  for(i = 0; i < 5; ++i) {
    
    /* si premier, on envoi le premier */
    if (myself == 1) {

      /* saisie et envoi de la chaine au suivant */
      printf("anneau(%d) : donner la chaine : ", myself);
      scanf("%s", chaine );

      envoyes = send(desc_sock_suiv, chaine, strlen(chaine) + 1, 0);

      if (envoyes == -1) {
        printf("Erreur a l'envoi\n");
        shutdown(desc_sock_suiv, 2);
        close(desc_sock_suiv);
        return 3;
      }

      printf("anneau(%d) : chaine envoyee\n", myself);
    }

    printf("anneau(%d) : pret a recevoir\n", myself);

    recus = recv(desc_sock_prec, chaine, TAILLE_MAX, 0);

    if (recus == -1) {
      printf("Erreur a la reception\n");
      shutdown(desc_sock_prec, 2);
      close(desc_sock_prec);
      return 4;
    }

    printf("anneau(%d) : message recu : %s\n", myself, chaine);
    
    if (myself != 1) {

      envoyes = send(desc_sock_suiv, chaine, strlen(chaine) + 1, 0);

      if (envoyes == -1) {
        printf("Erreur a l'envoi\n");
        shutdown(desc_sock_suiv, 2);
        close(desc_sock_suiv);
        return 3;
      }

      printf("anneau(%d) : chaine envoyee\n", myself);
    }
    
  }
  
  printf("anneau(%d) : fin de communication\n", myself);

  shutdown(desc_sock_suiv, 2);
  shutdown(desc_sock_prec, 2);
  close(desc_sock_suiv);
  close(desc_sock_prec);
  close(desc_sock_conn);

  return 0;
}


