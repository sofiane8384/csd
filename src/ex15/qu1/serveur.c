/*
 **********************************************************
 *
 *  Programme : serveur.c
 *
 *  ecrit par : LP.
 *
 *  resume :    calcule le resultat de l'operation
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
#include <signal.h>
#include <unistd.h>

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "fonctionsSocket.h"

/* taille du buffeur de reception */
#define TAIL_BUF 100

// -------------------------------------------------
// Gestion fin processus fils
// --------------------------------------------------void finFils() 
void finFils() 
{
  int status;

  // Wait for the child to be finished
  wait( &status );
}

// -------------------------------------------------
// Fonction de traitement de la requete utilisee par
// le processus fils
// --------------------------------------------------
void traitReq( int sockTrans )
{
  
  char            operateur;  	/* buffer de reception */
  int             operande1;    /* operandes */
  int             operande2;          
  int             resultat;     /* ... de l'operation */
  
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
    err = recv( sockTrans, &operateur, sizeof( operateur ), 0);
    if (err < 0) {
      perror("serveur : erreur dans la reception d'operateur");
      shutdown(sockTrans, 2);
      exit(4);
    }
    if ( err == 0 ) {
      
      printf("serveur %d : fin de la connexion client\n", myPid);
      encore = 0;
      
    } else {
      
      // reception des operandes
      err = recv( sockTrans, &operande1, sizeof( operande1 ), 0);
      if (err < 0) {
	perror("serveur : erreur dans la reception d'operande1");
	shutdown(sockTrans, 2);
	exit(5);
      }
      err = recv( sockTrans, &operande2, sizeof( operande2 ), 0);
      if (err < 0) {
	perror("serveur : erreur dans la reception d'operande2");
	shutdown(sockTrans, 2);
	exit(6);
      }
      printf("serveur %d : voila l'operation recue : %d %c %d\n", 
	     myPid, operande1, operateur, operande2 );
      
      switch ( operateur ) {
	
      case '+' : resultat = operande1 + operande2;
	break;
      case '-' :  resultat = operande1 - operande2;
	break;
      case '*' :  resultat = operande1 * operande2;
	break;
      case '/' :  resultat = operande1 / operande2;
	break;
      default : 
	printf("serveur %d : erreur, operateur inconnu\n", myPid);
	resultat = 0;
      }
      
      err = send( sockTrans, (char *) &resultat , sizeof( resultat ), 0 );
      if ( err != sizeof( resultat ) ) {
	
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

    /* 
     * Gestion fin des processus fils = pour eviter zombies
     */
    signal( SIGCHLD, finFils); 

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
	close( sock_cont);
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
