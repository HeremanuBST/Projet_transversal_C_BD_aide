// ============================================================================
// FICHIER: emprunts.c
// Description: Implémentation de la gestion des emprunts
// ============================================================================

#include <stdio.h>
#include <string.h>
#include "emprunts.h"
#include "livres.h"
#include "utilisateurs.h"
#include "utils.h"

void afficher_un_emprunt(Emprunt* emp, Bibliotheque* bib) {
    int idx_livre = trouver_livre_par_isbn(bib, emp->isbn);
    int idx_user = trouver_utilisateur(bib, emp->id_etudiant);

    printf("ID Emprunt: %d\n", emp->id_emprunt);

    if (idx_livre != -1) {
        printf("Livre: %s\n", bib->livres[idx_livre].titre);
    }

    if (idx_user != -1) {
        printf("Utilisateur: %s %s\n",
               bib->utilisateurs[idx_user].prenom,
               bib->utilisateurs[idx_user].nom);
    }

    printf("Date emprunt: %s\n", emp->date_emprunt);
    printf("Date retour prevue: %s\n", emp->date_retour_prevue);

    if (emp->actif) {
        char date_actuelle[MAX_DATE];
        obtenir_date_actuelle(date_actuelle);
        int jours = calculer_jours_difference(emp->date_retour_prevue, date_actuelle);

        if (jours > 0) {
            printf("RETARD: %d jours\n", jours);
        } else {
            printf("Statut: En cours\n");
        }
    } else {
        printf("Date retour effective: %s\n", emp->date_retour_effective);
    }

    printf("----------------------------------------\n");
}

void emprunter_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];
    char id_etudiant[MAX_ID];

    printf("\n=== EMPRUNTER UN LIVRE ===\n");

    printf("ISBN du livre: ");
    scanf("%13s", isbn);
    vider_buffer();

    int idx_livre = trouver_livre_par_isbn(bib, isbn);
    if (idx_livre == -1) {
        printf("Erreur: Livre non trouve!\n");
        return;
    }

    if (!bib->livres[idx_livre].disponible) {
        printf("Erreur: Le livre est deja emprunte!\n");
        return;
    }

    printf("ID étudiant: ");
    scanf("%19s", id_etudiant);
    vider_buffer();

    int idx_user = trouver_utilisateur(bib, id_etudiant);
    if (idx_user == -1) {
        printf("Erreur: Utilisateur non trouvé!\n");
        return;
    }

    if (bib->utilisateurs[idx_user].nb_emprunts_actifs >= MAX_EMPRUNTS_PAR_USER) {
        printf("Erreur: L'utilisateur a atteint la limite de %d emprunts!\n",
               MAX_EMPRUNTS_PAR_USER);
        return;
    }

    if (bib->nb_emprunts >= MAX_EMPRUNTS) {
        printf("Erreur: Capacite maximale d'emprunts atteinte!\n");
        return;
    }

    Emprunt nouveau;
    nouveau.id_emprunt = bib->prochain_id_emprunt++;
    strcpy(nouveau.isbn, isbn);
    strcpy(nouveau.id_etudiant, id_etudiant);
    obtenir_date_actuelle(nouveau.date_emprunt);
    ajouter_jours(nouveau.date_emprunt, DUREE_EMPRUNT, nouveau.date_retour_prevue);
    strcpy(nouveau.date_retour_effective, "");
    nouveau.actif = 1;

    bib->emprunts[bib->nb_emprunts] = nouveau;
    bib->nb_emprunts++;

    bib->livres[idx_livre].disponible = 0;
    bib->utilisateurs[idx_user].nb_emprunts_actifs++;

    printf("\n-> Emprunt enregistre avec succes!\n");
    printf("Date de retour prevue: %s\n", nouveau.date_retour_prevue);
}

void retourner_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];
    char id_etudiant[MAX_ID];

    printf("\n=== RETOURNER UN LIVRE ===\n");

    printf("ISBN du livre: ");
    scanf("%13s", isbn);
    vider_buffer();

    printf("ID étudiant: ");
    scanf("%19s", id_etudiant);
    vider_buffer();

    int trouve = 0;
    for (int i = 0; i < bib->nb_emprunts; i++) {
        if (bib->emprunts[i].actif &&
            strcmp(bib->emprunts[i].isbn, isbn) == 0 &&
            strcmp(bib->emprunts[i].id_etudiant, id_etudiant) == 0) {

            obtenir_date_actuelle(bib->emprunts[i].date_retour_effective);
            bib->emprunts[i].actif = 0;

            int idx_livre = trouver_livre_par_isbn(bib, isbn);
            if (idx_livre != -1) {
                bib->livres[idx_livre].disponible = 1;
            }

            int idx_user = trouver_utilisateur(bib, id_etudiant);
            if (idx_user != -1) {
                bib->utilisateurs[idx_user].nb_emprunts_actifs--;
            }

            int jours_retard = calculer_jours_difference(
                bib->emprunts[i].date_retour_prevue,
                bib->emprunts[i].date_retour_effective
            );

            printf("\n-> Retour enregistre avec succes!\n");

            if (jours_retard > 0) {
                printf("!! RETARD: %d jours\n", jours_retard);
                printf("(Fonctionnalite penalites à implementer)\n");
            } else {
                printf("Retour dans les delais.\n");
            }

            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Erreur: Aucun emprunt actif trouvé pour ce livre et cet utilisateur!\n");
    }
}

void afficher_emprunts_actifs(Bibliotheque* bib) {
    int nb_actifs = 0;

    printf("\n=== EMPRUNTS EN COURS ===\n\n");

    for (int i = 0; i < bib->nb_emprunts; i++) {
        if (bib->emprunts[i].actif) {
            afficher_un_emprunt(&bib->emprunts[i], bib);
            nb_actifs++;
        }
    }

    if (nb_actifs == 0) {
        printf("Aucun emprunt en cours.\n");
    } else {
        printf("\nTotal: %d emprunt(s) en cours\n", nb_actifs);
    }
}

void verifier_retards(Bibliotheque* bib) {
    char date_actuelle[MAX_DATE];
    obtenir_date_actuelle(date_actuelle);

    int nb_retards = 0;

    printf("\n=== VERIFICATION DES RETARDS ===\n");
    printf("Date actuelle: %s\n\n", date_actuelle);

    for (int i = 0; i < bib->nb_emprunts; i++) {
        if (bib->emprunts[i].actif) {
            int jours = calculer_jours_difference(
                bib->emprunts[i].date_retour_prevue,
                date_actuelle
            );

            if (jours > 0) {
                printf("!! RETARD DETECTE:\n");
                afficher_un_emprunt(&bib->emprunts[i], bib);
                nb_retards++;
            }
        }
    }

    if (nb_retards == 0) {
        printf("-> Aucun retard detecte.\n");
    } else {
        printf("\nTotal: %d retard(s) detecte(s)\n", nb_retards);
    }
}
