EXT = c
CC = gcc
EXEC = client

CFLAGS = -Wall -Iinclude
LDFLAGS = 

BINDIR = bin
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.$(EXT))
OBJ = $(SRC:$(SRCDIR)/%.$(EXT)=$(BINDIR)/%.o)

all: $(EXEC)
 
.PHONY: help clean mrproper

help:
	@ echo 'Makefile `$(EXEC)`'
	@ echo ''
	@ echo 'Usage :'
	@ echo 'make           Build project executable'
	@ echo 'make all       Build project executable'
	@ echo 'make clean     Clean objects directory'
	@ echo 'make mrproper  Remove objects and binaries directory'
	@ echo 'make help      Show this help message'
	@ echo ''

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
 
$(BINDIR)/%.o: $(SRCDIR)/%.$(EXT)
	@$(CC) -o $@ -c $< $(CFLAGS)
 
clean:
	@rm -rf $(BINDIR)/*.o
	@rm -f $(EXEC)