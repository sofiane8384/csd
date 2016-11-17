/**
 * @author Laurent Philippe, Julien Bernard
 * @date 16 Feb 2004, modified 16 Nov 2011, modified 12 Feb 2012
 *
 * Invocation du serveur de calcul.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "fonctionsSocket.h"

int main(int argc, char *argv[]) {

  int sock; /* descipteur de la socket locale */
  int err;  /* code d'erreur */
  char boucle = 'o';

  char operateur;
  int operande1, operande2;
  int resultat;

  /*
   * Verification des arguments
   */
  if (argc != 3) {
    printf("Usage: client nom_machine no_port\n");
    exit(1);
  }

  sock = socketClient_EAD(argv[1], atoi(argv[2]));
  if (sock < 0) {
    printf( "client: erreur socketClient_ead\n");
    exit(2);
  }
 
  do {

    /* 
     * Saisie de l'operation
     */
    printf("client: \n");
    printf("\t donner un operateur : ");
    scanf(" %c", &operateur);
    printf("\t donner l'operande 1 : ");
    scanf(" %d", &operande1);
    printf("\t donner l'operande 2 : ");
    scanf(" %d", &operande2);
    printf("client: envoi de - %d %c %d - \n", operande1, operateur, operande2);
    
    /*
     * Envoi de l'operation en plusieurs parties
     */
    err = send(sock, &operateur, sizeof(operateur), 0);
    if (err != sizeof(operateur)) {
      perror("client: erreur sur le send d'operateur");
      shutdown(sock, 2);
      exit(3);
    }
    
    err = send(sock, &operande1, sizeof(operande1), 0);
    if (err != sizeof(operande1)) {
      perror("client: erreur sur le send d'operande1");
      shutdown(sock, 2);
      exit(4);
    }

    err = send(sock, &operande2, sizeof(operande2), 0);
    if (err != sizeof(operande2)) {
      perror("client : erreur sur le send d'operande2");
      shutdown(sock, 2);
      exit(5);
    }

    printf("client: envoi realise\n");

    /*
     * Reception du résultat
     */ 
    err = recv(sock, &resultat, sizeof(resultat), 0);
    if (err < 0) {
      perror("client: erreur a la reception");
      shutdown(sock, 2);
      exit(6);
    }
    printf("client: resultat recu : %d\n", resultat);
   
    /*
     * On continue ?
     */
    printf("client: on continue = o : ");

    // Attention, l'espace avant le %c permet de vider le buffer
    // du caractere de nouvelle ligne de la saisie precedente
    scanf(" %c", &boucle);
    printf("\n");


  } while (boucle == 'o');

  /* 
   * Fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
  
  return 0;
}
