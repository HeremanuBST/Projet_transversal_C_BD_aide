#ifndef BIBILOTHEQUE_NUMERIQUE_UTILISATEUR_H
#define BIBILOTHEQUE_NUMERIQUE_UTILISATEUR_H

#include "structure.h"

// Ajouter un utilisateur
void ajouter_utilisateur(Bibliotheque* bib);

// Supprimer un utilisateur
void supprimer_utilisateur(Bibliotheque* bib);

// Modifier un utilisateur (nom, prenom, email)
void modifier_utilisateur(Bibliotheque* bib);

// Afficher tous les utilisateurs
void afficher_utilisateurs(Bibliotheque* bib);

// Trouver l'index d'un utilisateur par son ID (ou -1 si non trouvé)
int trouver_utilisateur(Bibliotheque* bib, const char* id_utilisateur);

// Afficher les informations d'un utilisateur individuel
void afficher_un_utilisateur(const Utilisateur* user);





#endif //BIBILOTHEQUE_NUMERIQUE_UTILISATEUR_H