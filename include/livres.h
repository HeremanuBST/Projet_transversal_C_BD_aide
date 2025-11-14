
// ============================================================================
// FICHIER: livres.h
// Description: Fonctions de gestion des livres
// ============================================================================

#ifndef LIVRES_H
#define LIVRES_H

#include "structures.h"

void ajouter_livre(Bibliotheque* bib);
void supprimer_livre(Bibliotheque* bib);
void modifier_livre(Bibliotheque* bib);
void rechercher_livre(Bibliotheque* bib);
void afficher_livres(Bibliotheque* bib);
void trier_livres(Bibliotheque* bib);
int trouver_livre_par_isbn(Bibliotheque* bib, const char* isbn);
void afficher_un_livre(Livre* livre);

#endif
