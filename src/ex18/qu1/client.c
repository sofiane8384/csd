/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *  ecrit par : LP.
 *
 *  resume :    invocation du serveur de services
 *
 *  date :      16 / 02 / 04
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

//
// Fonction d'affichage du resultat
//
void traitRep( TCodeRequest errorCode)
{

  // Traitement de la reponse
  switch( errorCode ) {
  
  case ERR_NAME_ALREADY_EXIST:
    printf("Server error : Name already used \n");
    break;
  case ERR_UNKNOWN_NAME :
    printf("Server error : Name not found \n");
    break;
  case ERR_UNKNOWN_PORT :
    printf("Server error : Port not found \n");
    break;
  default : 
    printf("Client error : unknown error code\n");
  }
}


//
// Principal
// 
int main(int argc, char **argv)
{

  int sock,               /* descipteur de la socket locale */
      err;                /* code d'erreur */

  // Structures de requete/reponse
  TRequest req;
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
 
  // Cr�ation d'une requ�te d'ajout
  req.codeReq = AJOUT;
  strcpy( req.specific.ajout.nom, "ead" ); 
  strcpy( req.specific.ajout.proto, "tcp" ); 
  req.specific.ajout.port = 2609;

  // envoi de la requete
  err = send( sock, (void*) &req, sizeof( req ), 0);
  if ( err!= sizeof( req ) ) {
    
    perror("client : erreur sur le send de la requete");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi ajout realise\n");
  
  // Reception du resultat
  err = recv ( sock, (void *) &rep, sizeof( rep ), 0 );
  if ( err == -1 ) {
    
    perror("client : erreur a la reception");
    shutdown(sock, 2);
    exit(6);
  }

  if ( rep.codeRep != ERR_OK ) {

    traitRep( rep.codeRep );
   
  } else { 

    printf("Client : request correctly executed \n"); 
  }

  // Cr�ation d'une requ�te d'attribution
  req.codeReq = ATTRIB;
  strcpy( req.specific.attrib.nom, "ead2" ); 
  strcpy( req.specific.attrib.proto, "tcp" ); 

  // envoi de la requete
  err = send( sock, (void*) &req, sizeof( req ), 0);
  if ( err!= sizeof( req ) ) {
    
    perror("client : erreur sur le send de la requete");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi attrib realise\n");

  // Reception du resultat
  err = recv ( sock, (void *) &rep, sizeof( rep ), 0 );
  if ( err == -1 ) {
    
    perror("client : erreur a la reception");
    shutdown(sock, 2);
    exit(6);
  }

  if ( rep.codeRep != ERR_OK ) {

    traitRep( rep.codeRep );
   
  } else { 

    printf("Client : port attribue %d \n", rep.specific.attrib.port ); 
  }

  // Cr�ation d'une requ�te de consultation
  req.codeReq = CONSULT_NOM;
  strcpy( req.specific.consultNom.nom, "ead" ); 

  // envoi de la requete
  err = send( sock, (void*) &req, sizeof( req ), 0);
  if ( err!= sizeof( req ) ) {
    
    perror("client : erreur sur le send de la requete");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi consult realise\n");

  // Reception du resultat
  err = recv ( sock, (void *) &rep, sizeof( rep ), 0 );
  if ( err == -1 ) {
    
    perror("client : erreur a la reception");
    shutdown(sock, 2);
    exit(6);
  }

  if ( rep.codeRep != ERR_OK ) {

    traitRep( rep.codeRep );
   
  } else { 

    printf("Client : nom = %s proto = %s port = %d \n", 
	   req.specific.consultNom.nom,
	   rep.specific.consultNom.proto,
	   rep.specific.consultNom.port ); 
  }

  // Cr�ation d'une requ�te de suppression
  req.codeReq = SUPPRESS;
  strcpy( req.specific.suppress.nom, "ead" ); 

  // envoi de la requete
  err = send( sock, (void*) &req, sizeof( req ), 0);
  if ( err!= sizeof( req ) ) {
    
    perror("client : erreur sur le send de la requete");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi suppress realise\n");
  
  // Reception du resultat
  err = recv ( sock, (void *) &rep, sizeof( rep ), 0 );
  if ( err == -1 ) {
    
    perror("client : erreur a la reception");
    shutdown(sock, 2);
    exit(6);
  }

  if ( rep.codeRep != ERR_OK ) {

    traitRep( rep.codeRep );
   
  } else { 

    printf("Client : request correctly executed \n"); 
  }

  // Cr�ation d'une requ�te de fin
  req.codeReq = FIN;

  // envoi de la requete
  err = send( sock, (void*) &req, sizeof( req ), 0);
  if ( err!= sizeof( req ) ) {
    
    perror("client : erreur sur le send de la requete");
    shutdown(sock, 2);
    exit(3);
  }
  printf("client : envoi suppress realise\n");
  
  /* 
   * Fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);


  return 0;
}
 

