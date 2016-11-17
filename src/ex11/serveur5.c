/**
 * @author Laurent Philippe, Julien Bernard
 * @date 16 Feb 2004, modified 16 Nov 2011, modified 12 Feb 2012
 *
 * Serveur de calcul.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "fonctionsSocket.h"

#define MAX_CLIENTS 10

int main(int argc, char *argv[]) {
  int sock_cont;
  int sock_trans[MAX_CLIENTS];
  int err;  /* code d'erreur */
  int nfds;

  int i;
  int etape[MAX_CLIENTS];
  char operateur[MAX_CLIENTS];
  int operande1[MAX_CLIENTS];
  int operande2[MAX_CLIENTS];
  int resultat;

  fd_set set;

  /*
   * Verification des arguments
   */
  if (argc != 2) {
    printf ("Usage : serveur no_port\n");
    exit(1);
  }

  /*
   * Creation de la socket, protocole TCP
   */
  printf("serveur: creation de la socket sur %d\n", atoi(argv[1]));
  sock_cont = socketServeur_EAD(atoi(argv[1]));
  if (sock_cont < 0) {
    printf("serveur: erreur socketServeur_EAD\n");
    exit( 2 );
  }

  for (i = 0; i < MAX_CLIENTS; ++i) {
    etape[i] = -1;
  }

  /*
   * Boucle du serveur
   */
  for (;;) {

    /*
     * Reconstitution de l'ensemble
     */
    FD_ZERO(&set);
    FD_SET(sock_cont, &set);
    nfds = sock_cont;

    for (i = 0; i < MAX_CLIENTS; ++i) {
      if (etape[i] == -1) {
        continue;
      }

      FD_SET(sock_trans[i], &set);

      if (sock_trans[i] > nfds) {
        nfds = sock_trans[i];
      }
    }

    /*
     * Attente de connexion
     */
    err = select(nfds + 1, &set, NULL, NULL, NULL);

    if (FD_ISSET(sock_cont, &set)) {
      printf("serveur: nouvelle connexion\n");

      /* Recherche d'un slot libre */
      for (i = 0; i < MAX_CLIENTS; ++i) {
        if (etape[i] == -1) {
          break;
        }
      }

      if (i == MAX_CLIENTS) {
        /* Aucun slot libre */
        fprintf(stderr, "serveur: aucun slot libre, arret!\n");
        exit(9);
      }

      sock_trans[i] = accept(sock_cont, NULL, NULL);
      if (sock_trans[i] < 0) {
        perror("serveur: erreur sur accept");
        exit(3);
      }

      printf("serveur: attribution du slot %i\n", i);

      etape[i] = 0;
    } else {

      for (i = 0; i < MAX_CLIENTS; ++i) {
        if (etape[i] == -1) {
          continue;
        }

        if (!FD_ISSET(sock_trans[i], &set)) {
          continue;
        }

        printf("serveur: reception sur la connexion %i (etape %i)\n", i, etape[i]);

        /* La i-ème connexion est active */
        if (etape[i] == 0) {

          /* réception de l'opérateur */

          err = recv(sock_trans[i], &operateur[i], sizeof(operateur[i]), 0);

          if (err < 0) {
            perror("serveur: erreur dans la reception d'operateur");
            shutdown(sock_trans[i], 2);
            exit(4);
          }

          if (err == 0) {
            close(sock_trans[i]);

            etape[i] = -1;

            printf("serveur: fermeture de la connexion %i\n", i);

            break;
          }

          etape[i] = 1;

        } else if (etape[i] == 1) {

          /* réception du premier opérande */

          err = recv(sock_trans[i], &operande1[i], sizeof(operande1[i]), 0);

          if (err < 0) {
            perror("serveur: erreur dans la reception d'operande1");
            shutdown(sock_trans[i], 2);
            exit(5);
          }

          etape[i] = 2;
        } else if (etape[i] == 2) {

          /* réception second opérande */

          err = recv(sock_trans[i], &operande2[i], sizeof(operande2[i]), 0);

          if (err < 0) {
            perror("serveur: erreur dans la reception d'operande2");
            shutdown(sock_trans[i], 2);
            exit(6);
          }

          /* et envoi du résultat */

          int ok = 0;

          if (operateur[i] == '/' && operande2[i] == 0) {
            ok = 1;
          } else {
            printf("serveur: voila l'operation recue par %i : %d %c %d\n", i, operande1[i], operateur[i], operande2[i]);

            switch (operateur[i]) {
            case '+' : resultat = operande1[i] + operande2[i]; break;
            case '-' : resultat = operande1[i] - operande2[i]; break;
            case '*' : resultat = operande1[i] * operande2[i]; break;
            case '/' : resultat = operande1[i] / operande2[i]; break;
            default :
              printf("serveur: erreur, operateur inconnu\n");
              ok = 2;
            }
          }

          err = send(sock_trans[i], &ok, sizeof(ok), 0);

          if (err != sizeof(ok)) {
            perror("serveur: erreur dans l'envoi de la legalite de l'operation");
            shutdown(sock_trans[i], 2);
            exit(7);
          }

          err = send(sock_trans[i], &resultat, sizeof(resultat), 0);

          if (err != sizeof(resultat)) {
            perror("serveur: erreur dans l'envoi du resultat");
            shutdown(sock_trans[i], 2);
            exit(8);
          }

          etape[i] = 0;
        }

      }

    }

  }

  return 0;
}
