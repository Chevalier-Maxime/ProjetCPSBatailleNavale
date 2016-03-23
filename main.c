/*
 * main.c
 * 
 * 
 */


#include <stdio.h>

#include "structureDonnee.h"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Le programme doit etre execute de la facon suivante : batailleNavale tailleGrille\nPar exemple, vous pouvez taper batailleNavale 10\n");
	}
	
	int i;
	
	//let valchiffre c = int_of_char c - int_of_char '0';;
	
	//source : http://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	grille G = (char **)malloc(taille * sizeof(char *));
    for (i=0; i<r; i++)
         G[i] = (char *)malloc(taille * sizeof(char));
	
	return 0;
}

