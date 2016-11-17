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

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Protocol includes
#include "protocole.h"

#include "serveur.h"

// Service Table
TServiceTableEntry serviceTable[ SERVICE_TABLE_SIZE ];

// -------------------------------------------
// Fonction de traitement de la table
// -------------------------------------------

// Initialisation de la table
void initServiceTable()
{
  int i;

  for ( i = 0 ; i < SERVICE_TABLE_SIZE ; i++ ) {

    serviceTable[ i ].state = FREE;
  }
}

// recherche dans la table par nom
// retourne -1 si nom trouve
int getIndiceByName(char* nom)
{
  int i = 0;
  int retour;
  int found = 0;
  
  while (( found == 0) && ( i < SERVICE_TABLE_SIZE )) {

    if ( strcmp( nom, serviceTable[ i ].nom ) == 0 ) {

      found = 1;

    } else {     

      i++;
    }
  }

  if ( i == SERVICE_TABLE_SIZE ) retour = NOT_FOUND; else retour = i;
  return retour;
}

// recherche dans la table par port
int getIndiceByPort(short port)
{
  int i = 0;
  int retour;
  int found = 0;
  
  while (( found == 0) && ( i < SERVICE_TABLE_SIZE )) {

    if ( port == serviceTable[ i ].port ) {

      found = 1;

    } else {     

      i++;
    }
  }
   
  if ( i == SERVICE_TABLE_SIZE ) retour = NOT_FOUND; else retour = i;
  return retour;
}

// recherche le prochain libre de la table
int getNextFree()
{
  int i = 0;
  int retour;
  int found = 0;
  
  while (( found == 0) && ( i < SERVICE_TABLE_SIZE )) {

    if ( serviceTable[ i ].state == FREE ) {

      found = 1;

    } else {     

      i++;
    }
  }
   
  if ( i == SERVICE_TABLE_SIZE ) retour = NOT_FOUND; else retour = i;
  return retour;
}


// -------------------------------------------
// Fonction de traitement d'une requete d'ajout
// -------------------------------------------
TErrorCode ajoutTable( TAjoutReq ajout )
{
  int i;
  TErrorCode retour;

  i = getIndiceByName( ajout.nom );
  if ( i != NOT_FOUND ) { // Name exist

    retour = ERR_NAME_ALREADY_EXIST;

  } else {

    i = getNextFree();
    if ( i == NOT_FOUND ) { // no more entry

      retour = ERR_NO_MORE_ENTRY;

    } else {

      // ajout service
      serviceTable[ i ].state = OCCUPED;
      strcpy( serviceTable[ i ].nom, ajout.nom );
      strcpy( serviceTable[ i ].proto, ajout.proto );
      serviceTable[ i ].port = ajout.port;

      retour = ERR_OK;
    }
  }

  return retour;
}

// ---------------------------------------------------
// Fonction de traitement d'une requete d'attribution
// ---------------------------------------------------
TErrorCode attribPort( TAttribReq attrib , short* port)
{

  TErrorCode retour;
  
  // attribution du numero de port
  static int currentPort = 2609;

  *port = currentPort;
  currentPort++;

  // declaration du service, utilisation de la fonction d'ajout
  TAjoutReq req;

  strcpy( req.nom, attrib.nom );
  strcpy( req.proto, attrib.proto );
  req.port = *port;

  retour = ajoutTable( req );

  return retour;
}

// ---------------------------------------------------
// Fonction de traitement d'une requete de consultation par nom
// ---------------------------------------------------
TErrorCode consultNom( TConsultNomReq consultNom , char* proto, short* port)
{
  int i;
  TErrorCode retour;

  i = getIndiceByName( consultNom.nom );
  if ( i == NOT_FOUND ) { // Name doesn't exist

    retour = ERR_UNKNOWN_NAME;

  } else {

    // recopie des infos
    strcpy( proto, serviceTable[ i ].proto );
    (*port) = serviceTable[ i ].port ;
    
    retour = ERR_OK;
  }

  return retour; 
}

// ---------------------------------------------------
// Fonction de traitement d'une requete de consultation par port
// ---------------------------------------------------
TErrorCode consultPort( TConsultPortReq consultPort , char* nom, char* proto)
{
  int i;
  TErrorCode retour;

  i = getIndiceByPort( consultPort.port );
  if ( i == NOT_FOUND ) { // Port doesn't exist

    retour = ERR_UNKNOWN_PORT;

  } else {

    // recopie des infos
    strcpy( nom, serviceTable[ i ].nom );
    strcpy( proto, serviceTable[ i ].proto );

    
    retour = ERR_OK;
  }

  return retour; 
}

// ---------------------------------------------------
// Fonction de traitement d'une requete de suppression
// ---------------------------------------------------
TErrorCode suppressTable( TSuppressReq suppress )
{
  int i;
  TErrorCode retour;

  i = getIndiceByName( suppress.nom );
  if ( i == NOT_FOUND ) { // Name doesn't exist

    retour = ERR_UNKNOWN_NAME;

  } else {

    // suppression service
    serviceTable[ i ].state = FREE;

    // Inutile... mais plus sur
    strcpy( serviceTable[ i ].nom, " " );
    strcpy( serviceTable[ i ].proto, " " );
    serviceTable[ i ].port = 0;
    
    retour = ERR_OK;
  }

  return retour;
}

// -------------------------------------------------
// Fonction de traitement general de la requete 
// --------------------------------------------------

void traitReq( TRequest req, TReply* rep )
{

  
  // parametres des fonctions specifiques
  short port;
  char nom[NAME_SIZE]; 
  char proto[PROTO_SIZE];


  //
  // appel des fonctions specifiques aux requetes
  //
  switch ( req.codeReq ) {
    
  case AJOUT : printf("Serveur : ajout\n");
    (*rep).codeRep = ajoutTable( req.specific.ajout );
    break;

  case ATTRIB :  printf("Serveur : attrib\n");
    (*rep).codeRep = attribPort( req.specific.attrib, &port );
    if ( (*rep).codeRep == ERR_OK ) {

      (*rep).specific.attrib.port = port;
    }
    break;

  case CONSULT_NOM : printf("Serveur : consult_nom\n");
    (*rep).codeRep = consultNom( req.specific.consultNom, proto, &port );
    if ( (*rep).codeRep == ERR_OK ) {
      
      strcpy( (*rep).specific.consultNom.proto, proto );
      (*rep).specific.consultNom.port = port;
    }
    break;

  case CONSULT_PORT : printf("Serveur : consult_port\n");
    (*rep).codeRep = consultPort( req.specific.consultPort, nom, proto );
    if ( (*rep).codeRep == ERR_OK ) {
      
      strcpy( (*rep).specific.consultPort.nom, nom );
      strcpy( (*rep).specific.consultPort.proto, proto );
    }
    
    break;
    
  case SUPPRESS : printf("Serveur : suppress\n");
    (*rep).codeRep = suppressTable( req.specific.suppress );
    break;

  case FIN : printf("Serveur : fin \n");
    break;

  default : 
    printf("serveur : erreur, operateur inconnu\n");
    (*rep).codeRep = ERR_UNKNOWN_REQUEST;
  }
  
}


// -------------------------------------------------
// Fonction principale
// --------------------------------------------------

int main( int argc, char** argv, char** envp )
{
  int sock_cont,                  /* descipteur de socket de connexion */
      sockTrans[MAX_CONNECT],     /* descipteurs des sockets locales */
      nbConnect,                  /* nombre de connexions en cours */
      err;                        /* code d'erreur */

  struct sockaddr_in nomTrans;    /* adresse de la socket de transmission */

  TRequest req;                   /* Requete recue */
  TReply   rep;                   /* Reponse envoyee */

  socklen_t   sizeAddrTrans;     /* taille de l'adresse d'une socket */
  
  /* Variables pour le select */
  fd_set readSet;

  /* Variables d'iteration */
  int i;
  
  
  /* Initialisations */
  nbConnect = 0;
  
  initServiceTable();

  /*
   * Verification des arguments
   */
  if ( argc != 2 ) {
    
    printf ( "usage : serveur no_port\n" );
    exit( 1 );
  }
  
  /* 
   * Creation de la socket, protocole TCP 
   */
  printf("serveur : creation de la socket sur %d\n", atoi( argv[1] ));
  sock_cont = socketServeur_EAD( atoi( argv[1] ) );
  if ( sock_cont < 0 ) {
    
    printf( "serveur : erreur socketServeur\n" );
    exit( 2 );
  }
  
  
  /* Boucle principale */
  for (;;) {
    
    /* Preparation du fd_set */
    FD_ZERO( &readSet );
    
    FD_SET( sock_cont, &readSet );

    /* Positionne l'ensemble des descripteurs */
    for ( i = 0 ; i < nbConnect ; i++ ) {

      FD_SET( sockTrans[ i ], &readSet );
    }

    err = select ( FD_SETSIZE, &readSet, NULL, NULL, NULL );
    if (err<0) {

      perror("serveur : Error in select"); 
    } 

    /* Test du descripteur de connexion */
    if ( FD_ISSET( sock_cont, &readSet )) {
      

      // 
      // Gestion des nouvelles demandes de connexion
      // 
      if ( nbConnect < MAX_CONNECT ) {
	
	/* Acceptation d'une demande de connexion */
	sizeAddrTrans = sizeof( struct sockaddr_in );
	sockTrans[ nbConnect ] = accept (sock_cont, 
					 (struct sockaddr *) &nomTrans, 
					 &sizeAddrTrans);  
	if ( sockTrans[ nbConnect ] < 0 ) {
	  
	  printf("serveur: Erreur %d sur le accept1\n", errno);

	} else {

	  printf("serveur : connexion de %d \n", nbConnect );
	  nbConnect++;
	}

      } else {

	printf("serveur : plus de connexion disponibles \n");
      }

    } /* Fin demandes de connexion */
      
    //
    // Gestion des requetes 
    //
    for ( i = 0 ; i < nbConnect ; i++ ) {
      
      if ( FD_ISSET( sockTrans[ i ], &readSet )) {

	/* Reception du message */
	err=recv(sockTrans[ i ], (void *) &req, sizeof( req) , 0);
	if ( err < 0 ) {
	  
	  printf("serveur: Erreur %d dans le recv pour %d\n", errno, i);
	  shutdown(sockTrans[ i ], 2);
	  close(sockTrans[ i ]);

	}

	traitReq( req, &rep );

	// Pour la fin on ne retourne pas de reponse
	if ( req.codeReq == FIN ) {

	  printf("Serveur : fin client %d \n", i);
	  shutdown(sockTrans[ i ], 2);
	  close(sockTrans[ i ]);

	  nbConnect--;

	} else {

	  err = send( sockTrans[ i ], (void *) &rep , sizeof( rep ), 0 );
	  if ( err != sizeof( rep ) ) {
	    
	    perror("serveur : erreur dans l'envoi du resultat");
	    shutdown(sockTrans[ i ], 2);
	    close(sockTrans[ i ]);
	  }
	}  
      } 

    } // fin descripteurs de transmission

  } // fin boucle for(;;)

  return 0;
}

 
  
