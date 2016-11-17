# author: Julien Bernard
# created: 20 Jul 2010
# updated: 11 Feb 2012

FUNC_DIR=..
FUNC_C=$(FUNC_DIR)/fonctionsCommunication.c $(FUNC_DIR)/fonctionsSocket.c
FUNC_O=$(FUNC_C:.c=.o)

CFLAGS=-Wall -O2 -I$(FUNC_DIR)
LDFLAGS=

TARGETS=emetteur0 recepteur0 client0 serveur0 emetteur1 recepteur1 client1 serveur1 emetteur2 recepteur2 client2 serveur2 emetteur3 recepteur3 client4 serveur4

all: $(TARGETS)

emetteur0: $(FUNC_O)
recepteur0: $(FUNC_O)
client0: $(FUNC_O)
serveur0: $(FUNC_O)
emetteur1: $(FUNC_O)
recepteur1: $(FUNC_O)
client1: $(FUNC_O)
serveur1: $(FUNC_O)
emetteur2: $(FUNC_O)
recepteur2: $(FUNC_O)
client2: $(FUNC_O)
serveur2: $(FUNC_O)
emetteur3: $(FUNC_O)
recepteur3: $(FUNC_O)
client4: $(FUNC_O)
serveur4: $(FUNC_O)

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f $(FUNC_O)
