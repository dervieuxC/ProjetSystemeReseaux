#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#include "fonction.h"
#include "requette.h"

int premierInterface(PRequette req);

bool verifCmdValide(int verifAFaire);

void commandeInterface(int cmd, PRequette req);

void saisieVilleDepart(char *villeDepart);

void saisieVilleArrivee(char *villaArrivee);

void saisieHoraireDepart(char *horaireDepart);

void saisieTrancheHoraire(char *trancheHoraireMin, char* trancheHoraireMax);

int deuxiemeInterface(PRequette req);

void resultatinterface(int socket, char* chaineResultat, int taille_max_ligne);

int viderBuffer(int repScanf);


#endif