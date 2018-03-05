/**
 * \class client.c
 * \file client.c
 * \brief Client main
 * \author
 * \version 1.0
 * \date 04/12/2017
 */

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

#include "interface.h"
#include "requette.h"

/**
 * \struct IN_ADDR
 * \brief Objet de type in_addr
 */
typedef struct in_addr IN_ADDR;

/**
* \fn void fctserveur (int sockdescr)
* \brief Comportement du client
* \param sockdescr numéro de la socker du client qui lui permet de fait le lien avec le serveur
* \return void
*/
void fctclient (int sockdescr){ 
	
// Fonction qui saisit une chaine de caractères au clavier et l'envoie 
// dans la socket;
	bool verifContinue = 1;
	while(verifContinue){

		//initialisation de la requette à NULL
		PRequette req = NULL;
		char* printBuffer = (char*) malloc(500);
		char buffer[500];
		int noCmdInte;
		int cmd2;


		newRequette(&req);
		//affichage de l'acceuil
		noCmdInte = premierInterface(req);
		//demande des valeurs que l'on a besoin pour la requette
		commandeInterface(noCmdInte,req);

		creationReq(req,printBuffer);

		strcpy(buffer, printBuffer);
		printf("\n%s\n",buffer);
		
		write(sockdescr,buffer,strlen(buffer)-1);
				
		// attente de la réponce
		char bufferlecture[1000];

		memset(&bufferlecture,'\0',strlen(bufferlecture));
		
		read(sockdescr,&bufferlecture,1000);

		printf("%s\n",bufferlecture);

		
		cmd2 = deuxiemeInterface(req);
		printf("%i\n",cmd2 );

		if(cmd2 < 0){
			printf("Fermeture de l'Application\n");
			exit(0);
		}else if(cmd2 == 0){
			creationReq(req,printBuffer);
			strcpy(buffer, printBuffer);
			write(sockdescr,buffer,sizeof(buffer)-1);
			char buffeurLectureBis[1000];
			memset(&buffeurLectureBis,'\0',strlen(buffeurLectureBis));
			read(sockdescr,&buffeurLectureBis,1000);
			printf("%s\n",buffeurLectureBis );
		}
		free(req);
		free(printBuffer);
	}
}

/**
* \fn int main(int argc, char **argv)
* \brief Point d'enter du client, Permet de se connecté au serveur 
* \param argc ndique simplement le nombre de chaînes de caractères sur lequel pointe argv
* \param argv argv pointe sur une chaîne de caractères qui sera le chemin de votre programme
* \return int
* 
* Attention !! exemple : "./client serv numero_de_port" !!
* Utilisation de argv[1] pour serveur et argv[2] pour ne numéro de port.
*
*/
int main(int argc, char **argv)
{
// Client : 
// récupère le nom du serveur et le numéro de port en arguments (si présents !), 
// demande la connexion au serveur, et effectue sa requête
// grâce à la fonction fctclient
	struct sockaddr_in s;
	struct hostent *h;
	//int fini = 1;

	int p = socket(AF_INET, SOCK_STREAM, 0);
	if(p == -1)
	{
		   perror("-Erreur d'ouverture du socket");
		   exit(1);
	}
	h = gethostbyname(argv[1]);

	s.sin_family = AF_INET;
	s.sin_addr = *(IN_ADDR *) h->h_addr;
	s.sin_port	= (htons(atoi(argv[2])));

	int conn = connect(p,(struct sockaddr *)&s,sizeof(s));
	if(conn == -1)
	{
		   perror("-Erreur d'ouverture connection");
		   exit(1);
	}
	fctclient(p);
	return 0;
}