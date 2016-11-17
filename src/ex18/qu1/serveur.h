#ifndef SERVEUR_H
#define SERVEUR_H

/* Nombre max de connexions */
#define MAX_CONNECT 32

typedef enum { OCCUPED, FREE } TState;

// Service table entry
typedef struct {

  TState state; 
  char   nom[NAME_SIZE]; 
  char   proto[PROTO_SIZE];
  short  port;
  
} TServiceTableEntry;

// Service Table size
#define SERVICE_TABLE_SIZE 10

// code d'erreur non trouve dans la table
#define NOT_FOUND -1

#endif
