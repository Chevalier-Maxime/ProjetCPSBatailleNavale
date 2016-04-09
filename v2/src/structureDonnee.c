#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"



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
	m->maille = 0;
	int * b = &(m->maille);
	
	set_ideb(b,ideb);
	set_ifin(b,ifin);
	set_jdeb(b,jdeb);
	set_jfin(b,jfin);
	set_coule(b,0);
	
	m->suivant = NULL;
	return m;
}

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

liste_navires * cree_liste_navires(grille g, int n)
{
	liste_navires * l = liste_vide();
	maillon * m;
	int i, j,it,jt;
	int tabGrille[n][n];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			tabGrille[i][j]=0;
		}
	}
	
	
	for(i = 0; i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(g[i][j]==COLORIER)
			{
				//on regarde si on a deja traité cette partie
				if(tabGrille[i][j]==0)
				{
					//On regarde sur la ligne
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
						//on regarle la colonne
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
						else
						{
							//erreur, un bateau ne peut pas faire une seule case
						}
					}
				}
			}
		}
	}
	return l;
}

void set_field(int *m, int v, int p_faible, int p_fort)
{
	int mask = 0;
	int i,taille;
	taille = p_fort -p_faible;
	for(i=0; i <= taille; i++)
	{
		mask = (mask<<1)|1;
	}
	mask=mask<<p_faible; //On positionne le masque au bon endroit
	*m = (*m)|((v<<p_faible)&mask); // on decale v à la position ou il doit etre, on le tronque avec un masque si v est trop grand, et on le met dans le maillon
}

int get_field(int *m, int p_faible, int p_fort)
{
	int mask = 0;
	int i,taille,v;
	taille = p_fort -p_faible;
	for(i=0; i <= taille; i++)
	{
		mask = (mask<<1)|1;
	}
	mask=mask<<p_faible;
	v= ((*m)&mask)>>p_faible; //on selection la partie souhaité du maillon, puis on la décale
	return v;
}

void set_ideb(int *m, int v)
{
	set_field(m,v,FAIBLE_I_DEB,FORT_I_DEB);
}
void set_ifin(int *m, int v)
{
	set_field(m,v,FAIBLE_I_FIN,FORT_I_FIN);
}
void set_jdeb(int *m, int v)
{
	set_field(m,v,FAIBLE_J_DEB,FORT_J_DEB);
}
void set_jfin(int *m, int v)
{
	set_field(m,v,FAIBLE_J_FIN,FORT_J_FIN);
}
void set_coule(int *m, int v)
{
	set_field(m,v,FAIBLE_COULE,FORT_COULE);
}
int get_ideb(int *m)
{
	return get_field(m,FAIBLE_I_DEB, FORT_I_DEB);
}
int get_ifin(int *m)
{
	return get_field(m,FAIBLE_I_FIN, FORT_I_FIN);
}
int get_jdeb(int *m)
{
	return get_field(m,FAIBLE_J_DEB, FORT_J_DEB);
}
int get_jfin(int *m)
{
	return get_field(m,FAIBLE_J_FIN, FORT_J_FIN);
}
int get_coule(int *m)
{
	return get_field(m,FAIBLE_COULE, FORT_COULE);
}
