#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"


#define TAILLE_NOM_FICHIER 256

/**
 * Fonction permettant d'ouvrir un fichier en lecture
 * Bloquante quand on donne un mauvais nom de fichier
 * @return un pointeur sur le fichier
**/ 
FILE* ouvrir_fichier()
{
	char nomFichier[TAILLE_NOM_FICHIER];
	FILE* fichier;
	int dejaPasse = 0;
	int retester = 0;
	do{
		if(dejaPasse)
		{
			fprintf(stderr,"Ce fichier n'existe pas, pensez inclure l'extention si le fichier en possède une.\nPar exemple, tapez nomFichier.txt\n");
			printf("Essayer un autre fichier ? (1 = oui, 0 = non) ->  ");
			scanf("%d",&retester);
			if(!retester)
				{exit(0);}
		}
		printf("Quel est votre nom de fichier?  ");
		scanf("%s",nomFichier);
		fichier = fopen(nomFichier,"r");
		dejaPasse = 1;
	}while(fichier == NULL);
	return fichier;
}


/**
 * Teste si la grille du joueur 1 comporte le bon nombre de bateaux.
 * @param g : la grille du joueur 1 rempli
 * @param n : la taille de la grille
 * @return 1 si la grille est correctement rempli, 0 sinon
**/
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

/**
 * Remplie une grille a partir d'un fichier
 * @param g : la grille à remplir
 * @param n : la taille de la grille
 * @return 1 si on arrive à remplir la grille, quitte le programme sinon
**/
int remplir_grille(grille g,int n)
{
	FILE* fichier = ouvrir_fichier();
	int i,j;
	char findechaine;
	
	fscanf(fichier, "%d", &j);
	if(j == n)
	{
		findechaine = fgetc(fichier);
		
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
				else{printf("Le fichier est mal formé :(i1,j1)...(ik,jk)\n");exit(0);}
			 }
			 else
			 {printf("Le fichier est mal formé :(i1,j1)...(ik,jk)\n");exit(0);}
			 findechaine = fgetc(fichier);//Lire ( ou EOF
			 if(g[i][j] == COLORIER)
			 {
				 printf("Des bateaux se supperposent. Vous devez changer de fichier\n");
				 exit(0);
				 break;
			 }
			 
			 if((i<0)||(i>=n)||(j<0)||(j>=n))
			 {
				 printf("Les coordonées contenue dans le fichier ne correspondent pas à la grille\n");
				 exit(0);
				 break;
			 }
			 else{g[i][j] = COLORIER;}
		}
		fclose(fichier);
		if(complet(g,n)){return 1;}
		else{printf("Grille mal formées\n");
			 exit(0);}
	}
	else
	{printf("Le fichier ne correspond pas à ce type de grille\n");exit(0);}	
}

/**
 * Initialise une grille avec toutes les cases à BLANC
 * @param g : la grille a initialiser
 * @param n : la taille de la grille
**/
void initialiser_grille(grille g, int n)
{
	
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{	g[i][j]=BLANC;}
	}
		
}
