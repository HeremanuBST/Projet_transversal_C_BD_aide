
// FICHIER: utils.c


#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/utils.h"

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void obtenir_date_actuelle(char* date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void ajouter_jours(const char* date_depart, int jours, char* date_arrivee) {
    struct tm tm = {0};
    int annee, mois, jour;

    sscanf(date_depart, "%d-%d-%d", &annee, &mois, &jour);

    tm.tm_year = annee - 1900;
    tm.tm_mon = mois - 1;
    tm.tm_mday = jour + jours;

    mktime(&tm);

    sprintf(date_arrivee, "%04d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int comparer_dates(const char* date1, const char* date2) {
    return strcmp(date1, date2);
}

int calculer_jours_difference(const char* date1, const char* date2) {
    struct tm tm1 = {0}, tm2 = {0};
    int a1, m1, j1, a2, m2, j2;

    sscanf(date1, "%d-%d-%d", &a1, &m1, &j1);
    sscanf(date2, "%d-%d-%d", &a2, &m2, &j2);

    tm1.tm_year = a1 - 1900;
    tm1.tm_mon = m1 - 1;
    tm1.tm_mday = j1;

    tm2.tm_year = a2 - 1900;
    tm2.tm_mon = m2 - 1;
    tm2.tm_mday = j2;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return (int)difftime(t2, t1) / (60 * 60 * 24);
}

void pause_ecran() {
    printf("\nAppuyez sur Entree pour continuer...");
    vider_buffer();
    getchar();
}
