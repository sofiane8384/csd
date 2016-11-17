/*
 **********************************************************
 *
 *  Programme : testInterCli.c
 *
 *  ecrit par : Laurent P.
 *
 *  resume :    envoi une chaine de caracteres a un programme serveur
 *              dont l'adresse intrenet et le numero de port son lu
 *              au clavier. (cf. prgm testInterServ.c)
 *
 *  date :      22/05/95
 *
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fonctionsSocket.h"

/* Chaine envoyee au serveur-recepteur */
#define chaine "Hello world !"


int main()
{
  int sock,               /* descipteur de la socket locale */
      err;                /* code d'erreur */

  /* 
   * Creation d'une socket, domaine AF_INET, protocole TCP 
   */
  sock = socketClient_EAD( "localhost", 5555 );
 
  /* 
   * Envoi de la chaine 
   */
  printf("client: envoi de - %s - \n", chaine);
  
  err = send( sock, chaine, strlen(chaine), 0);
  if ( err!= strlen(chaine) ) {
      perror("tcpInetCli, eErreur sur le send\n");
      exit(3);
  }

  /* Fermeture de la socket */
  close(sock);
  
  return 0;
}
 

