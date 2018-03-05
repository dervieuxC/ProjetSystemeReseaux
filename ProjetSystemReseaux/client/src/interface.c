#include "interface.h"
#define HORAIRE 10
#define TRANCHE_HORAIRE 20
#define TAILLE_NOM_VILLE 100
#define TAILLE_CHAINE 500
#define TAILLE_BUFFER_CLEAN 500
/**
* \fn int premierInterface() 
* \brief affiche la première interface
* \param req correspond à la requette qui est initialiser à vide
* \return un entier qui correspond à la commande choisi
* Propose à l'utilisateur des commandes réalisable par le serveur et lui demande laquel il veut executer
*/
int premierInterface(PRequette req) 
{
	//Declaration des variables
	bool verifCmd = 0;
	int maCmdSelec;
	int scanfTrue;
	while (verifCmd == 0)
	{
		//Affichage de l'acceuil
		printf(" -------------------------------------------------------------------------- \n");
		printf(" | Bienvenue sur l'application                                            | \n");
		printf(" | >  1 - Voir tous les trajets entre deux villes à partire d'un horaire  | \n");
		printf(" | >  2 - Voir tous les trajets entre deux villes entre deux horaires     | \n");
		printf(" | >  3 - Voir Tous les trajets entre deux villes                         | \n");
		printf(" -------------------------------------------------------------------------- \n");
		printf("veuillez choisir le numero de la commande que vous voulez executer\n");
		scanfTrue = scanf("\n%d",&maCmdSelec);
		//si la saisie est valide
		if(viderBuffer(scanfTrue))
		{
			//Permet de verifier si la commande est valide on sort de la boucle  sinon on continue de boucler sur la demande de commande
			verifCmd = verifCmdValide(maCmdSelec);
		}
	}
	setCmd(req,maCmdSelec);
	return maCmdSelec;
}

/**
* \fn int deuxiemeInterface()
* \brief deuxieme interface qui permet recuperer le choix de l'utilisateur
* \param  req correspond à la requette
* \return int qui represente la commande selectionner par l'utilisateur
*/
int deuxiemeInterface(PRequette req)
{	
	bool verifCmdSelec = 0;
	int cmdSelec;
	int scanfTrue;
	while(verifCmdSelec == 0)
	{
		printf(" --------------------------------------------------------------------- \n");
		printf(" | > 1 - Faire une nouvelle requete                                  | \n");
		printf(" | > 2 - Trier la liste de train par rapport au meilleur prix        | \n");
		printf(" | > 3 - Trier la liste de train par rapport au trajet le plus court | \n");
		printf(" | > 4 - Quitter                                                     | \n");
		printf(" --------------------------------------------------------------------- \n\n");
		printf("veuillez choisir le numero de la commande que vous voulez executer\n");
		scanfTrue = scanf("\n%d",&cmdSelec);
		if(viderBuffer(scanfTrue))
		{
			// condition de sortie
			if (cmdSelec == 4)
			{
				return -1;
			}
			// nouvelle requette
			else if(cmdSelec == 1)
			{
				return 1;
			}
			else
			{
				verifCmdSelec = verifCmdValide(cmdSelec);
			}	
		}
		
	}
	setCmdTrie(req,cmdSelec-1);
	return 0;
}

/**
*\fn bool verifCmdValide(int verifAFaire) 
*\brief verifie si la commande est valide
*\param la valeur entrer lors du scanf
*\return bool vraie si la commande entrer es valide sinon renvoie 0 donc faux
*/
bool verifCmdValide(int verifAFaire) 
{
	// si la commande est valide
	if (verifAFaire == 1 || verifAFaire == 2 || verifAFaire == 3) 
	{
		printf("commande bien prise en compte\n");			
		return 1;
	}
	//Sinon la commande n'est pas valide 
	else
	{
		printf("commande Invalide\n");
		printf("veuillez entrer une commande valide\n");
		return 0;
	}
}


/**
*\fn void commandeInterface(int valeurCommande, char *reponseRequete) 
*\brief permet de gerer la suite de l'interface apres selecion de la commande
*\param valeur de la commande choisie par l'utilisateur
*\param 
*\return void
* la fonction permet de changer la reponse qui est un string qui prend la forme (cmd;villeDepart;villeArrivee;horaireMin,horaireMax) 
* suivant la commande selectionner l'utilisateur ne devra pas entrer les même information
* 1 : villeDepart,villeArrive,horaireMin
* 2 : villeDepart,villeArrivee,trancheHoraire
* 3 : villeDepart,villeArrivee
*/
void commandeInterface(int cmd, PRequette req) 
{
	//declaration de char* qui permettent de stocker les données saisie par l'utilisateur
	char* villeDepart = (char*) malloc(TAILLE_NOM_VILLE);
	char* villeArrivee = (char*) malloc(TAILLE_NOM_VILLE);
	char* horaireMin = (char*) malloc(TRANCHE_HORAIRE);
	char* horaireMax = (char*) malloc(TRANCHE_HORAIRE);

	// switch qui choisie les infos à demander à l'utilisateur et qui les stock puis les concataine pour avoir une seule reponse
	switch(cmd)
	{

		// commande 1 qui est Voir tous les trajets entre deux villes à partire d'un horaire
		case 1:
			saisieVilleDepart(villeDepart);
			printf("valeur de la ville de départ: %s\n",villeDepart);
			saisieVilleArrivee(villeArrivee);
			printf("valeur de la ville d'arrivée: %s\n",villeArrivee);
			saisieHoraireDepart(horaireMin);
			printf("valeur de l'horaire de Depart: %s\n",horaireMin);
			strcpy(horaireMax,"");
			//concatenation
			//sprintf(reponseRequete,"%i;%s;%s;%s",valeurCommande,villeDepart,villeArrivee,horaire);
			break;

		// commande 2 qui est Voir tous les trajets entre deux villes entre deux horaires
		case 2: 
			saisieVilleDepart(villeDepart);
			printf("valeur de la ville de départ: %s\n",villeDepart);
			saisieVilleArrivee(villeArrivee);
			printf("valeur de la ville d'arrivée: %s\n",villeArrivee);
			saisieTrancheHoraire(horaireMin,horaireMax);
			printf("valeur de la tranche horraire: %s:%s\n",horaireMin,horaireMax);
			//concatenation
			//sprintf(reponseRequete,"%i;%s;%s;%s",valeurCommande,villeDepart,villeArrivee,horaire);
			break;

		// commande 3 qui est Voir Tous les trajets entre deux villes
		case 3:
			saisieVilleDepart(villeDepart);
			printf("valeur de la ville de départ: %s\n",villeDepart);
			saisieVilleArrivee(villeArrivee);
			printf("valeur de la ville d'arrivée: %s\n",villeArrivee);
			strcpy(horaireMin,"");
			strcpy(horaireMax,"");
			//concatenation
			//sprintf(reponseRequete,"%i;%s;%s",valeurCommande,villeDepart,villeArrivee);
			break;
	}

	//set les ville et les horaires dans la requette
	setVilleDepart(req,villeDepart);
	setVilleArrive(req,villeArrivee);
	setHeureMin(req,horaireMin);
	setHeureMax(req,horaireMax);

	// desalocation de la memoire pour les char* qui permettaient de stocker les infos entrer par l'utilisateur
	free(villeDepart);
	free(villeArrivee);
	free(horaireMin);
	free(horaireMax);

	//printf("%s\n",reponseRequete);
}

/**
* \fn void saisieVilleDepart(char *villeDepart)
* \brief permet de saisir la ville de départ
* \param villeDepart correspond au char à remplire avec la saisie
* \return void
*/
void saisieVilleDepart(char *villeDepart)
{
	printf("Veuillez entrer le nom de la ville de départ:\n");
	scanf("\n%[^\n]%*c",villeDepart);
}

/**
* \fn void saisieVilleArrivee(char *villeArrivee)
* \brief permet de saisir la ville d'arrivé
* \param villeArrivee correspond au char à remplire avec la saisie
* \return void
*/
void saisieVilleArrivee(char *villeArrivee)
{
	printf("Veuillez entrer le nom de la ville d'arrivée:\n");
	scanf("\n%[^\n]%*c",villeArrivee);
}

/**
* \fn void saisieHoraireDepart(char *horaireDepart)
* \brief permet de saisir l'horair de départ
* \param horaireDepart correspond au char à remplire avec la saisie
* \return void
*/
void saisieHoraireDepart(char *horaireDepart)
{
	int heureDepart;
	int minuteDepart;
	bool verifH = 0;
	bool verifMin= 0;
	int scanfTrue1, scanfTrue2;
	while(verifH == 0)
	{
		printf("Veuillez entrer l'heure où vous voulez partire(entre 0 et 23):\n");
		scanfTrue1 = scanf("\n%d",&heureDepart);
		if(viderBuffer(scanfTrue1)){
			verifH = verifHeure(heureDepart);
		}
	}
	while(verifMin == 0)
	{
		printf("Veuillez entrer les minutes où vous voulez partire(entre 0 et 59):\n");
		scanfTrue2 = scanf("\n%d",&minuteDepart);
		if(viderBuffer(scanfTrue2)){
			verifMin = verifMinute(minuteDepart);
		}
	}
	sprintf(horaireDepart,"%i:%i",heureDepart,minuteDepart);
}

/**
* \fn void saisieTrancheHoraire(char *trancheHoraire)
* \brief permet de saisir les tranches horaire
* \param trancheHoraireMin correspond au char à remplire avec la saisie
* \param trancheHoraireMax correspond au char à remplire avec la saisie
* \return void
*/
void saisieTrancheHoraire(char *trancheHoraireMin, char* trancheHoraireMax)
{
	int heureTrancheUn;
	int minuteTrancheUn;
	int heureTrancheDeux;
	int minuteTrancheDeux;
	bool verifH = 0;
	bool verifMin= 0;
	int scanfTrue1, scanfTrue2,scanfTrue3,scanfTrue4;
	//tant que l'utilisateur n'a pas entrer une valeur valide
	while(verifH == 0)
	{
		printf("Veuillez entrer l'heure minimum où vous voulez partire(entre 0 et 23):\n");
		scanfTrue1 = scanf("\n%d",&heureTrancheUn);
		if(viderBuffer(scanfTrue1)){
			verifH = verifHeure(heureTrancheUn);
		}
	}
	//tant que l'utilisateur n'a pas entrer une valeur valide
	while(verifMin == 0)
	{
		printf("Veuillez entrer les minutes minimum où vous voulez partire(entre 0 et 59):\n");
		scanfTrue2 = scanf("\n%d",&minuteTrancheUn);
		if(viderBuffer(scanfTrue2)){
			//verification si les minute sont entre 0 et 59
			verifMin = verifMinute(minuteTrancheUn);
		}
	}

	//réinitialisation des variable de verification
	verifH = 0;
	verifMin = 0;

	//tant que l'utilisateur n'a pas entrer une valeur valide
	while (verifH == 0)
	{
		printf("Veuillez entrer l'heure maximum où vous voulez partire(entre 0 et 23):\n");
		scanfTrue3 = scanf("\n%d",&heureTrancheDeux);
		if(viderBuffer(scanfTrue3)){
			verifH = verifHeureBis(heureTrancheUn, heureTrancheDeux);
		}
	}
	//tant que l'utilisateur n'a pas entrer une valeur valide
	while (verifMin == 0)
	{
		printf("Veuillez entrer les minutes maximum où vous voulez partire(entre 0 et 59):\n");
		scanfTrue4 = scanf("\n%d",&minuteTrancheDeux);
		if(viderBuffer(scanfTrue4)){
			verifMin = verifMinuteBis(heureTrancheUn, heureTrancheDeux ,minuteTrancheUn,minuteTrancheDeux);
		}
	}

	//concatenation des heure et des minutes
	sprintf(trancheHoraireMin,"%i:%i",heureTrancheUn,minuteTrancheUn);
	sprintf(trancheHoraireMax,"%i:%i",heureTrancheDeux,minuteTrancheDeux);
}


/**
* \fn int viderBuffer(int repScanf)
* \brief permet de vider le buffer 
*
*/
int viderBuffer(int repScanf)
{
	char* tmpBuffer = (char*) malloc (TAILLE_BUFFER_CLEAN);
	scanf("%[^\n]",tmpBuffer);
	getchar();
	int resultat = 1;
	if ( repScanf != 1 )
	{
		printf("Error : %s\n",tmpBuffer );
		resultat = 0;
	}
	free(tmpBuffer);
	return resultat;
}