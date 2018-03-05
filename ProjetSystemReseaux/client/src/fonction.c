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
*\fn bool verifHeure(int heureSaisie)
*\brief
*\param heure saisie par l'utilisateur que l'on doit verifier
*\return bool
*/
bool verifHeure(int heureSaisie)
{
	if (heureSaisie >= 0 && heureSaisie < 24) 
	{
		printf("heure valide\n");
		return 1;
	}
	else
	{
		printf("heure non valide\n");
		return 0;
	}
}

/**
*\fn bool verifHeureBis(int heure1, int heureSaisie)
*\brief
*\param heure saisie par l'utilisateur que l'on doit verifier
*\return bool
*/
bool verifHeureBis(int heure1, int heureSaisie)
{
	if(verifHeure(heureSaisie)){
		if (heureSaisie >= heure1) 
		{
			printf("heure valide\n");
			return 1;
		}
		else
		{
			printf("heure non valide car doit être supprieur à :%i\n",heure1);
			return 0;
		}
	}else{
		return 0;
	}
	
}

/**
*\fn bool verifMinute(int minuteSaisie)
*\brief
*\param minute sasie par l'utilisateur que l'on doit verifier
*\return bool
*/
bool verifMinute(int minuteSaisie)
{
	if (minuteSaisie >= 0 && minuteSaisie <60)
	{
		printf("minute valide\n");
		return 1;
	}
	else
	{
		printf("minute non valide\n");
		return 0;
	}
}

/**
*\fn bool verifMinuteBis(int heure1, int heure2 ,int minute1, int minuteSaisie)
*\brief
*\param heure saisie par l'utilisateur que l'on doit verifier
*\return bool
*/
bool verifMinuteBis(int heure1, int heure2 ,int minute1, int minuteSaisie)
{
	if(verifHeure(minuteSaisie)){
		if(heure1 == heure2){
			if (minuteSaisie > minute1) 
			{
				printf("minute valide\n");
				return 1;
			}
			else
			{
				printf("minute non valide car doit être supprieur à :%i\n",minute1);
				return 0;
			}
		}
		return 1;
		
	}else{
		return 0;
	}
	
}