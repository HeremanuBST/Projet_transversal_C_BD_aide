//
// Created by bapti on 28/11/2025.
//

#ifndef BIBILOTHEQUE_NUMERIQUE_LIVRE_H
#define BIBILOTHEQUE_NUMERIQUE_LIVRE_H

#include "structure.h"

// Ajouter un nouveau livre (œuvre) à la bibliothèque
void ajouter_livre(Bibliotheque* bib);

// Supprimer un livre de la bibliothèque (ainsi que ses exemplaires)
void supprimer_livre(Bibliotheque* bib);

// Modifier les informations d'un livre (titre, auteur, catégorie, année)
void modifier_livre(Bibliotheque* bib);

// Rechercher un livre (par ISBN ou par mots-clés) et afficher les résultats
void rechercher_livre(Bibliotheque* bib);

// Afficher la liste de tous les livres
void afficher_livres(Bibliotheque* bib);

// Trier les livres selon un critère choisi (titre, auteur, catégorie, année ou popularité)
void trier_livres(Bibliotheque* bib);

// Trouver l'index d'un livre par son ISBN (ou -1 si non trouvé)
int trouver_livre_par_isbn(Bibliotheque* bib, const char* isbn);

// Afficher les informations d'un livre individuel
void afficher_un_livre(const Livre* livre);





#endif //BIBILOTHEQUE_NUMERIQUE_LIVRE_H