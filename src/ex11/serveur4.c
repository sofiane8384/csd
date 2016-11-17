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
#include <sys/socket.h>
#include <netinet/in.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {
  int sock_cont;
  int sock_trans;
  int err;  /* code d'erreur */

  char operateur;
  int operande1;
  int operande2;
  int resultat;

  int encore; /* test de boucle pour les envois */
                    
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
    
  /*
   * Boucle du serveur
   */
  for (;;) {

   /*
    * Attente de connexion
    */
    sock_trans = accept(sock_cont, NULL, NULL);
    if (sock_trans < 0) {
      perror("serveur: erreur sur accept");
      exit(3);
    }

    encore = 1;

    do {
      /*
       * Reception et affichage de l'operation en provenance du client
       * si ce dernier a coupe la connexion, on sort sans rien recevoir
       */
      err = recv(sock_trans, &operateur, sizeof(operateur), 0);

      if (err < 0) {
        perror("serveur: erreur dans la reception d'operateur");
        shutdown(sock_trans, 2);
        exit(4);
      }

      if (err == 0) {
        printf("Fin de la connexion client\n");
        encore = 0;
      } else {

        /*
         * reception des operandes
         */
        err = recv(sock_trans, &operande1, sizeof(operande1), 0);
        if (err < 0) {
          perror("serveur: erreur dans la reception d'operande1");
          shutdown(sock_trans, 2);
          exit(5);
        }

        err = recv(sock_trans, &operande2, sizeof(operande2), 0);
        if (err < 0) {
          perror("serveur: erreur dans la reception d'operande2");
          shutdown(sock_trans, 2);
          exit(6);
        }

        int ok = 0;

        if (operateur == '/' && operande2 == 0) {
          ok = 1;
        } else {
          printf("serveur: voila l'operation recue : %d %c %d\n", operande1, operateur, operande2);

          switch (operateur) {
          case '+' : resultat = operande1 + operande2; break;
          case '-' : resultat = operande1 - operande2; break;
          case '*' : resultat = operande1 * operande2; break;
          case '/' : resultat = operande1 / operande2; break;
          default :
            printf("serveur: erreur, operateur inconnu\n");
            ok = 2;
          }
        }

        err = send(sock_trans, &ok, sizeof(ok), 0);
        if (err != sizeof(ok)) {
          perror("serveur: erreur dans l'envoi de la legalite de l'operation");
          shutdown(sock_trans, 2);
          exit(7);
        }

        err = send(sock_trans, &resultat, sizeof(resultat), 0);
        if (err != sizeof(resultat)) {
          perror("serveur: erreur dans l'envoi du resultat");
          shutdown(sock_trans, 2);
          exit(8);
        }
      }
    } while (encore == 1);

    /*
     * arret de la connexion et fermeture
     */
    shutdown(sock_trans, 2);
    close(sock_trans);
  }

  return 0;
}
