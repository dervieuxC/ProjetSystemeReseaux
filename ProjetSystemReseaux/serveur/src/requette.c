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
* \fn void newRequette(PRequette* req, int num, int numTrie, char vD[], char vA[], char hD[], char hA[])
* \brief Permet de créer une nouvelle instance de requette
* \param req correspond 
* \param num correspond au numéro de la requette (1 2 ou3)
* \param  numTrie correspond au numéro de commande de trie ( 1 ou 2)
* \param vD correspond à la ville de départ envoyer par l'utilisateur
* \param vA correspond à la ville d'arrivée envoyer par l'utilisateur
* \param hD correspond à l'horaire minimum où l'utilisateur veut partire
* \param hA correspond à l'horaire maximum où l'utilisateur veut partire
* \return void
* 
*/
void newRequette(PRequette* req, int num, int numTrie, char vD[], char vA[], char hD[], char hA[]){
	PRequette pr = (PRequette) malloc(sizeof(Requette));
	pr->cmd = num;
	pr->cmdTrie = numTrie;
	strcpy(pr->ville_depart,vD);
	strcpy(pr->ville_arrive,vA);
	strcpy(pr->horaire_min,hD);
	strcpy(pr->horaire_max,hA);
	*req = pr;
}

/**
* \fn void lireSocket(int socket, PRequette* req, int tailleBuffer)
* \brief Permet de lire la socket et donc de recupérer les infos envoyer par l'utilisateur
* \param socket correspont au numéro de socket du fils
* \param req correspond à la variable req où l'on doit stocker ces information
* \param tailleBufer correspond à la taille du buffer
* \return void
* 
*/
void lireSocket(int socket, PRequette* req, int tailleBuffer){
	char* buffer = (char*)malloc(tailleBuffer * sizeof(char));
	char* tmpVal[7] = {"","","","","","",""};
	int n ;
	n = read(socket, buffer, (tailleBuffer)-1);
	// si le read trouve quelque chose
	if(n > 0){
		//printf("buffer = '%s'\n",buffer );
		strtokBis(buffer,";",tmpVal);
		//printf("%s - %s - %s - %s - %s - %s\n",tmpVal[0],tmpVal[1],tmpVal[2],tmpVal[3],tmpVal[4], tmpVal[5]);
		newRequette(req, atoi(tmpVal[0]),atoi(tmpVal[1]),tmpVal[2],tmpVal[3],tmpVal[4], tmpVal[5]);
	}
	free(buffer);
}

/**
* \fn void afficheReq(PRequette req)
* \brief permet d'afficher la requette
* \param req correspond à la requette que l'on veut affiche
* \return void
*/
void afficheReq(PRequette req){
	printf(" %s | %s | %s | %s\n",req->ville_depart, req->ville_arrive,req->horaire_min,req->horaire_max );
}