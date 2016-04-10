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

#define OFFSET_I_DEB 0
#define OFFSET_J_DEB 7
#define OFFSET_I_FIN 14
#define OFFSET_J_FIN 21
#define OFFSET_COULE 31

#define FAIBLE_I_DEB 0
#define FAIBLE_J_DEB 7
#define FAIBLE_I_FIN 14
#define FAIBLE_J_FIN 21
#define FAIBLE_COULE 31

#define FORT_I_DEB 3
#define FORT_J_DEB 10
#define FORT_I_FIN 17
#define FORT_J_FIN 24
#define FORT_COULE 31

typedef char** grille;

typedef struct maillon{
	int32_t maille;
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

void set_field(int *m,int v, int p_faible, int p_fort);
int get_field(int *m, int p_faible, int p_fort);

void set_ideb(int *m, int v);
void set_ifin(int *m, int v);
void set_jdeb(int *m, int v);
void set_jfin(int *m, int v);
void set_coule(int *m, int v);
int get_ideb(int *m);
int get_ifin(int *m);
int get_jdeb(int *m);
int get_jfin(int *m);
int get_coule(int *m);

#endif
