# author: Julien Bernard
# date: 20 Jul 2010

FUNC_DIR=../../fonctions
FUNC_C=${FUNC_DIR}/fonctionsSocket.c
FUNC_H=$(FUNC_C:.c=.h)

CFLAGS=-Wall -O2 -I${FUNC_DIR}
LDFLAGS=

all: client serveur

client: client.c  ${FUNC_C} ${FUNC_H}
	gcc ${CFLAGS} $(LD_FLAGS) -o client client.c ${FUNC_C}

serveur: serveur.c  ${FUNC_C} ${FUNC_H}
	gcc ${CFLAGS} $(LD_FLAGS) -o serveur serveur.c ${FUNC_C}

clean:
	rm -f client serveur
