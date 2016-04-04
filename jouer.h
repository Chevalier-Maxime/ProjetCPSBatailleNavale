#include <stdio.h>
#include <stdlib.h>
#include "structureDonnee.h"

int navire_coule(maillon *m, int ic, int jc, grille gc);
void un_navire_coule(maillon *m, int ic, int jc, grille gc);
void joue(grille g, grille gc, int n , liste_navire l , int i, int j);
int jeu_fini(liste_navire l);
