# author: Julien Bernard
# created: 20 Jul 2010
# updated: 11 Feb 2012

FUNC_DIR=..
FUNC_C=$(FUNC_DIR)/fonctionsCommunication.c $(FUNC_DIR)/fonctionsSocket.c
FUNC_O=$(FUNC_C:.c=.o)

CFLAGS=-Wall -O2 -I$(FUNC_DIR)
LDFLAGS=

TARGETS=emetteur recepteur client serveurSelect serveurNB

all: $(TARGETS)

emetteur: $(FUNC_O)
recepteur: $(FUNC_O)
client: $(FUNC_O)
serveurSelect: $(FUNC_O)
serveurNB: $(FUNC_O)

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f $(FUNC_O)
