/*
 **********************************************************
 *
 *  Entete : protocole.h
 *
 *  ecrit par : LP.
 *
 *  resume :    donne les structures des données utilisées par
 *              la communication avec le serveur de port.
 *
 *              ATTENTION, on ne met dans ce fichier que ce qui
 *                         concerne la communication
 *
 *  date :      16 / 02 / 06
 *
 ***********************************************************
 */

#include "fonctionsSocket.h"

// --------------------------------------------
//
// Constantes specifiques au protocole
//
// --------------------------------------------

#define NAME_SIZE 50
#define PROTO_SIZE 4


// --------------------------------------------
//
// Types enumeres : request type and error type
//
// --------------------------------------------

// codes des requetes
typedef enum { AJOUT, 
	       ATTRIB, 
	       CONSULT_NOM, 
	       CONSULT_PORT, 
	       SUPPRESS,
	       FIN 
} TCodeRequest;

// codes d'erreur
typedef enum { ERR_OK,
	       ERR_UNKNOWN_REQUEST,
	       ERR_NO_MORE_ENTRY,
	       ERR_NAME_ALREADY_EXIST, 
	       ERR_UNKNOWN_NAME,
               ERR_UNKNOWN_PORT
} TErrorCode;

//------------------------
//
// Structures des requetes
//
//------------------------

// Partie specifique

// Requete d'ajout
typedef struct {

  char nom[NAME_SIZE]; 
  char proto[PROTO_SIZE];
  short port;
  
} TAjoutReq;

// Requete d'attribution
typedef struct {

  char nom[NAME_SIZE]; 
  char proto[PROTO_SIZE];
  
} TAttribReq;

// Requete de consultation par nom
typedef struct {

  char nom[NAME_SIZE]; 
  
} TConsultNomReq;

// Requete de consultation par port
typedef struct {

  short port;
  
} TConsultPortReq;

// Requete de suppression
typedef struct {

  char nom[NAME_SIZE]; 
  
} TSuppressReq;


// Type de requete generique

typedef struct {

  TCodeRequest codeReq;
  union {

    TAjoutReq       ajout;
    TAttribReq      attrib;
    TConsultNomReq  consultNom;
    TConsultPortReq consultPort;
    TSuppressReq    suppress;
  } specific ;
    
} TRequest;

// -----------------------
//
//  Structure des reponses
//
// -----------------------

// Partie specifique

// Reponse d'ajout n'a pas de partie specifique

// Reponse d'attribution
typedef struct {

  short port;
  
} TAttribRep;

// Reponse de consultation par nom
typedef struct {

  char proto[PROTO_SIZE];
  short port;
  
} TConsultNomRep;

// Reponse de consultation par port
typedef struct {

  char nom[NAME_SIZE]; 
  char proto[PROTO_SIZE];
  
} TConsultPortRep;

// Reponse de suppression n'a pas de partie specifique

// Type de reponse generique

typedef struct {

  TErrorCode codeRep;
  union {

    TAttribRep      attrib;
    TConsultNomRep  consultNom;
    TConsultPortRep consultPort;

  } specific;
    
} TReply;

