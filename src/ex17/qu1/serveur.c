/*
 **********************************************************
 *
 *  Programme : serveur.c
 *
 *  ecrit par : LP.
 *
 *  resume :    calcule l'operation
 *              plusieurs fois pour le client. Chaque client est 
 *              traite par un processus different
 *
 *  date :      16 / 02 / 06
 *
 ***********************************************************
 */

// Standard includes
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Protocol includes
#include "protocole.h"

/* taille du buffeur de reception */
#define TAIL_BUF 100

// -------------------------------------------------
// Fonction de traitement de la requete utilisee par
// le processus fils
// --------------------------------------------------
void traitReq( int sockTrans )
{
  
  TRequete        req;          /* Requete de calcul */
  TReply          rep;          /* Reponse au client */
  
  int             encore;       /* test de boucle pour les envois */
  pid_t           myPid;        /* Identif du process */
  int             err;	        /* code d'erreur */


  encore = 1;

  myPid = getpid();

  while ( encore == 1 ) {
    
    /*
     * Reception et affichage de l'operation en provenance du client
     * si ce dernier a coupe la connexion, on sort sans rien recevoir
     */
    err = recv( sockTrans, &req, sizeof( req ), 0);
    if (err < 0) {
      perror("serveur : erreur dans la reception d'operateur");
      shutdown(sockTrans, 2);
      exit(4);
    }
    if ( err == 0 ) {
      
      printf("serveur %d : fin de la connexion client\n", myPid);
      encore = 0;
      
    } else {
      
      char operateur = '#';

      // Affichage
      switch( req.operateur ) {
      case PLUS : operateur = '+'; break;
      case MOINS : operateur = '-' ; break;
      case FOIS : operateur = '*'; break;
      case DIV : operateur = '/'; break;
      default: printf("Client unknown operator\n");
      }
      printf("serveur %d : voila l'operation recue : %d %c %d\n", 
	     myPid, req.firstOp, operateur, req.secondOp );
      
      switch ( req.operateur ) {
	
      case PLUS : 
	rep.errorCode = ERR_OK ;
	rep.resultat = req.firstOp + req.secondOp;
	break;
      case MOINS :  
	rep.errorCode = ERR_OK ;
	rep.resultat = req.firstOp - req.secondOp;
	break;
      case FOIS : 
	rep.errorCode = ERR_OK ; 
	rep.resultat = req.firstOp * req.secondOp;
	break;
      case DIV :
  
	if ( req.secondOp == 0 ) {

	  rep.errorCode = ERR_DIV_ZERO;

	} else {

	  rep.errorCode = ERR_OK ; 
	  rep.resultat = req.firstOp / req.secondOp;
	}
	break;
      default : 
	printf("serveur %d : erreur, operateur inconnu\n", myPid);
	rep.errorCode = ERR_UNKNOWN_OP;
	rep.resultat = 0;
      }
      
      err = send( sockTrans, (void *) &rep , sizeof( rep ), 0 );
      if ( err != sizeof( rep ) ) {
	
	perror("serveur : erreur dans l'envoi du resultat");
	shutdown(sockTrans, 2);
	exit(7);
      }
    }
  }
  
}

// -------------------------------------------------
// Fonction principale
// --------------------------------------------------

int main(int argc, char** argv)
{
    int             sock_cont, 
                    sock_trans;	        /* descipteurs des sockets locales */


    struct sockaddr_in nom_transmis;	/* adresse de la socket de */
					/* transmission */

    socklen_t       size_addr_trans;	/* taille de l'adresse d'une
					   socket */
    int             pid;                /* PID du processus fils */


                    


    /*
     * Verification des arguments
     */
    if ( argc != 2 ) {

      printf ( "usage : serveur no_port\n" );
      exit( 1 );
    }

    size_addr_trans = sizeof(struct sockaddr_in);

    /* 
     * Creation de la socket, protocole TCP 
     */
    printf("serveur : creation de la socket sur %d\n", atoi( argv[1] ));
    sock_cont = socketServeur_EAD( atoi( argv[1] ) );
    if ( sock_cont < 0 ) {

      printf( "serveur : erreur socketServeur\n" );
      exit( 2 );
    }
    
    /*
     * Boucle du serveur
     */
    for (;;) {

      /*
       * Attente de connexion
       */
      sock_trans = accept(sock_cont, 
			  (struct sockaddr *)&nom_transmis, 
			  &size_addr_trans);
      if (sock_trans < 0) {
	perror("serveur :  erreur sur accept");
	exit(3);
      }



      pid = fork();

      switch ( pid ) {
      case 0 :  // Processus fils, appel de la fonction
	        // de traitement des requetes
	
	close( sock_cont );
	traitReq( sock_trans );
	
	/* 
	 * arret de la connexion et fermeture
	 */
	shutdown(sock_trans, 2);
	close(sock_trans);
	
	// fin du fils
	exit(0);
	break;

      case -1 : // erreur

	perror("Creation processus fils");
	
	// Fermeture des sockets et fin
	close( sock_cont );
	shutdown(sock_trans, 2);
	close(sock_trans);
	exit(3);
	
      default : // processus pere

	
	// Ferme la socket connectee et attend la suite
	close(sock_trans);
      }
    }

  return 0;
}
