/**
 * \class train.c
 * \file train.c
 * \brief Serveur main
 * \author
 * \version 1.0
 * \date 04/12/2017
 *
 */

#include "train.h"

/**
* \fn void addTrain(PTrain* train, int num, char vD[], char vA[], char hD[], char hA[], float p, enum promotion Ppromo)
* \brief Permet de créer un train 
* \param train correspond à la liste de train où l'on doit ajouter le train que l'on veut
* \param num correspond au numero de nouveau train
* \param vD correspond à la ville de depart du nouveau train
* \param vA correspond à la ville d'arrivée du nouveau train
* \param hD correspond à l'horaire de départ du nouveau train
* \param hA correspond à l'horaire d'arrivée du nouveau train
* \param p correspond au prix du nouveau train
* \param Ppromo la valeur de l'enum du nouveau train
* \return void
* 
*/
void addTrain(PTrain* train, int num, char vD[], char vA[], char hD[], char hA[], float p, enum promotion Ppromo)
{
	PTrain tr = (PTrain) malloc(sizeof(Train));
	tr->numero = num;
	strcpy(tr->ville_depart,vD);
	strcpy(tr->ville_arrive,vA);
	strcpy(tr->horaire_depart,hD);
	strcpy(tr->horaire_arrive,hA);
	tr->prix = p;
	tr->temps_trajet = tempsTrajet(tr);
	tr->promo = Ppromo;
	tr->next = *train;
	*train = tr;
}

/**
* \fn void liberationMem(PTrain pt)
* \brief permet de libérer la mémoire d'un train
* \param le train au quel on veut libérer la mémoire
* \return void
* La fonction permet de libérer la mémoire du train envoyer en paramètre mais aussi de tout ceux qui sont lié à lui
*/
void liberationMem(PTrain pt)
{
	//Tant qu'il y a des trains
	while (pt != NULL)
	{
		PTrain train = pt->next;
		free(pt);
		pt = train;
	}
	//printf("Libération Mem\n");
}

/**
* \fn int compartoVille(PTrain trainList, PTrain* train, char param1[], char param2[])
* \brief permet de comparer les villes de départ ou d'arrivée
* \param trainList correspond à la liste de train à traiter
* \param train correspond à la nouvelle liste de train où sera mis les bons trains
* \param param1 correspond à "ville_depart" ou "ville_arrive" pour savoir quoi comparer
* \param param2 correspond à la ville entrer par l'utilisateur
* \return void
*/
void compartoVille(PTrain trainList, PTrain* train, char param1[], char param2[])
{
	int i =0;
	PTrain pt = trainList;
	//afficheTrain(trainList);
	//tant qu'il ya un train
	while (pt != NULL)
	{
		//si la valeur que la fonction equalVille est 1 alors la ville du train est égale à celle demander par l'utilisateur
		if( equalVille(pt,param1,param2))
		{
			//on place le train à la suite des autres
			i++;
			PTrain tr = (PTrain) malloc(sizeof(Train));
			*tr = *pt;
			tr->next = *train;
			*train = tr;
		}
		//train suivant
		pt = pt->next;
	}
}

/**
* \fn int equalVille(PTrain pt, char param1[],char param2[])
* \brief permet de verifier si les villes de passer en parmaètre sint équivalente
* \param pt correspond au train que l'on veut verifier
* \param param1 correspond à "ville_depart" ou "ville_arrive" pour savoir quoi comparer
* \param param2 correspond à la ville entrer par l'utilisateur
* \return int est considérer comme un bool
*/
int equalVille(PTrain pt, char param1[],char param2[]){
	int boole = 0;
	char mot1[20];
	char mot2[20];
	//si le paramètre (param1) est ville_depart
	if(strcmp(param1,"ville_depart") == 0)
	{
		//on met la ville de départ dans mot1
		sprintf(mot1,"%s%c",pt->ville_depart,'\0');
	}
	//si le paramètre (param2) est ville_arrive
	else if(strcmp(param1,"ville_arrive") == 0)
	{
		//on met la ville d'arrive dans mot1
		sprintf(mot1,"%s%c",pt->ville_arrive,'\0');
		
	}
	//on met la ville demander par l'utilisateur dans mot2
	sprintf(mot2,"%s%c",param2,'\0');
	retireEspace(mot1);
	retireEspace(mot2);
	//on transforme les chaines en MAJUSCULE
	chaineEnMajuscule(mot1);
	chaineEnMajuscule(mot2);
	//printf("%i\n", (strcmp(mot1,mot2) == 0));
	return boole = (strcmp(mot1,mot2) == 0);;
}

/**
* \fn void init_train(PTrain* train, char uri_doc[], int taille_max_ligne)
* \brief Permet d'initialiser la liste de train
* \param train correspond à la liste des trains à initialiser
* \param uri_doc correspond à l'URI du document texte où sont stockés les trains
* \param taille_max_ligne correspond à la taille maximum d'une ligne que l'on peut lire
* \return void
* 
*/
void init_train(PTrain* train, char uri_doc[], int taille_max_ligne)
{
	int n , nbl = 0;
	char* ligne = (char*)malloc(taille_max_ligne * sizeof(char));
	char* tmpVal[7] = {"","","","","","",""};
	enum promotion promo;
	n = ouvertureFile(uri_doc);
	nbl = lireLigne(n,ligne);
	//tant que le nombre de ligne est supérieur à 0
	while( nbl > 0)
	{
		//permet de couper la ligne et de placer tout les éléments dans un tableau
		strtokBis(ligne,";",tmpVal);
		//si l'enum correspond à REDUC
		if (strcmp(tmpVal[6], "REDUC")==0)
		{
				promo = REDUC;
		}
		//si l'enum correspond à SUPPL
		else if( strcmp(tmpVal[6], "SUPPL")==0)
		{
				promo = SUPPL;
		}
		//si l'enum est nul donc il n'y a pas de promo
		else
		{
				promo = TN;
		}
		//printf("%i %s %s %s %s %f %s\n",atoi(tmpVal[0]), tmpVal[1], tmpVal[2], tmpVal[3],tmpVal[4], atof(tmpVal[5]),tmpVal[6]);
		addTrain(train, atoi(tmpVal[0]) , tmpVal[1], tmpVal[2], tmpVal[3],tmpVal[4], atof(tmpVal[5]), promo);
		nbl = lireLigne(n,ligne);
	}
	free(ligne);
}

/**
* \fn void listeTrainToString (PTrain listeTrainDemander, char* resultatClient)
* \brief Permet de transformer la liste de trains en chaine de caractères construites
* \param listeTrainDemander correspond à la liste des trains à envoyer au client
* \param resultatClient correspond au résultat construit par le client
* \return void
* 
*/
void listeTrainToString (PTrain listeTrainDemander, char* resultatClient)
{
	strcpy(resultatClient,"");

	//si la liste de train est vide on affiche que aucun train est disponible
	if(listeTrainDemander == NULL)
	{
		sprintf(resultatClient,"%s","aucun train correspond à votre demande");
	}
	//sinon 
	else
	{
		//Tant qu'il y a des trains
		while (listeTrainDemander != NULL)
		{
			//construction de l'affichage ( villeDepart heureDepart | villeArrive heureArrive | prix: prixTrajet)
			sprintf(resultatClient,"%s%s %s | %s %s | prix:%f%c",resultatClient,
														   		listeTrainDemander->ville_depart,
														   		listeTrainDemander->horaire_depart,
																listeTrainDemander->ville_arrive,
																listeTrainDemander->horaire_arrive,
																listeTrainDemander->prix,
																'\n');
			//passage au train suivant
			listeTrainDemander = listeTrainDemander->next;
		}
	}
	//ajoute un \0 à la fin du fichier qui permet de connaitre la fin du fichier
	sprintf(resultatClient,"%s%c",resultatClient,'\0');
}

/**
* \fn void triListeTrainPrix (PTrain trainList, PTrain* train)
* \brief Permet de trier les trains par rapport au prix et instancie un train
* \param trainList correspond à la liste des trains à trier
* \param train correspond au train le moins chere
* \return void
* 
*/
void triListeTrainPrix (PTrain trainList, PTrain* train)
{
	//initialisation des variables
	PTrain tmp, trainTemp;
	float min, temp1;
	min = trainList->prix;
	trainTemp = trainList;

	//printf("min = %f\n",min );
	//Pour tout les trains
	for(tmp=trainList ; tmp!=NULL ; tmp=tmp->next)
	{
		//initialisation d'une varible temporaire pour comparer les prix
		temp1 = tmp->prix;
     	//si le prix du train est inférieur au prix min courant
 		if(min > temp1)
 		{
 			//Si oui alors le minimum est la prix du train
        	min = temp1;
        	trainTemp = tmp;
    	}
	}
	//création du train qui possède le prix le plus bas
	PTrain tr = (PTrain) malloc(sizeof(Train));
	*tr = *trainTemp;
	tr->next = *train;
	*train = tr;
}

/**
* \fn void triListeTrainPromo(PTrain train)
* \brief permet d'effectuer la reduction et donc de remplacer le prix du train
* \param train correspond à la liste de trains (entière)
* \return void
* Change les prix des trains suivant si il y a une reduction un supplément ou rien
* Dans le cas d'un supplément le prix augmente de 10%
* Dans le cas d'une reduction le prix est diminué de 20%
*/
void triListeTrainPromo(PTrain train)
{
	PTrain pt = train;
	//Tant qu'il y a des trains
	while(pt!=NULL)
	{
		//Switch suivant la valeur de l'enum
		switch(pt->promo)
		{

			//cas au l'enum est égal à REDUC donc -20% sur le prix
			case REDUC:
				pt->prix = pt->prix -(pt->prix *20/100);
				//printf("%f\n",pt->prix);
				break;

			//cas ou l'enum es égal à SUPPL
			case SUPPL:
				pt->prix= pt->prix +(pt->prix *10/100);
				break;

			//cas par defaut quand il n'y a pas de reduction ou de supplément
			default:
			break;

		}
		pt = pt->next;
	}
	train = pt;
}


/**
* \fn void comparetoHoraireDepart(PTrain trainList,PTrain* train,char horaire Depart[])
* \brief Permet de comparer l'horaire de départ des trains avec celui entrer par l'utilisateur
* \param trainList correspond à la liste des trains à vérifier
* \param train correspond à la nouvelle liste qui contiendra les trains correspondent à l'horaire
* \param horaireDepart correspond à l'horaire de départ saisie par l'utilisateur
* \return void
*/
void comparetoHoraireDepart(PTrain trainList,PTrain* train,char horaireDepart[])
{
	int i =0;
	PTrain pt = trainList;
	//Tant qu'il y a des trains
	while (pt != NULL) 
	{
		printf("%s\n",pt->ville_depart);
		int verifEqual = 1;
		verifEqual = equalHoraireDepart(pt,horaireDepart);
		printf("%i\n",verifEqual );
		//si les horaires sont égales
		if( verifEqual == 1)
		{
			i++;
			//printf("i = %i\n",i );
			//ajout du bon train dans à la suite des autres
			PTrain tr = (PTrain) malloc(sizeof(Train));
			*tr = *pt;
			tr->next = *train;
			*train = tr;
		}
		//Train suivant
		pt = pt->next;
	}
}


/**
* \fn int equalHoraireDepart(PTrain pt,char horaireDepart[])
* \brief Permet de verifier si les horaires de départs sont égales
* \param pt liste de trains
* \param horaireDepart[] correspond à un tableau contenant l'horaire de départ saisie par l'utilisateur
* \return int qui correspond à un bool (0 si c'est faux et 1 si c'est vraie)
*/
int equalHoraireDepart(PTrain pt,char horaireDepart[])
{
 char* bufferHoraireDepart = (char*) malloc(500);
 char* bufferHoraireTrain = (char*) malloc(500);

 strcpy(bufferHoraireDepart,horaireDepart);
 strcpy(bufferHoraireTrain,pt->horaire_depart);

 char* token = ":";

 char* tableHoraireDepart[2];
 char* tableHoraireTrain[2];

 strtokBis(bufferHoraireDepart,token,tableHoraireDepart);
 strtokBis(bufferHoraireTrain,token,tableHoraireTrain);

 int heureDepart = atoi(tableHoraireDepart[0]);
 int minuteDepart = atoi(tableHoraireDepart[1]);
 int heureTrain = atoi(tableHoraireTrain[0]);
 int minuteTrain = atoi(tableHoraireTrain[1]);

 free(bufferHoraireDepart);
 free(bufferHoraireTrain);

 if (heureDepart == heureTrain)
 {
 	if(minuteDepart <= minuteTrain)
 	{
 		return 1;
 	}
 	else
 	{
 		return 0;
 	}
 }
 else if((heureDepart < heureTrain))
 {
 	return 1;
 }
 else
 {
 	return 0;
 }
}

/**
* \fn void comparetoTrancheHoraire(PTrain trainList,PTrain* train,char horaireMin[],char horaireMax[])
* \param trainList correspond 
* \param train correspond 
* \param horaireMin[] correspond à un tableau qui contient l'horaire min que l'utilisateur à saisie
* \param horaireMax[] correspond à un tableau qui contien l'horaire max que l'utilisateur à saisie
*/
void comparetoTrancheHoraire(PTrain trainList,PTrain* train,char horaireMin[],char horaireMax[])
{
	int i =0;
	PTrain pt = trainList;
	while (pt != NULL) 
	{
		//printf("%s\n",pt->ville_depart);
		int verifEqual = 1;
		verifEqual = equalTrancheHoraire(pt,horaireMin,horaireMax);
		//printf("%i\n",verifEqual );
		if( verifEqual == 1)
		{
			i++;
			//printf("i = %i\n",i );
			PTrain tr = (PTrain) malloc(sizeof(Train));
			*tr = *pt;
			tr->next = *train;
			*train = tr;
		}
		pt = pt->next;
	}
}


/**
* \fn int equalTrancheHoraire(PTrain pt,char horaireMin[], char horaireMax[])
* \brief
* \param pt correspond à un train qu'il faut verifier 
* \param horaireMin[] correspond à un tableau qui contient l'horaire Minimum saisie par l'utilisateur
* \param horaireMax[] correspond à un tableau qui contient l'horaire Maximum saisie par l'utilisateur
* \return int qui correspond à un bool (0 si l'egalité est fausse sinon renvoie 1)
*/
int equalTrancheHoraire(PTrain pt,char horaireMin[], char horaireMax[])
{
	
	//création de char* pour stocker les valeurs 
	char* bufferHoraireMin = (char*) malloc(500);
	char* bufferHoraireMax = (char*) malloc(500);
	char* bufferHoraireTrain = (char*) malloc(500);

	//on copie dans le buffer les valeurs correspondant à ce que l'on veut
	strcpy(bufferHoraireMin,horaireMin);
	strcpy(bufferHoraireMax,horaireMax);
	strcpy(bufferHoraireTrain,pt->horaire_depart);
	//printf("%s -- %s -- %s\n",bufferHoraireMin,bufferHoraireMax,bufferHoraireTrain);

	//création du token pour strtokBis
	char* token = ":";
	printf("token = %s\n",token );

	//création de tableau de char* pour stocker les heures et les minutes de chaque horaire
	char* tableHoraireMin[2];
	char* tableHoraireMax[2];
	char* tableHoraireTrain[2];

	//on coupe la chaine horaire lorsque l'on trouve un : ce qui signifie qu'il y a une separation entre heure et minute
	strtokBis(bufferHoraireMin,token,tableHoraireMin);
	strtokBis(bufferHoraireMax,token,tableHoraireMax);
	strtokBis(bufferHoraireTrain,token,tableHoraireTrain);

	printf("horaire min : %s -- %s \n",tableHoraireMin[0],tableHoraireMin[1]);
	printf("horaire max : %s -- %s\n",tableHoraireMax[0],tableHoraireMax[1]);
	printf("horaire train : %s -- %s\n",tableHoraireTrain[0],tableHoraireTrain[1]);


	//création des variable heure et minute de chaque horaire en int qui permet de les calculs et de les comparer
	int heureMin = atoi(tableHoraireMin[0]);
	int minuteMin = atoi(tableHoraireMin[1]);
	int heureMax = atoi(tableHoraireMax[0]);
	int minuteMax = atoi(tableHoraireMax[1]);
	int heureTrain = atoi(tableHoraireTrain[0]);
	int minuteTrain = atoi(tableHoraireTrain[1]);

	//desalocation des buffer
	free(bufferHoraireMin);
	free(bufferHoraireMax);
	free(bufferHoraireTrain);


	//printf("%i %i %i %i %i %i\n",heureMin,heureMax,heureTrain,minuteMin,minuteMax,minuteTrain );

	//si heure minimum est égale heure maximum et heure Minimum est égale à l'heure du train
	//alors heure Maximum est aussi égale à l'heure du train
	if ((heureMin == heureMax ) && (heureMin == heureTrain))
	{
		//si les minutes minimum sont égale aux minutes maximum et les minutes Minimum sont égale  aux minutes du train
		//alors les minutes Maximum est aussi égale aux minutes du train du train
		if((minuteMin <= minuteTrain) && (minuteMax >= minuteTrain))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if ((heureMin == heureTrain) && (minuteMin <= minuteTrain))
	{
		printf("bon\n");
		return 1;
	}
	if ((heureMax == heureTrain) && (minuteMax >= minuteTrain))
	{

		printf("bon\n");
		return 1;
	}
	if ((heureMin < heureTrain) &&  (heureMax > heureTrain))
	{
		printf("bon\n");
		return 1;
	}
	
	printf("pasBon\n");
	return 0;
	
}

/**
* \fn void afficheTrain(PTrain train) 
* \brief Permet d'afficher les trains
* \param train correspond à la liste d etrain à afficher
* \return void
* 
*/
void afficheTrain(PTrain train) 
{
	PTrain pt = train;
	while (pt != NULL ) 
	{
		printf("%i vD:%s vA:%s hD:%s hA:%s prix:%f temps:%f\n",pt->numero,
													  pt->ville_depart,
													  pt->ville_arrive,
													  pt->horaire_depart,
													  pt->horaire_arrive,
													  pt->prix,
													  pt->temps_trajet);
		pt = pt->next;
	}
}


/**
* \fn float tempsTrajet(PTrain pt) 
* \brief Permet de calculer le temps de trajet
* \param pt train sur le quel doit s'applique le calcule
* \return float qui correspond au temps du trajet (1,12 = 1h12min)
*/
float tempsTrajet(PTrain pt) 
{
	//int trajet;
	char* bufferDepart = (char*) malloc(500);
	char* bufferArrivee  = (char*) malloc(500);

	strcpy(bufferDepart,pt->horaire_depart);
	strcpy(bufferArrivee,pt->horaire_arrive);

	char* tableDepart[2];
	char* tableArrivee[2];

	strtokBis(bufferDepart,":",tableDepart);
	strtokBis(bufferArrivee,":",tableArrivee);

	int heureDepart = atoi(tableDepart[0]);
	int minuteDepart = atoi(tableDepart[1]);
	int heureArrive = atoi(tableArrivee[0]);
	int minuteArrivee = atoi(tableArrivee[1]);

	//printf("%i -- %i -- %i --%i\n",heureDepart,minuteDepart,heureArrive,minuteArrivee);
	
    int resultatHeure = heureArrive - heureDepart;
    int resultatMinute = minuteArrivee - minuteDepart;
 	
    if (resultatHeure < 0)
    {
    	resultatHeure = 24 + resultatHeure;
    	//printf("%i\n", resultatHeure);
    } 
    if (resultatMinute < 0)
    {
    	if (resultatHeure != 0)
    	{
    		resultatHeure = resultatHeure -1;
    	}
    	resultatMinute = 60 + resultatMinute;
    }
    float r = (float) resultatMinute;
	//moving the decimal point (.) to left most
    while( r > 1.0f ) r *= 0.1f; 
    r = (float)resultatHeure + r;
	//r = resultatHeure+(resultatMinute/100f);
	free(bufferDepart);
	free(bufferArrivee);
	return r;
    //printf("heure : %i -- minute : %i\n",resultatHeure,resultatMinute);
}

/**
*\fn void trajetOptimum(PTrain trainList, PTrain *train)
* \brief permet de renvoyer le train le plus rapide
* \param trainList correspond à la liste des trains à trier
* \param  train correspond à un nouveau train qui va prendre la valeur du train le plus rapide de la liste
* \return void
*/
void trajetOptimum(PTrain trainList, PTrain *train)
{
	PTrain tmp, trainTemp;
	float min, temp1;
	min = trainList->temps_trajet;
	trainTemp = trainList;
	//printf("min = %f\n",min );
	for(tmp=trainList ; tmp!=NULL ; tmp=tmp->next)
	{
		temp1 = tmp->temps_trajet;
 		if(min > temp1)
 		{
 			// le 3è temporaire est l'adresse de l'élement où se trouve le minimum
           min = temp1;
           trainTemp = tmp;
    	}
	}
	PTrain tr = (PTrain) malloc(sizeof(Train));
	*tr = *trainTemp;
	tr->next = *train;
	*train = tr;
}