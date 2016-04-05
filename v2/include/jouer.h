#ifndef JOUER_H
#define JOUER_H

#include "structureDonnee.h"

int navire_coule(maillon *m, int ic, int jc, grille gc);
int un_navire_coule(liste_navires l, int ic, int jc, grille gc);
void joue(grille g, grille gc, int n , liste_navires l , int i, int j);
int jeu_fini(liste_navires l);

#endif
