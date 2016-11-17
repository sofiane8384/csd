#ifndef FONCTIONS_COMMUNICATION_H
#define FONCTIONS_COMMUNICATION_H

/**
 * @author Laurent Philippe, Julien Bernard
 * @date 25 Jun 2006, modified 12 Jul 2010
 */



/**
 * Envoie la chaîne de caractère.
 * @param chaine la chaine de caractère à envoyer.
 */
void envoyer(const char *chaine);

/**
 * Reçoit une chaîne de caractère.
 * @return la chaine de caractère reçue.
 */
char *recevoir(void);

/**
 * Coupe la communication.
 */
void fin_communication(void);

#endif /* FONCTIONS_COMMUNICATION_H */
