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

void newRequette(PRequette* req);

void setCmd(PRequette req, int cmdR);

void setCmdTrie(PRequette req, int cmdT);

void setVilleDepart(PRequette req, char vD[]);

void setVilleArrive(PRequette req, char vA[]);

void setHeureMin(PRequette req, char hMin[]);

void setHeureMax(PRequette req, char hMax[]);

void creationReq(PRequette req, char* resultat);

#endif