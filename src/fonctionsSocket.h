#ifndef FONCTIONS_SOCKET_H
#define FONCTIONS_SOCKET_H

/**
 * @author Laurent Philippe, Julien Bernard
 * @date 25 Jan 2006, modified 29 Jun 2010
 */

#include <netinet/in.h>

/* Codes erreur des fonctions */
#define ERR_SOCKET  -1
#define ERR_BIND    -2
#define ERR_LISTEN  -3
#define ERR_GETHOST -4
#define ERR_CONNECT -5

/**
 * Crée une socket serveur en mode connecté et la renvoie.
 * @param port le numéro du port du serveur
 * @return la socket créée
 */
int socketServeur_EAD(unsigned short port);

/**
 * Crée une socket client en mode connecté et la connecte au serveur
 * @param nom_machine le nom du serveur (ex : "localhost")
 * @param port le port du serveur
 * @return la socket créée
 */
int socketClient_EAD(const char *nom_machine, unsigned short port);

/**
 * Crée une socket en mode non-connecté
 * @param port le port de connexion
 * @return la socket créée
 */
int socketUDP_EAD(unsigned short port);

/**
 * Crée une structure d'adresse
 * @param nom_machine le nom du serveur (ex : "localhost")
 * @param port le port du serveur
 * @return une structure adresse allouée grâce à malloc
 */
struct sockaddr *socketAddr_EAD(const char *nom_machine, unsigned short port);

/**
 * Renvoie la taille de la structure d'adresse
 * @return la taille souhaitée
 */
socklen_t tailleAddr_EAD(void);

#endif /* FONCTIONS_SOCKET_H */
