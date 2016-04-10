/*
 * main.c
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"
#include "affichage.h"
#include "remplir.h"
#include "jouer.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Le programme doit etre execute de la facon suivante : BatailleNavale tailleGrille\nPar exemple, vous pouvez taper BatailleNavale 10\n");
		return 1;
	}
	
	//teste si l'argument donnant la taille commence au moins par un entier >10
	//valide : 10 ,10mfr : donne 10
	//invalide(retourne 0) : 0, 1, m10
	int taille = atoi(argv[1]);
	if(taille <10)
	{
		fprintf(stderr,"Veuillez saisir un entier valide ( >0 et compose de chiffres uniquement)");
		return 1;
	}
	
	int i;
	//alloue la grille du joueur 1
	//source : http://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	grille G = (char **)malloc(taille * sizeof(char *));
    for (i=0; i<taille; i++){
		 G[i] = (char *)malloc(taille * sizeof(char));
	 }
	 
	 //On rempli G
	 remplir_grille(G, taille);
	 //affiche_jeu(G, taille);
	 
	 liste_navires * l = cree_liste_navires(G, taille);
	 
	//alloue la grille du joueur 2
	grille GC = (char **)malloc(taille * sizeof(char *));
    for (i=0; i<taille; i++){
		 GC[i] = (char *)malloc(taille * sizeof(char));
	 }
	 
	//On initialise G2 pour le jeu
	initialiser_grille(GC, taille);
	
	//afficher les grilles 
	//affiche_etat_coules(GC, taille);
	
	joue(G, GC, taille , *l , taille, taille);
	return 0;
}

