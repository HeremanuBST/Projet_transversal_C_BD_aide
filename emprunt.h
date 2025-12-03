//
// Created by bapti on 28/11/2025.
//

#ifndef BIBILOTHEQUE_NUMERIQUE_EMPRUNT_H
#define BIBILOTHEQUE_NUMERIQUE_EMPRUNT_H


#include "structure.h"

// Emprunter un exemplaire de livre (création d'un emprunt)
void emprunter_exemplaire(Bibliotheque* bib);

// Retourner un exemplaire emprunté (enregistrer le retour)
void retourner_exemplaire(Bibliotheque* bib);

// Afficher tous les emprunts actifs (non retournés)
void afficher_emprunts_actifs(Bibliotheque* bib);

// Afficher tous les emprunts en cours (alias des emprunts actifs)
void afficher_emprunts_en_cours(Bibliotheque* bib);

// Vérifier les emprunts en retard (> DUREE_EMPRUNT jours)
void verifier_retards(Bibliotheque* bib);

// Afficher les détails d'un emprunt (formatage)
void afficher_un_emprunt(const Emprunt* emp, Bibliotheque* bib);

// Afficher des statistiques (top livres empruntés, utilisateur le plus actif, etc.)
void afficher_statistiques(Bibliotheque* bib);

// Afficher l'historique complet des emprunts d'un utilisateur donné
void historique_emprunts_utilisateur(Bibliotheque* bib);






#endif //BIBILOTHEQUE_NUMERIQUE_EMPRUNT_H