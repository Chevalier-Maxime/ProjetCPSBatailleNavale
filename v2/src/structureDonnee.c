#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"


void set_field(maillon *m, int v, int p_faible, int p_fort)
{
	int val  = m->maille	;
	
	if((FAIBLE_I_DEB==p_faible)&&(FORT_I_DEB==p_fort))
	{val = (val&(~MASK_I_DEB)) + (v<<OFFSET_I_DEB); }
	
	else if((FAIBLE_I_FIN==p_faible)&&(FORT_I_FIN==p_fort))
	{val = (val&(~MASK_I_FIN)) + (v<<OFFSET_I_FIN);}
	
	else if((FAIBLE_J_DEB==p_faible)&&(FORT_J_DEB==p_fort))
	{val = (val&(~MASK_J_DEB)) + (v<<OFFSET_J_DEB);}
	
	else if((FAIBLE_J_FIN==p_faible)&&(FORT_J_FIN==p_fort))
	{val = (val&(~MASK_J_FIN)) + (v<<OFFSET_J_FIN);}
	
	else if((FAIBLE_COULE==p_faible)&&(FORT_COULE==p_fort))
	{val = (val&(~MASK_COULE)) + (v<<OFFSET_COULE);}
}

int get_field(maillon *m, int p_faible, int p_fort)
{
	int val  = m->maille;
	
	if((FAIBLE_I_DEB==p_faible)&&(FORT_I_DEB==p_fort))
	{return (val&MASK_I_DEB)>>OFFSET_I_DEB; }
	
	else if((FAIBLE_I_FIN==p_faible)&&(FORT_I_FIN==p_fort))
	{return (val&MASK_I_FIN)>>OFFSET_I_FIN;}
	
	else if((FAIBLE_J_DEB==p_faible)&&(FORT_J_DEB==p_fort))
	{return (val&MASK_J_DEB)>>OFFSET_J_DEB;}
	
	else if((FAIBLE_J_FIN==p_faible)&&(FORT_J_FIN==p_fort))
	{return (val&MASK_J_FIN)>>OFFSET_J_FIN;}
	
	else if((FAIBLE_COULE==p_faible)&&(FORT_COULE==p_fort))
	{return (val&MASK_COULE)>>OFFSET_COULE;}	
	
	else{printf("ERREUR\n"); exit(0);}
	
}

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
	set_field(m, ideb, FAIBLE_I_DEB, FORT_I_DEB);
	set_field(m, ifin, FAIBLE_I_FIN, FORT_I_FIN);
	set_field(m, jdeb, FAIBLE_J_DEB, FORT_J_DEB);
	set_field(m, jfin, FAIBLE_J_FIN, FORT_J_FIN);
	set_field(m, 0, FAIBLE_COULE, FORT_COULE);
	m->suivant = NULL;
	printf("Le maillon vaut : %d\n",m->maille);
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
					}
				}
			}
		}
	}
	return l;
}

