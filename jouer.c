#include <stdio.h>
#include <stdlib.h>
#include "jouer.h"

int navire_coule(maillon *m, int ic, int jc, grille gc)
{
	int i, j;
	gc[ic][jc] = TOUCHER;
	int couler = 1;
	
	for(i = m->i_deb; i < m->i_fin+1; i++)
	{
		for(j = m->j_deb; j < m->j_fin+1; j++)
		{
			couler = couler & (gc[i][j]==TOUCHER);
		}
	}
	if(couler)//si coulé
	{
			printf("Coulé!")
			for(i = m->i_deb; i < m->i_fin+1; i++)
			{
				for(j = m->j_deb; j < m->j_fin+1; j++)
				{
					gc[i][j]==COULE;//afficher sur la grille
					m->coule = 1;//afficher dans chainon
				}
			}
	}
	return couler;
}

int un_navire_coule(liste_navire l, int ic, int jc, grille gc)
{
	maillon *m = l->debut;
	while(m!=NULL)
	{
		if(m->coule!=1)//si pas coulé
		{
			if((ic>=m->i_deb)&&(ic<=m->i_fin))
			{
				if((jc>=m->j_deb)&&(jc<=m->j_fin))
				{
					printf("Touché!");
					return navire_coule(m, ic, jc, gc);
				}
			}
		}
		m = m->suivant;
	}
	return 0;
}

void joue(grille g, grille gc, int n , liste_navire l , int i, int j)
{
	int ic = -1;
	int jc = -1;
	cree_liste_navires(g,l);
	while(!jeu_fini(l))
	{
		affiche_etat_coules(gc,i);
		while((ic<0)&&(jc<0)&&(ic>i)&&(jc>j))
		{
			printf("Choisir les coordonées i et j compris en tre 0 et %d : ",i)
			scanf("%d %d", ic , ij);
		}
		un_navire_coule(l, ic, jc, gc);		
	}	
}

int jeu_fini(liste_navire l)
{
	maillon *m = l->debut;
	int fini = 1;
	while(m!=NULL)
	{
		fini = fini & (m->coule);
		m = m->suivant;
	}
	return fini;
}

