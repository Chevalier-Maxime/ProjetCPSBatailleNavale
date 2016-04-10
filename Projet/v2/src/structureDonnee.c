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
	//tabGrille permet de savoir si on a deja traité le navire
	int tabGrille[n][n];
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
					//On regarde si le bateau est horizontal
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

/**
 * Stocke v dans l'intervalle de bits [p_fort,p_faible] de x sans modifier les autres bits.
 * @param m : un pointeur sur l'entier à modifier
 * @param v : la valeur a inserer dans m
 * @param p_faible : borne inferieur de m où stocker v
 * @param p_fort : borne superieur de m où stocker v
**/
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
	*m = (*m)&(~mask); //On efface le champ à modifier
	*m = (*m)|((v<<p_faible)&mask); // on decale v à la position ou il doit etre, on le tronque avec un masque si v est trop grand, et on le met dans le maillon
}

/**
 * Retourne l'entier stocké dans l'intervalle de bits [fort, faible] de x
 * @param m : un pointeur sur l'entier ou est stocké la valeur à récuperer
 * @param p_faible : borne inferieur de m où est stocker v
 * @param p_fort : borne superieur de m où est stocker v
 * @return l'entier stocké dans l'intervalle de bits [fort, faible] de x
**/

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

/**
 * Stocke v dans le champ ideb de m
 * @param m : pointeur sur l'entier à modifier
 * @param v : la valeur à inserer
**/
void set_ideb(int *m, int v)
{
	set_field(m,v,FAIBLE_I_DEB,FORT_I_DEB);
}

/**
 * Stocke v dans le champ ifin de m
 * @param m : pointeur sur l'entier à modifier
 * @param v : la valeur à inserer
**/
void set_ifin(int *m, int v)
{
	set_field(m,v,FAIBLE_I_FIN,FORT_I_FIN);
}

/**
 * Stocke v dans le champ jdeb de m
 * @param m : pointeur sur l'entier à modifier
 * @param v : la valeur à inserer
**/
void set_jdeb(int *m, int v)
{
	set_field(m,v,FAIBLE_J_DEB,FORT_J_DEB);
}

/**
 * Stocke v dans le champ jfin de m
 * @param m : pointeur sur l'entier à modifier
 * @param v : la valeur à inserer
**/
void set_jfin(int *m, int v)
{
	set_field(m,v,FAIBLE_J_FIN,FORT_J_FIN);
}

/**
 * Stocke v dans le champ coule de m
 * @param m : pointeur sur l'entier à modifier
 * @param v : la valeur à inserer
**/
void set_coule(int *m, int v)
{
	set_field(m,v,FAIBLE_COULE,FORT_COULE);
}

/**
 * récupère la valeur du champ ideb de m
 * @param m : pointeur sur l'entier où est stocké ideb
 * @return le champ ideb de m
**/
int get_ideb(int *m)
{
	return get_field(m,FAIBLE_I_DEB, FORT_I_DEB);
}

/**
 * récupère la valeur du champ ifin de m
 * @param m : pointeur sur l'entier où est stocké ifin
 * @return le champ ifin de m
**/
int get_ifin(int *m)
{
	return get_field(m,FAIBLE_I_FIN, FORT_I_FIN);
}
/**
 * récupère la valeur du champ jdeb de m
 * @param m : pointeur sur l'entier où est stocké jdeb
 * @return le champ jdeb de m
**/
int get_jdeb(int *m)
{
	return get_field(m,FAIBLE_J_DEB, FORT_J_DEB);
}

/**
 * récupère la valeur du champ jfin de m
 * @param m : pointeur sur l'entier où est stocké jfin
 * @return le champ jfin de m
**/
int get_jfin(int *m)
{
	return get_field(m,FAIBLE_J_FIN, FORT_J_FIN);
}

/**
 * récupère la valeur du champ coule de m
 * @param m : pointeur sur l'entier où est stocké coule
 * @return le champ coule de m
**/
int get_coule(int *m)
{
	return get_field(m,FAIBLE_COULE, FORT_COULE);
}
