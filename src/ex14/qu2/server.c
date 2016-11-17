/*
 **********************************************************
 *
 *  Program : server.c
 *
 *  author : Laurent P.
 *
 *  synopsis :    recoit une chaine de caracteres du programme client
 *
 *  date :      
 ***********************************************************
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "fonctionsSocket.h"

int main()
{
    int             sock_cont, 
                    sock_trans;	        /* descipteurs des sockets locales */

    struct sockaddr_in nom_transmis;	/* adresse de la socket de */
					/* transmission */

    socklen_t size_addr_trans;	/* taille de l'adresse d'une socket */

    int len, titi;
    char recu, envoi[5];

    size_addr_trans = sizeof(struct sockaddr_in);

    /* Creation de la socket, protocole TCP */
    sock_cont = socketServeur_EAD( 5555 );

    sock_trans = accept(sock_cont, 
                        (struct sockaddr *)&nom_transmis, 
                        &size_addr_trans);
    if (sock_trans < 0) {
	perror("server, erreur sur accept");
	exit(5);
    }

    /*
     * Reception et affichage du message en provenance du client java
     */
    len = recv( sock_trans, &recu, 1, 0);
    if (len < 0) {
        perror("server, erreur dans la reception");
        exit(6);
    }
    printf("Voila le message recu: %d, taille = %d\n", recu, len);

    /*
     * Envoi d'un message au client java
     * attention le nombre est trop grand et on ne recoit que
     * le dernier octet
     */
    titi = 0x2222;
    len = send( sock_trans, &titi, 1, 0);
    if (len < 0) {
        perror("server, erreur dans l'envoi");
        exit(6);
    }
    printf("Entier envoye\n");
    
    /*
     * Envoi d'un buffer au client java
     */
    envoi[0]=1;
    envoi[1]=2;
    envoi[2]=3;
    envoi[3]=4;
    envoi[4]=5;

    len = send( sock_trans, envoi, 5, 0);
    if (len < 0) {
        perror("server, erreur dans l'envoi");
        exit(6);
    }
    printf("Buffer envoye\n");

    /* arret de la connexion */
    shutdown(sock_trans, 2);

    /* Fermeture de la socket */
    close(sock_cont);

    return 0;
}
