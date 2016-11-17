#ifndef TYPES_H
#define TYPES_H

/* Les types doivent être identiques du coté du client et du serveur.
 * Une manière de faire, comme ici, est de les définir dans un fichier inclus
 * des deux côtés. Une autre manière est de définir ces types des deux côtés,
 * ce qui implique de faire les modifications des deux côtés en cas de
 * changement du type (d'où des risques d'erreur).
 *
 * !!! Attention !!!
 * Jamais de pointeur dans les variables, structures ou types envoyés dans
 * une socket.
 */

typedef int mon_type_t;

typedef struct {
  int a;
  char b[6];
  float c;
} ma_structure_t;

#endif /* TYPES_H */
