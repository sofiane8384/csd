/**
 * @author Laurent Philippe, Julien Bernard
 * @date 25 Jun 2006, modified 12 Jul 2010
 *
 * Reçoit une chaine de caractère de l'émetteur.
 */

#include <stdio.h>
#include <stdlib.h>

#include "fonctionsCommunication.h"

int main() {
  char *chaine_recevoir;
  char chaine_envoyer[100];

  /* 
   * Reception du message
   */
  chaine_recevoir = recevoir();

  printf("Message recu: %s\n", chaine_recevoir);

  /* 
   * Saisie de la chaine de retour
   */
  printf("Donnez une chaine: ");
  scanf("%s", chaine_envoyer);
  
  /*
   * Envoi de la chaine
   */
  envoyer(chaine_envoyer);

  
  fin_communication();
  
  free(chaine_recevoir);
  return 0;
}
