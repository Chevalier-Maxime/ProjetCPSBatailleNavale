#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"
#include "affichage.h"


int navire_coule(maillon *m, int ic, int jc, grille gc)
{
	int i, j;
	
	gc[ic][jc] = TOUCHER;	
	
	for(i = get_field(m,FAIBLE_I_DEB,FORT_I_DEB); i <=get_field(m,FAIBLE_I_FIN,FORT_I_FIN); i++)
	{
		for(j = get_field(m,FAIBLE_J_DEB,FORT_J_DEB); j <=get_field(m,FAIBLE_J_FIN,FORT_J_FIN); j++)
		{
			if(gc[i][j]!=TOUCHER){return 0;}
		}
	}
	printf("Coulé!\n");
	for(i = get_field(m,FAIBLE_I_DEB,FORT_I_DEB); i <=get_field(m,FAIBLE_I_FIN,FORT_I_FIN); i++)
	{
		for(j = get_field(m,FAIBLE_J_DEB,FORT_J_DEB); j <=get_field(m,FAIBLE_J_FIN,FORT_J_FIN); j++)
		{
			gc[i][j]=COULE;//afficher sur la grille
			set_field(m,1,FAIBLE_COULE,FORT_COULE);//afficher dans chainon
		}
	}
	return 1;
}

int un_navire_coule(liste_navires l, int ic, int jc, grille gc)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(get_field(m,FAIBLE_COULE,FORT_COULE)!=1)//si pas coulé
		{
			if((ic>=get_field(m,FAIBLE_I_DEB,FORT_I_DEB))&&(ic<=get_field(m,FAIBLE_I_FIN,FORT_I_FIN)))
			{
				if((jc>=get_field(m,FAIBLE_J_DEB,FORT_J_DEB))&&(jc<=get_field(m,FAIBLE_J_FIN,FORT_J_FIN)))
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

int jeu_fini(liste_navires l)
{
	maillon *m = l.debut;
	while(m!=NULL)
	{
		if(get_field(m,FAIBLE_COULE,FORT_COULE)==0){printf("Le jeu n'est pas fini\n");return 0;}
		m = m->suivant;
	}
	return 1;
}

void joue(grille g, grille gc, int n , liste_navires l , int i, int j)
{
	int ic = -1;
	int jc = -1;
	int nbcoup =0;
	while(!jeu_fini(l))
	{
		jc=-1;
		ic=-1;
		affiche_etat_coules(gc,n);
		while(((ic<0)||(ic>n))||((jc<0)||(jc>n)))
		{
			printf("Choisir les coordonées i et j compris entre 0 et %d : \n",n);
			scanf("%d %d", &ic, &jc);
			
		}
		un_navire_coule(l, ic, jc, gc);
		nbcoup ++;		
	}
	printf("\n\n Vous avez gagné !!\n La partie à durée %d coups\n",nbcoup);
}



