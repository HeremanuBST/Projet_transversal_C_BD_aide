//
// Created by bapti on 28/11/2025.
//

#ifndef BIBILOTHEQUE_NUMERIQUE_EXEMPLAIRE_H
#define BIBILOTHEQUE_NUMERIQUE_EXEMPLAIRE_H


#include "structure.h"

// Ajouter un exemplaire d'un livre (copie physique)
void ajouter_exemplaire(Bibliotheque* bib);

// Supprimer un exemplaire (par son numéro interne)
void supprimer_exemplaire(Bibliotheque* bib, int num_exemplaire);

// Modifier un exemplaire (permet de modifier la date d'achat, par exemple)
void modifier_exemplaire(Bibliotheque* bib);

// Afficher tous les exemplaires (liste complète)
void afficher_exemplaires(Bibliotheque* bib);

// Trouver l'index d'un exemplaire par son numéro (ou -1 si non trouvé)
int trouver_exemplaire_par_num(Bibliotheque* bib, int num_exemplaire);

// Initialiser le prochain numéro d'exemplaire (utilisé après chargement des données)
void initialiser_prochain_num_exemplaire(int prochain_num);

#endif //BIBILOTHEQUE_NUMERIQUE_EXEMPLAIRE_H