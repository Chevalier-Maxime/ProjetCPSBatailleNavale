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
/*1 si ok ; 0 sinon*/
int complet(grille g,int n)
{
	int porte_avion =  NB_PORTE_AVION;
    int croiseur =  NB_CROISEUR;
	int contre_torpilleur = NB_CONTRE_TORPILLEURS;
	int torpilleur = NB_TORPILLEURS;
	
	int tab_est_passe[n][n];
	
	int taille = 0;
	int i,j,k;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	tab_est_passe[i][j]=0;}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if((!tab_est_passe[i][j])&&(g[i][j]==COLORIER))
			{
				taille++;
				tab_est_passe[i][j] = 1;//on coche la case
				
				if((j+1<n)&&(g[i][j+1]==COLORIER))//horizontale
				{
					
					if((i+1<n)&&(g[i+1][j+1]==COLORIER)){printf("Les bateaux sont colles\n");return 0;}//bateau collé
					
					taille++;
					tab_est_passe[i][j+1] = 1;//on coche la case
					
					for(k = j+2;g[i][k]==COLORIER;k++)
					{
						if((i+1<n)&&(g[i+1][k]==COLORIER)){printf("Les bateaux sont colles\n");return 0;}//bateau collé
						
						tab_est_passe[i][k] = 1;
						taille++;
					}
				}
				else if((i+1<n)&&(g[i+1][j]==COLORIER))//verticale
				{
					if((j+1<n)&&(g[i+1][j+1]==COLORIER)){printf("Les bateaux sont colles\n");return 0;}//bateau collé
					taille++;
					tab_est_passe[i+1][j] = 1;//on coche la case
					
					for(k = i+2;g[k][j]==COLORIER;k++)
					{
						if((j+1<n)&&(g[k][j+1]==COLORIER)){printf("Les bateaux sont colles\n");return 0;}//bateau collé
						tab_est_passe[k][j] = 1;
						taille++;
					}
				}
				switch(taille)
				{
					case T_TORPILLEURS : 		if(torpilleur>0){torpilleur--;}
												else{printf("Trop de torpilleur\n");return 0;}//erreur bateau
												break;
					
					case T_CONTRE_TORPILLEURS : if(contre_torpilleur>0){contre_torpilleur--;}
												else{printf("Trop de contre torpilleur\n");return 0;}//erreur bateau
												break;
					
					case T_CROISEUR : 			if(croiseur>0){croiseur--;}
												else{printf("Trop de croisseur\n");return 0;}//erreur bateau
												break;
					
					case T_PORTE_AVION : 		if(porte_avion>0){porte_avion--;}
												else{printf("Trop de porte avion\n");return 0;}//erreur bateau
												break;
					default : printf("Erreur taille\n");return 0;//erreur de taille
				}
				taille = 0;
			}
		}
	}
	
	if(porte_avion+croiseur+contre_torpilleur+torpilleur!=0){printf("Bateau manquants\n");return 0;}
	return 1 ;
}

int remplir_grille(grille g,int n)
{
	FILE* fichier = ouvrir_fichier();
	int i,j;
	char findechaine = fgetc(fichier);
	
	printf("On rempli la grille\n");
	while(findechaine!='f')
	{
		if(findechaine=='(')
		{
			fscanf(fichier,"%d",&i);//Lire i
			findechaine = fgetc(fichier);//Lire ;
			if(findechaine==';')
			{ 
				fscanf(fichier,"%d",&j);//Lire j
				findechaine = fgetc(fichier);//Lire )
			}
			else{printf("Le fichier est mal formé :(i1,j1)...(ik,jk)");break;}
		 }
		 else
		 {printf("Le fichier est mal formé :(i1,j1)...(ik,jk)");break;}
		 findechaine = fgetc(fichier);//Lire ( ou EOF
		 if(g[i][j] == COLORIER)
		 {
			 printf("Des bateaux se supperposent. Vous devez changer de fichier");
			 break;
		 }
		 else{g[i][j] = COLORIER;}
	}
	fclose(fichier);
	return complet(g,n);
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

