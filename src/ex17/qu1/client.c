/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *  ecrit par : LP.
 *
 *  resume :    invocation du serveur de calcul
 *
 *  date :      16 / 02 / 06
 *
 ***********************************************************
 */

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fonctionsSocket.h"

// Protocole includes
#include "protocole.h"

int main(int argc, char **argv)
{

  int sock,               /* descipteur de la socket locale */
      err;                /* code d'erreur */
  char boucle = 'o';
  char operateur;

  // Structures de requete/reponse
  TRequete req;
  TReply rep;


  /*
   * Verification des arguments
   */
  if ( argc != 3 ) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }

  /* 
   * Creation d'une socket, domaine AF_INET, protocole TCP 
   */
  printf("client : connect to %s, %d\n", argv[1], atoi( argv[2]));
  sock = socketClient_EAD( argv[1], atoi( argv[2]) );
  if ( sock < 0 ) {
    
    printf( "client : erreur socketClient\n");
    exit(2);
  }
 
  do {

    /* 
     * Saisie de l'operation
     */
    printf("client : \n");
    printf("\t donner un operateur : ");
    scanf(" %c", &operateur );
    switch( operateur ) {
    case '+' : req.operateur = PLUS; break;
    case '-' : req.operateur = MOINS; break;
    case '*' : req.operateur = FOIS; break;
    case '/' : req.operateur = DIV; break;
    default: printf("Client unknown operator\n");
    }

    printf("\t donner l'operande 1 : ");
    scanf(" %d", &req.firstOp );
    printf("\t donner l'operande 2 : ");
    scanf(" %d", &req.secondOp );

    printf("client : envoi de - %d %c %d - \n", 
	   req.firstOp, operateur, req.secondOp );
    
    /*
     * Envoi de l'operation en une seule structure
     */
    err = send( sock, (void*) &req, sizeof( req ), 0);
    if ( err!= sizeof( req ) ) {
      
      perror("client : erreur sur le send de la requete");
      shutdown(sock, 2);
      exit(3);
    }
    printf("client : envoi realise\n");

    /*
     * Reception du resultat
     */ 
    err = recv ( sock, (void *) &rep, sizeof( rep ), 0 );
    if ( err == -1 ) {

      perror("client : erreur a la reception");
      shutdown(sock, 2);
      exit(6);
    }

    // Traitement de la reponse
    switch( rep.errorCode ) {
    case ERR_OK : 
      printf("client : resultat recu : %d\n", rep.resultat);
      break;
    case ERR_DIV_ZERO :
      printf("Server error : division by zero\n");
      break;
    case ERR_UNKNOWN_OP :
      printf("Server error : unknown operator\n");
      break;
    default : 
      printf("Client error : unknown error code\n");
    }

    /*
     * On continue ?
     */
    printf("client : on continue = o : ");
    
    // Attention, l'espace avant le %c permet de vider le buffer 
    // du caractere CR (enter) de la saisie precedente
    scanf(" %c", &boucle );
    printf("\n");
    
    
  } while ( boucle == 'o' );
  
  /* 
   * Fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
  
  return 0;
}
 

