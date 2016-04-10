/*Maxime Chavalier - Héloïse Fernandes de Almeida */
#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"


/**
 * Créé une liste de navire vide
 * @return un pointeur sur une liste de navire vide
**/
liste_navires * liste_vide()
{
	liste_navires * l = malloc(sizeof(liste_navires));
	l->debut = NULL;
	l->fin = NULL;
	return l;
}

/**
 * Créé un nouveau maillon
 * @param ideb : la position i du debut du bateau
 * @param ifin : la position i de la fin du bateau
 * @param jdeb : la position j du debut du bateau
 * @param jfin : la position j de la fin du bateau
 * @return un pointeur sur maillon
**/
maillon * nouveau(int ideb,int ifin, int jdeb, int jfin)
{
	maillon * m = malloc(sizeof(maillon));
	m->i_deb = ideb;
	m->i_fin = ifin;
	m->j_deb = jdeb;
	m->j_fin = jfin;
	m->coule = 0;
	m->suivant = NULL;
	return m;
}

/**
 * Insere un maillon dans une liste de navire
 * @param m : un pointeur sur le maillon a inserer dans l
 * @param l : un pointeur sur la liste de maillon
**/
void insertion (maillon * m, liste_navires * l)
{
	if(l->debut == NULL)
	{
		l->debut = m;
		l->fin = m;
	}
	else
	{
		l->fin->suivant=m;
		l->fin = m;
	}
}

/**
 * Créé une liste de navire à partir de la grille du joueur 1 deja remplie
 * @param g : la grille du joueur 1 remplie avec des navires
 * @param n : la taille de la grille
 * @return un pointeur sur liste de navire
**/
liste_navires * cree_liste_navires(grille g, int n)
{
	liste_navires * l = liste_vide();
	maillon * m;
	int i, j,it,jt;
	int tabGrille[n][n]; //tabGrille permet de savoir si on a deja traité le navire
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			tabGrille[i][j]=0;
		}
	}
	
	//On parcours la grille
	for(i = 0; i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			//si la case est colorié
			if(g[i][j]==COLORIER)
			{
				//on regarde si on a deja traité cette partie
				if(tabGrille[i][j]==0)
				{
					//On regarde si le bateau est horizonta
					if((j<n-1)&&(g[i][j+1]==COLORIER))
					{
						tabGrille[i][j] = 1;
						jt=j+1;
						//On cherche sur la ligne ou s'arrete le bateau
						while(g[i][jt]==COLORIER)
						{
							tabGrille[i][jt] = 1;
							jt++;
						}
						
						m = nouveau(i,i,j,jt-1);
						insertion(m,l);
					}
					else{
						//on regarle si le bateau est vertical
						if((i<n-1)&&(g[i+1][j]==COLORIER))
						{
							tabGrille[i][j] = 1;
							it = i+1;
							while(g[it][j]==COLORIER)
							{
								tabGrille[it][j] = 1;
								it++;
							}
							m = nouveau(i,it-1,j,j);
							insertion(m,l);
						}
					}
				}
			}
		}
	}
	return l;
}
