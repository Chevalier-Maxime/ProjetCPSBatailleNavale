#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"

#define TAILLE_NOM_FICHIER 256


FILE* ouvrir_fichier()
{
	char nomFichier[TAILLE_NOM_FICHIER];

	printf("Quel est votre nom de fichier?");
	scanf("%s",nomFichier);
	return fopen(nomFichier,"r");
}

int complet(grille g,int n)
{
	int porte_avion =  1;
    int croiseur =  2;
	int contre_torpilleur = 3;
	int torpilleur = 4;
	int tab_est_passe[n][n];
	int taille = 0;
	
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			tab_est_passe[i][j]=0;
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if((!tab_est_passe[i][j])&&(g[i][j]==COLORIER))//Si la case est colo
			{
				taille++;//le bateau à une taille de 1
				tab_est_passe[i][j] = 1;//on coche la case
				if((j+1<n)&&(g[i][j+1]==COLORIER))//horizontale
				{
					taille++;//le bateau a une taille de 2
					tab_est_passe[i][j+1] = 1;//on coche la case
					for(k = j+1;g[i][k]==COLORIER;k++)
					{
						tab_est_passe[i][k] = 1;
						taille++;
					}
				}
				if((i+1<n)&&(g[i+1][j]==COLORIER))//verticale
				{
					taille++;//le bateau a une taille de 2
					tab_est_passe[i+1][j] = 1;//on coche la case
					for(k = i+1;g[k][j]==COLORIER;k++)
					{
						tab_est_passe[k][j] = 1;
						taille++;
					}
				}
				
			}
		}
	}
	
	
	
	
	
	return porte_avion+croiseur+contre_torpilleur+torpilleur ;
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
		if(complet(n)){estRempli = 1;}
	}
}

void initialiser_grillle(grille g, int n)
{
	
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			g[i][j]=BLANC;
	}
		
}



