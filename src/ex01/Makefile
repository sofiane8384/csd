# author: Julien Bernard
# created: 20 Jul 2010
# updated: 11 Feb 2012

FUNC_DIR=..
FUNC_C=$(FUNC_DIR)/fonctionsCommunication.c $(FUNC_DIR)/fonctionsSocket.c
FUNC_O=$(FUNC_C:.c=.o)

CFLAGS=-Wall -O2 -I$(FUNC_DIR)
LDFLAGS=

TARGETS=emetteur1 recepteur1 emetteur2 recepteur2

all: $(TARGETS)

emetteur1: $(FUNC_O)
recepteur1: $(FUNC_O)
emetteur2: $(FUNC_O)
recepteur2: $(FUNC_O)

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f $(FUNC_O)
