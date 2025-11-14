//
// Created by Heremanu on 07/11/2025.
//


// ============================================================================
// FICHIER: utils.h
// Description: Fonctions utilitaires
// ============================================================================

#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void vider_buffer(); // Sert à vider la mémoire de transite entre le scanf et la RAM
void obtenir_date_actuelle(char* date);
void ajouter_jours(const char* date_depart, int jours, char* date_arrivee);
int comparer_dates(const char* date1, const char* date2);
int calculer_jours_difference(const char* date1, const char* date2);
void pause_ecran();

#endif
