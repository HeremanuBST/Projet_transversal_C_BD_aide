// ============================================================================
// FICHIER: emprunts.h
// Description: Fonctions de gestion des emprunts
// ============================================================================

#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "structures.h"

void emprunter_livre(Bibliotheque* bib);
void retourner_livre(Bibliotheque* bib);
void afficher_emprunts_actifs(Bibliotheque* bib);
void verifier_retards(Bibliotheque* bib);
void afficher_un_emprunt(Emprunt* emp, Bibliotheque* bib);

#endif