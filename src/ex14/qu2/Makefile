# author: Julien Bernard
# date: 20 Jul 2010

FUNC_DIR=../../fonctions
FUNC_C=${FUNC_DIR}/fonctionsSocket.c
FUNC_H=$(FUNC_C:.c=.h)

CFLAGS=-Wall -O2 -I${FUNC_DIR}
LDFLAGS=

all: client server client.class server.class

client: client.c  ${FUNC_C} ${FUNC_H}
	gcc ${CFLAGS} $(LD_FLAGS) -o client client.c ${FUNC_C}

server: server.c  ${FUNC_C} ${FUNC_H}
	gcc ${CFLAGS} $(LD_FLAGS) -o server server.c ${FUNC_C}

client.class: client.java
	javac client.java

server.class: server.java
	javac server.java

clean:
	rm -f client server
	rm -f server.class client.class
