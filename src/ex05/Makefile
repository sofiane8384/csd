# author: Julien Bernard
# created: 20 Jul 2010
# updated: 11 Feb 2012

FUNC_DIR=..
FUNC_C=$(FUNC_DIR)/fonctionsCommunication.c $(FUNC_DIR)/fonctionsSocket.c
FUNC_O=$(FUNC_C:.c=.o)

CFLAGS=-Wall -O2 -I$(FUNC_DIR)
LDFLAGS=

TARGETS=client1 serveur1 client2 serveur2 client3 serveur3 client4 serveur4

all: $(TARGETS)

client1: $(FUNC_O)
serveur1: $(FUNC_O)
client2: $(FUNC_O)
serveur2: $(FUNC_O)
client3: $(FUNC_O)
serveur3: $(FUNC_O)
client4: $(FUNC_O)
serveur4: $(FUNC_O)

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f $(FUNC_O)
