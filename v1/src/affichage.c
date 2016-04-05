#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"


void affiche_jeu (grille g, int taille)
{
	printf("\nLe joueur J1 a place ses navires, etat de sa grille :\n");
	printf("  ");
	int i,j;
	//premiere ligne (numero colones)
	for(i=0;i<taille;i++)
	{
		printf("  %d",i);
	}
	printf("\n ");
	
	for(i=0;i<taille;i++)
	{
		printf("%d",i);
		for(j=0;j<taille;j++)
		{
			if((g[i][j]==COLORIER))
			{
				printf("  N");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n ");
	}
	
}

void affiche_etat_coules(grille g, int taille)
{
	printf("\nLe joueur J2 a lance ses torpilles, etat de sa grille :\n");
	printf("  ");
	int i,j;
	//premiere ligne (numero colones)
	for(i=0;i<taille;i++)
	{
		printf("  %d",i);
	}
	printf("\n");
	
	for(i=0;i<taille;i++)
	{
		printf(" %d",i);
		for(j=0;j<taille;j++)
		{
			if(g[i][j]!=BLANC)
			{
				printf("  %c", g[i][j]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}	
}

