#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]) {

  char chaine[100];
  int sock;                /* descipteur de la socket locale */
  int err;                 /* code d'erreur */
  struct hostent    *host; /* description de la machine serveur */
  struct sockaddr_in addr; /* adresse de la socket du serveur */

  /* Verification des arguments */
  if (argc != 3) {
    printf("Usage: client nom_machine no_port\n");
    exit(1);
  }

  /* Creation d'une socket, domaine AF_INET, protocole TCP */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("Erreur a la creation de la socket");
    exit(1);
  }

  /* Initialisation de l'adresse de la socket */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(atoi(argv[2]));

  /* Recherche de l'adresse de la machine */
  host = gethostbyname(argv[1]);
  if (host == NULL) {
    printf("Erreur dans la recherche de l'adresse de la machine (gethostbyname)");
    exit(2);
  }

  /* Recopie de l'adresse IP */
  addr.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;

  /* Connection au serveur */
  err = connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
  if (err < 0) {
    perror("Erreur la connexion de la socket");
    exit(3);
  }
  
  /* Saisie de la chaine */
  printf("client: donner une chaine : ");
  scanf("%s", chaine );
  printf("client: envoi de \"%s\"\n", chaine);
   
  /* Envoi de la chaine */
  size_t len = strlen(chaine) + 1;
  err = send(sock, chaine, len, 0);
  if (err != len) {
    perror("client: erreur sur le send");
    shutdown(sock, 2);
    exit(4);
  }
  printf("client: envoi realise\n");

  /* 
   * Fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);

  return 0;
}
 

