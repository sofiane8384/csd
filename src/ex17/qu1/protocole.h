/*
 **********************************************************
 *
 *  Entete : protocole.h
 *
 *  ecrit par : LP.
 *
 *  resume :    donne les structures des données utilisées par
 *              la communication avec le serveur de calcul.
 *
 *              ATTENTION, on ne met dans ce fichier que ce qui
 *                         concerne la communication
 *
 *  date :      16 / 02 / 06
 *
 ***********************************************************
 */

#include "fonctionsSocket.h"


// Types enumeres : request type and error type
typedef enum { PLUS, MOINS, FOIS, DIV } TOperator;
typedef enum { ERR_OK, ERR_DIV_ZERO , ERR_UNKNOWN_OP } TErrorCode;

// Structure de requete

typedef struct {

  TOperator operateur;
  int firstOp; 
  int secondOp; 
  
} TRequete;


//  Structure de reponse

typedef struct {

  TErrorCode errorCode; 
  int resultat; 
  
} TReply;
