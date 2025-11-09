// ============================================================================
// FICHIER: utilisateurs.h
// Description: Fonctions de gestion des utilisateurs
// ============================================================================

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

#include "structures.h"

void ajouter_utilisateur(Bibliotheque* bib);
void supprimer_utilisateur(Bibliotheque* bib);
void modifier_utilisateur(Bibliotheque* bib);
void afficher_utilisateurs(Bibliotheque* bib);
int trouver_utilisateur(Bibliotheque* bib, const char* id_etudiant);
void afficher_un_utilisateur(Utilisateur* user);

#endif