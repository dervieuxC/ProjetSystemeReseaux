/**
 * \class action.c
 * \file action.c
 * \brief Serveur main
 * \author
 * \version 1.0
 * \date 04/12/2017
 *
 */

#include "action.h"

/**
* \fn void redirection(PRequette uneRequette, PTrain listeTrain, char* resultat)
* \brief Permet de choisir le traitement suivant la requette reçu
* \param uneRequette correspond à la requette envoyer par l'utilisateur
* \param listeTrain correspond à la liste des trains (entière)
* \return void
* Cette fonction permet de choisir les traitements grâce au parametre cmd et cmdTrie de la structure de requette
* Elle execute un trie sur tout les trains (ex: si la ville de depart du train correspond à celle demander)
*/
void redirection(PRequette uneRequette, PTrain listeTrain, char* resultat){
	//initialisation de la chaine resultat à vide
	strcpy(resultat,"");
	//initialisation des liste de trains que l'on a besoin lors de notre traitement
	PTrain listeIntermediaireVilleDepart = NULL;
	PTrain listeIntermediaireVilleArrive = NULL;
	PTrain listeIntermediaireHoraire = NULL;
	PTrain listeTrainClient = NULL;
	PTrain listeIntermediaireOrd = NULL;
	//Switch qui permet de savoir quel reponse le client veut recevoire 
	switch(uneRequette->cmd)
	{
		// le commande demande une ville de depart et d'arrivee et aussi une horaire de depart
		case 1:
			//printf("case 1\n");
			//comparaison des deux villes la ville de départ et la ville d'arrivée si il n'y a aucune correspondance alors la chaine est vide
			compartoVille(listeTrain,&listeIntermediaireVilleDepart,"ville_depart",uneRequette->ville_depart);
			compartoVille(listeIntermediaireVilleDepart,&listeIntermediaireVilleArrive,"ville_arrive",uneRequette->ville_arrive);
			//comparaison avec l'horaire de depart que souhaite le client
			comparetoHoraireDepart(listeIntermediaireVilleArrive,&listeIntermediaireHoraire,uneRequette->horaire_min);
			//Transfert du resultat dans une liste de train Final
			listeTrainClient = listeIntermediaireHoraire;
			afficheTrain(listeTrainClient);
			break;

		// le commande demande une ville de depart et d'arrivee et aussi une tranche horaire
		case 2:
			//printf("case 2\n");
			//comparaison des deux villes la ville de départ et la ville d'arrivée si il n'y a aucune correspondance alors la chaine est vide
			compartoVille(listeTrain,&listeIntermediaireVilleDepart,"ville_depart",uneRequette->ville_depart);	
			compartoVille(listeIntermediaireVilleDepart,&listeIntermediaireVilleArrive,"ville_arrive",uneRequette->ville_arrive);
			//comparaison de la tranche horaire entrée par le client (cad: départ entre 10h00 et 12h30)
			comparetoTrancheHoraire(listeIntermediaireVilleArrive,&listeIntermediaireHoraire,uneRequette->horaire_min,uneRequette->horaire_max);
			listeTrainClient = listeIntermediaireHoraire;
			afficheTrain(listeTrainClient);
			break;

		// le commande demande une ville de depart et d'arrivee 
		case 3:
			//printf("case 3\n");
			//comparaison des deux villes la ville de départ et la ville d'arrivée si il n'y a aucune correspondance alors la chaine est vide
			compartoVille(listeTrain,&listeIntermediaireVilleDepart,"ville_depart",uneRequette->ville_depart);	
			compartoVille(listeIntermediaireVilleDepart,&listeIntermediaireVilleArrive,"ville_arrive",uneRequette->ville_arrive);
			listeTrainClient = listeIntermediaireVilleArrive;
			afficheTrain(listeTrainClient);
			break;

		//cas default si cmd possede autre chose que 1 2 ou 3
		default:
			printf("Erreur dans le numéro de commande\n" );
	}

	//Deuxieme switch celui-ci permet de savoir si l'utilisateur veut recuperer juste le train le moins chere ou le plus rapide
	switch(uneRequette->cmdTrie)
	{
	
		//Dans ce cas le moins chere est demande	
		case 1 :
			//printf("case 1 de cmdTrie\n");
			//fonction qui permet de mettre dans un Train le train le moins chere
			triListeTrainPrix(listeTrainClient,&listeIntermediaireOrd);
			listeTrainClient = NULL;
			//afficheTrain(listeIntermediaireOrd);
			listeTrainClient = listeIntermediaireOrd;
			break;
	
		//Dans ce cas le plus rapide est demander
		case 2 :
			//printf("case 2 de Trie\n");
			//fonction qui permet de mettre dans un Train le train le plus rapide
			trajetOptimum(listeTrainClient,&listeIntermediaireOrd);
			listeTrainClient = NULL;
			//afficheTrain(listeIntermediaireOrd);
			listeTrainClient = listeIntermediaireOrd;
			break;

		default :
			break;
	}
	
	//transformation de la liste de train en char* avec une structure identique au fichier trains.txt
	listeTrainToString(listeTrainClient,resultat);
	printf("%s\n",resultat);
	//liberation memoire des listes de trains utiliser pour le traitements
	liberationMem(listeIntermediaireOrd);
	liberationMem(listeIntermediaireVilleDepart);
	liberationMem(listeIntermediaireVilleArrive);
	liberationMem(listeIntermediaireHoraire);
}

