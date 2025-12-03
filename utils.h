//
// Created by bapti on 28/11/2025.
//

#ifndef BIBILOTHEQUE_NUMERIQUE_UTILS_H
#define BIBILOTHEQUE_NUMERIQUE_UTILS_H


#include "structure.h"

// Vider le buffer d'entrée (stdin) pour éviter les problèmes après un scanf
void vider_buffer();

// Obtenir la date actuelle au format "JJ/MM/AAAA"
void obtenir_date_actuelle(char* date);

// Ajouter un nombre de jours à une date donnée (format "JJ/MM/AAAA")
// date_depart : la date initiale, jours : le nombre de jours à ajouter
// Le résultat est stocké dans date_arrivee (qui doit avoir assez d'espace)
void ajouter_jours(const char* date_depart, int jours, char* date_arrivee);

// Comparer deux dates (format "JJ/MM/AAAA")
// Renvoie -1 si date1 < date2, 0 si égales, +1 si date1 > date2
int comparer_dates(const char* date1, const char* date2);

// Calculer la différence en jours entre deux dates (date2 - date1)
int calculer_jours_difference(const char* date1, const char* date2);

// Mettre le programme en pause jusqu'à appui sur Entrée
void pause_ecran();




#endif //BIBILOTHEQUE_NUMERIQUE_UTILS_H