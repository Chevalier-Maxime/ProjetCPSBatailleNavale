/*Maxime Chavalier - Héloïse Fernandes de Almeida */
#ifndef REMPLIR_H
#define REMPLIR_H

#include "structureDonnee.h"

FILE* ouvrir_fichier();
int complet(grille g,int n);
void remplir_grille(grille g,int n);
void initialiser_grille(grille g, int n);

#endif
