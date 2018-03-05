export CC = gcc
export CFLAGS = -Wall
export LDFLAGS=
CLIENT_DIR = client
SERVEUR_DIR = serveur

all: 
	@(cd $(CLIENT_DIR) && $(MAKE))
	@(cd $(SERVEUR_DIR) && $(MAKE))

clean:
	@(cd $(CLIENT_DIR) && $(MAKE) $@)
	@(cd $(SERVEUR_DIR) && $(MAKE) $@)