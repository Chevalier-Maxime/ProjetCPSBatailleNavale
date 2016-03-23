#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"

#define TAILLE_NOM_FICHIER 256
#define COLORIER 'N'

FILE* ouvrir_fichier()
{
	char nomFichier[TAILLE_NOM_FICHIER];

	printf("Quel est votre nom de fichier?");
	scanf("%s",nomFichier);
	return fopen(nomFichier,"r");
}

int complet()
{
	return 0;
}

void remplir(grille g,int n)
{
	FILE* fichier = ouvrir_fichier();
	int i,j;
	int estRempli = 0;
	char findechaine = fgetc(fichier);
	
	while(!estRempli)
	{
		printf("On rempli la grille");
		while(findechaine!=EOF)
		{
			if(findechaine=='(')
			{
				fscanf(fichier,"%d",&i);//Lire i
			    findechaine = fgetc(fichier);//on lit ;
			    if(findechaine==';')
				{ 
					fscanf(fichier,"%d",&j);//Lire j
					findechaine = fgetc(fichier);//Lire (
				}
				else{printf("Le fichier est mal formé :(i1,j1)...(ik,jk)");}
			 }
			 else
			 {printf("Le fichier est mal formé :(i1,j1)...(ik,jk)");}
			 if(g[i][j] == COLORIER)
			 {
				 printf("Des bateaux se supperposent. Vous devez changer de fichier");
				 break;
			 }
			 else{g[i][j] = COLORIER;}
		}
		if(complet()){estRempli = 1;}
	}
}



