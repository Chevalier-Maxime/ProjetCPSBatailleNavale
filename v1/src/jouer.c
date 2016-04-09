#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"
#include "affichage.h"

/**
 * Fonction permettant de tester si un bateau à été coulé.
 * A appeler quand on touche un bateau
 * @param m* : Le maillon du bateau à tester
 * @param ic : L'indice de la ligne ou on a touché
 * @param jc : L'indice de la colonne ou on a touché
 * @param gc : La grille du joueur 2
 * @return 1 si un bateau est coulé, 0 sinon
 **/
int navire_coule(maillon *m, int ic, int jc, grille gc)
{
	int i, j;
	
	//On modifie la grille du joueur 2 pour dire que le bateau est touché
	gc[ic][jc] = TOUCHER;	
	
	//On test le bateau courant est touché sur toutes ses cases
	for(i = m->i_deb; i <=m->i_fin; i++)
	{
		for(j = m->j_deb; j <=m->j_fin; j++)
		{
			if(gc[i][j]!=TOUCHER){return 0;}
		}
	}
	
	//Si oui, on dit a l'utilisateur que le bateau est coulé et on modifie la grille
	//pour mettre toutes les cases à coulé
	printf("Coulé!\n");
	for(i = m->i_deb; i <=m->i_fin; i++)
	{
		for(j = m->j_deb; j <=m->j_fin; j++)
		{
			gc[i][j]=COULE;//afficher sur la grille
			m->coule = 1;//afficher dans chainon
		}
	}
	return 1;
}


/**
 * Fonction permettant de tester si on touche un bateau
 * @param l : La liste de tous les navires
 * @param ic : L'indice de la ligne ou on a touché
 * @param jc : L'indice de la colonne ou on a touché
 * @param gc : La grille du joueur 2
 * @return 1 si on coule un navire, 0 sinon
 **/
int un_navire_coule(liste_navires l, int ic, int jc, grille gc)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(m->coule!=1)//si pas coulé
		{
			if((ic>=m->i_deb)&&(ic<=m->i_fin))
			{
				if((jc>=m->j_deb)&&(jc<=m->j_fin))
				{
					printf("Touché!\n");
					return navire_coule(m, ic, jc, gc);
				}
			}
		}
		m = m->suivant;
	}
	printf("Raté!\n");
	gc[ic][jc] = RATEE;
	return 0;
}


/**
 * Fonction permettant de savoir si on a coulé tous les navires.
 * @param l : La liste des bateaux du jeu
 * @return 1 si le jeu est fini, 0 sinon
 **/
int jeu_fini(liste_navires l)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(m->coule==0){return 0;}
		m = m->suivant;
	}
	return 1;
}

/**
 * Fonction permettant de jouer
 * @param g : la grille du joueur 1, où sont positionés les bateaux.
 * @param gc : La grille du joueur 2, initialisée.
 * @param n : la taille des grilles.
 * @param l : la liste des navires du jeu
 * @param i : 
 * @param j :
 **/
void joue(grille g, grille gc, int n , liste_navires l , int i, int j)
{
	int ic = -1;
	int jc = -1;
	int nbcoup =0;
	int s;
	int c;
	while(!jeu_fini(l))
	{
		jc=-1;
		ic=-1;
		//On affiche la grille du joueur 2
		affiche_etat_coules(gc,n);
		//Tant que l'utilisateur ne rentre pas des nombres entre 0 et n-1
		while(((ic<0)||(ic>=n))||((jc<0)||(jc>=n)))
		{
			printf("Choisir les coordonées i et j compris entre 0 et %d : \n",n);
			s = scanf("%d %d%*[^\n]", &ic, &jc);
			if(s != 2)
			{
				/* echec de la saisie */
				while ( ((c = getchar()) != '\n') && c != EOF);
				printf("Ca n'est pas un nombre valide\n");
			}
			else
			{
				/* reussite de la saisie */
				getchar(); /* on enleve le '\n' restant */
			}
			if (((ic<0)||(ic>=n))||((jc<0)||(jc>=n)))
			{
				printf("Veuillez entrer des coordonnées entre %d et %d\n", 0, n-1);
			}
		}
		un_navire_coule(l, ic, jc, gc);
		nbcoup ++;		
	}
	printf("\n\n Vous avez gagné !!\n La partie à durée %d coups\n",nbcoup);
}



