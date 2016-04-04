/*
 * main.c
 * 
 * 
 */

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* STDIO_H  */

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif /* STDLIB_H  */


#include "structureDonnee.h"
#include "affichage.h"
#include "remplir.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Le programme doit etre execute de la facon suivante : batailleNavale tailleGrille\nPar exemple, vous pouvez taper batailleNavale 10\n");
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
	 remplir(G, taille);
	
	//alloue la grille du joueur 2
	grille GC = (char **)malloc(taille * sizeof(char *));
    for (i=0; i<taille; i++){
		 G[i] = (char *)malloc(taille * sizeof(char));
	 }
	 
	//On initialise G2 pour le jeu
	initialiser_grillle(G, taille);
	
	//afficher les grilles 
	affiche_jeu(G, taille);
	return 0;
}

