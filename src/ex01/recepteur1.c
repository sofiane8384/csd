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

  /* 
   * Reception du message
   */
  chaine_recevoir = recevoir();

  printf("Message recu: %s\n", chaine_recevoir);

  fin_communication();
  
  free(chaine_recevoir);
  return 0;
}
