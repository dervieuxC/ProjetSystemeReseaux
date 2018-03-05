/**
 * \class requette.c
 * \file requette.c
 * \brief Serveur main
 * \author
 * \version 1.0
 * \date 04/12/2017
 *
 */

#include "requette.h"

/**
* \fn
* \brief
* \param
* \param
* \return 
* 
*/
void newRequette(PRequette* req){
	PRequette pr = (PRequette) malloc(sizeof(Requette));
	pr->cmd = 0;
	pr->cmdTrie = 0;
	strcpy(pr->ville_depart,"");
	strcpy(pr->ville_arrive,"");
	strcpy(pr->horaire_min,"");
	strcpy(pr->horaire_max,"");
	*req = pr;
}

// SETTERS
void setCmd(PRequette req, int cmdR){
	req->cmd = cmdR;
}

void setCmdTrie(PRequette req, int cmdT){
	req->cmdTrie = cmdT;
}

void setVilleDepart(PRequette req, char vD[]){
	strcpy(req->ville_depart , vD);
}

void setVilleArrive(PRequette req, char vA[]){
	strcpy(req->ville_arrive , vA);
}

void setHeureMin(PRequette req, char hMin[]){
	strcpy(req->horaire_min , hMin);
}

void setHeureMax(PRequette req, char hMax[]){
	strcpy(req->horaire_max , hMax);
}

/**
* \fn void creationReq(PRequette req, char* resultat)
* \brief
* \param
* \param
* \return void
* 
*/
void creationReq(PRequette req, char* resultat){
	sprintf(resultat,"%i;%i;%s;%s;%s;%s%c",req->cmd,
										   req->cmdTrie,
										   req->ville_depart,
										   req->ville_arrive,
										   req->horaire_min,
										   req->horaire_max,
										   '\0');
}