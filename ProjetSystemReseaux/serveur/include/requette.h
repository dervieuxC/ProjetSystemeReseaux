#ifndef REQUETTE_H
#define REQUETTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonction.h"

typedef struct Requette{
	int cmd;
	int cmdTrie;
	char ville_depart[100];
	char ville_arrive[100];
	char horaire_min[10];
	char horaire_max[10];
} Requette;

typedef Requette* PRequette;

void newRequette(PRequette* req, int num, int numTrie, char vD[], char vA[], char hD[], char hA[]);

void lireSocket(int socket, PRequette* req, int tailleBuffer);

void afficheReq(PRequette req);

#endif