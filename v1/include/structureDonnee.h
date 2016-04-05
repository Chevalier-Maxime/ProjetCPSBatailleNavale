
#ifndef STRUCTUREDONNEE_H
#define STRUCTUREDONNEE_H

#define NB_PORTE_AVION 1
#define NB_CROISEUR 2
#define NB_CONTRE_TORPILLEURS 3
#define NB_TORPILLEURS 4

#define T_PORTE_AVION 6
#define T_CROISEUR 4
#define T_CONTRE_TORPILLEURS 3
#define T_TORPILLEURS 2

#define COLORIER 'N'
#define BLANC 'B'
#define RATEE 'X'
#define COULE 'C'
#define TOUCHER 'T'

typedef char** grille;

typedef struct maillon{
	int i_deb;
	int j_deb;
	int i_fin;
	int j_fin;
	short int coule;
	struct maillon * suivant;
}maillon;

typedef struct liste_navires{
	maillon * debut;
	maillon * fin;
}liste_navires;

liste_navires * liste_vide();
maillon * nouveau(int ideb,int ifin, int jdeb, int jfin);
void insertion (maillon * m, liste_navires * l);

liste_navires * cree_liste_navires(grille g, int n);

#endif
