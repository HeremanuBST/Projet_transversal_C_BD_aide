// ============================================================================
// FICHIER: fichiers.h
// Description: Fonctions de sauvegarde et chargement
// ============================================================================

#ifndef FICHIERS_H
#define FICHIERS_H

#include "../structures.h"

void sauvegarder_donnees(Bibliotheque* bib);
void charger_donnees(Bibliotheque* bib);
void sauvegarder_livres(Bibliotheque* bib);
void sauvegarder_utilisateurs(Bibliotheque* bib);
void sauvegarder_emprunts(Bibliotheque* bib);
void charger_livres(Bibliotheque* bib);
void charger_utilisateurs(Bibliotheque* bib);
void charger_emprunts(Bibliotheque* bib);

#endif
