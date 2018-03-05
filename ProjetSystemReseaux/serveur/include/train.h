#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "fonction.h"

enum promotion {REDUC,SUPPL,TN};

typedef struct Train{
	int numero;
	char ville_depart[100];
	char ville_arrive[100];
	char horaire_depart[10];
	char horaire_arrive[10];
	float prix;
	float temps_trajet;
	enum promotion promo;
	struct Train *next;
} Train;

typedef Train* PTrain;

void addTrain(PTrain* train, int num, char vD[], char vA[], char hD[], char hA[], float p, enum promotion Ppromo );

void liberationMem(PTrain pt);

void compartoVille(PTrain trainList, PTrain* train, char param1[], char param2[]);

int equalVille(PTrain p, char param1[],char param2[]);

void init_train(PTrain* train, char uri_doc[], int taille_max_ligne);

void triListeTrainPrix (PTrain trainList, PTrain* train);

void triListeTrainPromo(PTrain train);

void listeTrainToString (PTrain listeTrainDemander, char* resultatClient);

void comparetoTrancheHoraire(PTrain trainList,PTrain* train,char horaireMin[],char horaireMax[]);

int equalTrancheHoraire(PTrain pt,char horaireMin[], char horaireMax[]);

void comparetoHoraireDepart(PTrain trainList,PTrain* train, char horaireDepart[]);

int equalHoraireDepart(PTrain pt, char horaireDepart[]);

void afficheTrain(PTrain train);

float tempsTrajet(PTrain pt);

void trajetOptimum(PTrain trainList, PTrain *train);

void setTempsTrajet(PTrain train, float tempsTrajet);

#endif