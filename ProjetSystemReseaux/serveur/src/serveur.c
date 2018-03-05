/**
 * \class serveur.c
 * \file serveur.c
 * \brief Serveur main
 * \author
 * \version 1.0
 * \date 04/12/2017
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <netdb.h>

#include "fonction.h"
#include "requette.h"
#include "train.h"
#include "action.h"

#define TAILLE_MAX_SOCKET_RECV 1024
#define TAILLE_MAX_SOCKET_SEND 2024
#define URI_DOC "../doc/Trains.txt"
#define TAILLE_MAX_LIGNE 1024

PTrain pt = NULL;

/**
* \fn void fctserveur (int sockdescr)
* \brief Comportement des flis du serveur qui interagissent avec leur client connecté
* \param sockdescr numéro de la socker de sevice du fils qui permet de fait le lien avec son client associés
* \return void
*/
void fctserveur (int sockdescr)
{ 
	//Tant que le fils que le client est connecté
	while(1)
	{
		char* resultatClient = (char*) malloc(500);
		PRequette req = NULL;
		//Permet de lire le client et de construire la requette
		lireSocket(sockdescr,&req,TAILLE_MAX_SOCKET_RECV);
		afficheReq(req);

		//traitement de la demande
		redirection(req,pt,resultatClient);

		// envoie de la rémponse au client
		char buffer[255];
		strcpy(buffer, resultatClient);
		printf("-%s-\n", buffer);
		// ecrit le resultat construit dans la socket pour l'envoyer au client
		write(sockdescr,buffer,strlen(buffer)-1);
		free(req);
		free(resultatClient);
	}
}

/**
* \fn void finfils(int sig)
* \brief Handler qui permet de récupérer le signal SIGCHLD pour la mort d'un fils
* \param sig est le numéro de signal
* \return void
*/
void finfils(int sig)
{
// Handler pour la réception de SIGCHLD
	printf("\nFermeture de connection\n");
	wait(NULL);
	
}

/**
* \fn int main(int argc, char **argv)
* \brief Point d'enter du serveur, Permet d'attendre la connection de client
* \param argc ndique simplement le nombre de chaînes de caractères sur lequel pointe argv
* \param argv argv pointe sur une chaîne de caractères qui sera le chemin de votre programme
* \return int
*/
int main(int argc, char **argv)
{
	//Création des trains 
	init_train(&pt,URI_DOC,TAILLE_MAX_LIGNE);
	triListeTrainPromo(pt);

	//--------------------------------------------
	// structures pour la socket d'écoute et la socket de service :
	struct sockaddr_in s, service;

	struct sigaction a;
	a.sa_handler = finfils;
	a.sa_flags = SA_RESTART;
	sigaction(SIGCHLD,&a,NULL);


	// déclarations des autres variables nécessaires : 
	//strutcture pour la socket d'ecoute et la socket de service :
	s.sin_family = AF_INET;
	// récupère le numéro de port en argument (si présent !), se met en état de 
	// recevoir des requêtes de clients, et sert chaque requête grâce à la 
	// fonction fctserveur ATTENTION ICI Num_port 2000 M prendre celui en paramètre
	s.sin_port	=(htons(atoi(argv[1])));
	s.sin_addr.s_addr = htonl(INADDR_ANY);

	// *** CREATION de socket d'écoute *** //	
	int sock_ecoute;
	sock_ecoute = socket(AF_INET, SOCK_STREAM, 0);

	//Vérification de la création de la socket d'écoute
	if(sock_ecoute == -1)
	{
		   perror("-Erreur d'ouverture du socket");
		   exit(errno);
	}
	//Attachement de la socket
	if(bind(sock_ecoute, (struct sockaddr *) &s, sizeof(s)) < 0)
	{
		   perror("-Erreur d'association au port");
		   exit(errno);
	}
	//Ouverture du service
	int l= listen(sock_ecoute,5);
	if(l == -1)
	{
		   perror("-Erreur d'ouverture du service listen");
		   exit(errno);
	}

	// boucle infinie
	while(1)
	{
		//int sock_service = socket(AF_INET, SOCK_STREAM, 0);
		//Acceptation d'une connexion 
		int taille_service = sizeof(service);
		int socket_service = accept(sock_ecoute,(struct sockaddr *)&service,(unsigned int *) &taille_service);
		//si il y a une erreur au niveau de la socket de service
		if (socket_service == -1)
		{
				perror("-Erreur de la fonction accept");
				exit(0);
			}
		//création d'un fils
		switch(fork())
		{
			//si il ya une erreur
			case-1:
				perror("-Prblème avec le fork");
				exit(errno);

			//si c'est le fils
			case 0:
				fctserveur(socket_service);
				exit(0);
			
				//break;
			default:
				//on ferme la socket de service car le père ne touchera jamais à celle ci
				close(socket_service);
				break;
		}			
	}

	return 0;
}