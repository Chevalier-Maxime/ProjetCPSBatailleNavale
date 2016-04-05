#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"
#include "affichage.h"


int navire_coule(maillon *m, int ic, int jc, grille gc)
{
	printf("Un navire touché\n");
	int i, j;
	
	gc[ic][jc] = TOUCHER;	
	
	for(i = m->i_deb; i <=m->i_fin; i++)
	{
		for(j = m->j_deb; j <=m->j_fin; j++)
		{
			if(gc[i][j]!=TOUCHER){return 0;}
		}
	}
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
	return 0;
}

int jeu_fini(liste_navires l)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(m->coule==0){printf("Le jeu n'est pas fini\n");return 0;}
		m = m->suivant;
	}
	return 1;
}

void joue(grille g, grille gc, int n , liste_navires l , int i, int j)
{
	printf("joue\n");
	int ic = -1;
	int jc = -1;
	while(!jeu_fini(l))
	{
		printf("le jeu n'est pas fini\n");
		jc=-1;
		ic=-1;
		affiche_etat_coules(gc,n);
		while(((ic<0)||(ic>n))||((jc<0)||(jc>n)))
		{
			printf("Choisir les coordonées i et j compris entre 0 et %d : \n",n);
			scanf("%d %d", &ic, &jc);
			
		}
		printf("blop");
		un_navire_coule(l, ic, jc, gc);		
	}
}



