#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void vider_buffer() {
    int c;
    // Lire et ignorer tous les caractères jusqu'au prochain '\n' ou EOF
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void obtenir_date_actuelle(char* date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Format "JJ/MM/AAAA"
    strftime(date, MAX_DATE, "%d/%m/%Y", &tm);
}

void ajouter_jours(const char* date_depart, int jours, char* date_arrivee) {
    int jour, mois, an;
    if (sscanf(date_depart, "%d/%d/%d", &jour, &mois, &an) != 3) {
        // format invalide, on met une date vide
        strcpy(date_arrivee, "");
        return;
    }
    struct tm tm_date = {0};
    tm_date.tm_mday = jour;
    tm_date.tm_mon = mois - 1;
    tm_date.tm_year = an - 1900;
    // Fixer l'heure à midi pour limiter les effets des changements d'heure (été/hiver)
    tm_date.tm_hour = 12;
    tm_date.tm_min = 0;
    tm_date.tm_sec = 0;
    tm_date.tm_isdst = -1;
    time_t time_date = mktime(&tm_date);
    if (time_date == -1) {
        // Erreur lors de la conversion
        strcpy(date_arrivee, "");
        return;
    }
    // Ajouter les jours en secondes
    time_date += (time_t)jours * 24 * 3600;
    struct tm *tm_res = localtime(&time_date);
    strftime(date_arrivee, MAX_DATE, "%d/%m/%Y", tm_res);
}

int comparer_dates(const char* date1, const char* date2) {
    int j1, m1, a1;
    int j2, m2, a2;
    if (sscanf(date1, "%d/%d/%d", &j1, &m1, &a1) != 3) return 0;
    if (sscanf(date2, "%d/%d/%d", &j2, &m2, &a2) != 3) return 0;
    if (a1 < a2) return -1;
    if (a1 > a2) return 1;
    // années égales
    if (m1 < m2) return -1;
    if (m1 > m2) return 1;
    // mois égaux
    if (j1 < j2) return -1;
    if (j1 > j2) return 1;
    return 0;
}

int calculer_jours_difference(const char* date1, const char* date2) {
    int j1, m1, a1;
    int j2, m2, a2;
    if (sscanf(date1, "%d/%d/%d", &j1, &m1, &a1) != 3) return 0;
    if (sscanf(date2, "%d/%d/%d", &j2, &m2, &a2) != 3) return 0;
    struct tm tm1 = {0}, tm2 = {0};
    tm1.tm_mday = j1;
    tm1.tm_mon = m1 - 1;
    tm1.tm_year = a1 - 1900;
    tm1.tm_hour = 12; tm1.tm_min = 0; tm1.tm_sec = 0;
    tm1.tm_isdst = -1;
    tm2.tm_mday = j2;
    tm2.tm_mon = m2 - 1;
    tm2.tm_year = a2 - 1900;
    tm2.tm_hour = 12; tm2.tm_min = 0; tm2.tm_sec = 0;
    tm2.tm_isdst = -1;
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    if (time1 == -1 || time2 == -1) {
        return 0;
    }
    double diff_seconds = difftime(time2, time1);
    // Arrondir à l'entier le plus proche (pour compenser d'éventuels décalages horaires)
    int diff_days;
    if (diff_seconds >= 0) {
        diff_days = (int)((diff_seconds + 43200) / 86400);
    } else {
        diff_days = (int)((diff_seconds - 43200) / 86400);
    }
    return diff_days;
}

void pause_ecran() {
    printf("Appuyez sur Entrée pour continuer...");
    fflush(stdout);
    vider_buffer();
    getchar();
}
