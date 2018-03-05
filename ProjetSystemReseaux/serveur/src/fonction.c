/**
 * \class fonction.c
 * \file fonction.c
 * \brief Serveur main
 * \author
 * \version 1.0
 * \date 04/12/2017
 *
 */

#include "fonction.h"



/**
* \fn int ouvertureFile(char* localisation)
* \brief Méthode ouvre un document  
* \param localisation URI qui fait référence à l'emplacement du fichier à lire
* \return int qui permet de savoir si l'ouverture c'est bien dérouler
* 
*/
int ouvertureFile(char* localisation)
{
	 return (open(localisation, O_RDONLY));
}

/**
* \fn int lireLigne(int fd, char *ligne)
* \brief Méthode qui permet de lire une ligne d'un fichier
* \param fd descriteur de fichier
* \param ligne est un pointeur qui fait référence à la ligne en cour de lecture
* \return int nombre de carartère sur une ligne
*
* On considère les cararères \n pour le retour à la ligne et \0 pour la fin de fichier
* 
*/
int lireLigne(int fd, char *ligne)
{
	int i=0;
	int n;
	char car;
	while(1){
		// renvoie le nb de caractères dans la ligne
		n = read(fd, &car, 1);
		if (n < 0){
			perror("ERROR lecture depuis la socket");
			return -1;
		}else if (n == 0){  // eof
			return 0;
		}else if(car == '\0'){
				return 0;
			}
		else {
			if (car == '\n'){
				ligne[i++]='\0';
				return i;
			}else if(car == '\0'){
				return 0;
			}else{
				ligne[i++]=car;
			}
		}
	}
	return 0;
}



/**
* \fn void strtokBis(char buffer[],char* tok,char* tmpVal[])
* \brief méthode utilisant strtok, et qui permt de mettre tous ses découpe dans une liste de char*
*
* \param buffer c'est là chaine de carartaire pris en compte
* \param token est une liste de caratère prise en compte pour réaliser la découpe
* \param tmpVal est la list de char* que l'on retoune
* \return void
* 
*/
void strtokBis(char buffer[],char* token,char* tmpVal[]){
	int i = 0;
	char* element;	
	element = strtok(buffer,token);
	while( element != NULL){
		//chaque élement
		tmpVal[i] = element;
		//élément suivant
		element = strtok(NULL,token);
		i++;
	}
}

/**
*\fn void chaineEnMajuscule(char*chaine)
*\brief permet de transformer une chaine de caractere quelquonque en MAJUSCULE
*\param chaine correspond à la chaine à transformer
*return void
*/
void chaineEnMajuscule(char*chaine)
{
     int i=0;
 	//Pour tout les caractères
     for(i=0;chaine[i]!='\0';i++)
     {
          chaine[i]=toupper(chaine[i]);
     }
 }

 void retireEspace(char* chaine)
 {
 	int i;
 	int j = -1;
 	for(i = 0;chaine[i];i++)
 	{
 		if(chaine[i] != ' ')
 		{
 			chaine[++j] = chaine[i];
 		}
 	}
 	chaine[++j] = '\0';
 }
