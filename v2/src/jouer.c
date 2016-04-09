#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"
#include "affichage.h"


int navire_coule(maillon *m, int ic, int jc, grille gc)
{
	int i, j;
	
	gc[ic][jc] = TOUCHER;	
	
	for(i = get_ideb((&m->maille)); i <=get_ifin((&m->maille)); i++)
	{
		for(j = get_jdeb((&m->maille)); j <=get_jfin((&m->maille)); j++)
		{
			if(gc[i][j]!=TOUCHER){return 0;}
		}
	}
	printf("Coulé!\n");
	for(i = get_ideb((&m->maille)); i <=get_ifin((&m->maille)); i++)
	{
		for(j = get_jdeb((&m->maille)); j <=get_jfin((&m->maille)); j++)
		{
			gc[i][j]=COULE;//afficher sur la grille
			set_coule((&m->maille),1);//afficher dans chainon
		}
	}
	return 1;
}

int un_navire_coule(liste_navires l, int ic, int jc, grille gc)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(get_coule((&m->maille))!=1)//si pas coulé
		{
			if((ic>=get_ideb((&m->maille)))&&(ic<=get_ifin((&m->maille))))
			{
				if((jc>=get_jdeb((&m->maille)))&&(jc<=get_jfin((&m->maille))))
				{
					printf("Touché!\n");
					return navire_coule(m, ic, jc, gc);
				}
			}
		}
		m = m->suivant;
	}
	gc[ic][jc] = RATEE;
	return 0;
}

int jeu_fini(liste_navires l)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(get_coule(&m->maille)==0){return 0;}
		m = m->suivant;
	}
	return 1;
}

void joue(grille g, grille gc, int n , liste_navires l , int i, int j)
{
	int ic = -1;
	int jc = -1;
	int nbcoup =0;
	int s;
	int c;
	printf("\nn = %d\n", n);
	while(!jeu_fini(l))
	{
		jc=-1;
		ic=-1;
		affiche_etat_coules(gc,n);
		while(((ic<0)||(ic>=n))||((jc<0)||(jc>=n)))
		{
			printf("Choisir les coordonées i et j compris entre 0 et %d : \n",n);
			s = scanf("%d %d%*[^\n]", &ic, &jc);
			if(s != 2)
			{
				while ( ((c = getchar()) != '\n') && c != EOF);
				printf("Ca n'est pas un nombre valide\n");
			}
			else
			{
				/* reussite de la saisie */
				getchar(); /* on enleve le '\n' restant */
				printf("i %d, j %d\n", ic, jc);
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



