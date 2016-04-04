#include "structureDonnee.h"
#include <stdio.h>
#include <stdlib.h>


liste_navires * liste_vide()
{
	liste_navires * l = malloc(sizeof(liste_navires));
	l->debut = NULL;
	l->fin = NULL;
	return l;
}
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
void insertion (maillon * m, liste_navires * l)
{
	maillon * temp = l->fin;
	temp->suivant = m;
	l->fin = m;
}

liste_navires * cree_liste_navires(grille g, int n)
{
	liste_navires * l = liste_vide();
	int i, j;
	
	for(i = 0; i<n;i++)
	{
		
	}
}
