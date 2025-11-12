// ============================================================================
// FICHIER: fichiers.c
// Description: Implémentation de la sauvegarde et du chargement
// ============================================================================

#include <stdio.h>
#include "../include/fichiers.h"

void sauvegarder_livres(Bibliotheque* bib) {
    FILE* f = fopen("livres.txt", "w");
    if (!f) {
        printf("Erreur: Impossible d'ouvrir le fichier livres.txt\n");
        return;
    }

    for (int i = 0; i < bib->nb_livres; i++) {
        fprintf(f, "%s|%s|%s|%d|%s|%d\n",
                bib->livres[i].isbn,
                bib->livres[i].titre,
                bib->livres[i].auteur,
                bib->livres[i].annee,
                bib->livres[i].categorie,
                bib->livres[i].disponible);
    }

    fclose(f);
}

void sauvegarder_utilisateurs(Bibliotheque* bib) {
    FILE* f = fopen("utilisateurs.txt", "w");
    if (!f) {
        printf("Erreur: Impossible d'ouvrir le fichier utilisateurs.txt\n");
        return;
    }

    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        fprintf(f, "%s|%s|%s|%s|%d\n",
                bib->utilisateurs[i].id_utilisateur,
                bib->utilisateurs[i].nom,
                bib->utilisateurs[i].prenom,
                bib->utilisateurs[i].email,
                bib->utilisateurs[i].nb_emprunts_actifs);
    }

    fclose(f);
}

void sauvegarder_emprunts(Bibliotheque* bib) {
    FILE* f = fopen("emprunts.txt", "w");
    if (!f) {
        printf("Erreur: Impossible d'ouvrir le fichier emprunts.txt\n");
        return;
    }

    fprintf(f, "%d\n", bib->prochain_id_emprunt);

    for (int i = 0; i < bib->nb_emprunts; i++) {
        fprintf(f, "%d|%s|%s|%s|%s|%s|%d\n",
                bib->emprunts[i].id_emprunt,
                bib->emprunts[i].isbn,
                bib->emprunts[i].id_utilisateur,
                bib->emprunts[i].date_emprunt,
                bib->emprunts[i].date_retour_prevue,
                bib->emprunts[i].date_retour_effective,
                bib->emprunts[i].actif);
    }

    fclose(f);
}

void sauvegarder_donnees(Bibliotheque* bib) {
    printf("\n=== SAUVEGARDE DES DONNEES ===\n");

    sauvegarder_livres(bib);
    sauvegarder_utilisateurs(bib);
    sauvegarder_emprunts(bib);

    printf("-> Donnees sauvegardees avec succes!\n");
    printf("  - %d livres\n", bib->nb_livres);
    printf("  - %d utilisateurs\n", bib->nb_utilisateurs);
    printf("  - %d emprunts\n", bib->nb_emprunts);
}

void charger_livres(Bibliotheque* bib) {
    FILE* f = fopen("livres.txt", "r");
    if (!f) {
        return;
    }

    bib->nb_livres = 0;

    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%d\n",
                  bib->livres[bib->nb_livres].isbn,
                  bib->livres[bib->nb_livres].titre,
                  bib->livres[bib->nb_livres].auteur,
                  &bib->livres[bib->nb_livres].annee,
                  bib->livres[bib->nb_livres].categorie,
                  &bib->livres[bib->nb_livres].disponible) == 6) {
        bib->nb_livres++;
        if (bib->nb_livres >= MAX_LIVRES) break;
    }

    fclose(f);
}

void charger_utilisateurs(Bibliotheque* bib) {
    FILE* f = fopen("utilisateurs.txt", "r");
    if (!f) {
        return;
    }

    bib->nb_utilisateurs = 0;

    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
                  bib->utilisateurs[bib->nb_utilisateurs].id_utilisateur,
                  bib->utilisateurs[bib->nb_utilisateurs].nom,
                  bib->utilisateurs[bib->nb_utilisateurs].prenom,
                  bib->utilisateurs[bib->nb_utilisateurs].email,
                  &bib->utilisateurs[bib->nb_utilisateurs].nb_emprunts_actifs) == 5) {
        bib->nb_utilisateurs++;
        if (bib->nb_utilisateurs >= MAX_UTILISATEURS) break;
    }

    fclose(f);
}

void charger_emprunts(Bibliotheque* bib) {
    FILE* f = fopen("emprunts.txt", "r");
    if (!f) {
        bib->prochain_id_emprunt = 1;
        return;
    }

    fscanf(f, "%d\n", &bib->prochain_id_emprunt);

    bib->nb_emprunts = 0;

    while (fscanf(f, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
                  &bib->emprunts[bib->nb_emprunts].id_emprunt,
                  bib->emprunts[bib->nb_emprunts].isbn,
                  bib->emprunts[bib->nb_emprunts].id_utilisateur,
                  bib->emprunts[bib->nb_emprunts].date_emprunt,
                  bib->emprunts[bib->nb_emprunts].date_retour_prevue,
                  bib->emprunts[bib->nb_emprunts].date_retour_effective,
                  &bib->emprunts[bib->nb_emprunts].actif) == 7) {
        bib->nb_emprunts++;
        if (bib->nb_emprunts >= MAX_EMPRUNTS) break;
    }

    fclose(f);
}

void charger_donnees(Bibliotheque* bib) {
    printf("Chargement des donnees...\n");

    charger_livres(bib);
    charger_utilisateurs(bib);
    charger_emprunts(bib);

    printf("-> Donnees chargees:\n");
    printf("  - %d livres\n", bib->nb_livres);
    printf("  - %d utilisateurs\n", bib->nb_utilisateurs);
    printf("  - %d emprunts\n", bib->nb_emprunts);
}
