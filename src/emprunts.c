// ============================================================================
// FICHIER: emprunts.c
// Description: Implémentation de la gestion des emprunts
// ============================================================================

#include <stdio.h>
#include <string.h>
#include "../include/emprunts.h"
#include "../include/livres.h"
#include "../include/utilisateurs.h"
#include "../include/utils.h"

// ---------------------------------------------------------------------------
//  Helper : recherche d'un exemplaire par ISBN
//  (suppose que Bibliotheque contient : Exemplaire exemplaires[] et int nb_exemplaires)
//  et que Exemplaire a un champ ISBN de type char[MAX_ISBN].
// ---------------------------------------------------------------------------
static int trouver_exemplaire_par_isbn(Bibliotheque* bib, const char* isbn) {
    for (int i = 0; i < bib->nb_exemplaires; i++) {
        if (strcmp(bib->exemplaires[i].ISBN, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

// ---------------------------------------------------------------------------
//  Affichage d'un emprunt
// ---------------------------------------------------------------------------
void afficher_un_emprunt(Emprunt* emp, Bibliotheque* bib) {
    int idx_livre = trouver_livre_par_isbn(bib, emp->isbn);
    int idx_user  = trouver_utilisateur(bib, emp->id_utilisateur);

    printf("ID Emprunt      : %d\n", emp->id_emprunt);
    printf("ISBN            : %s\n", emp->isbn);

    if (idx_livre != -1) {
        printf("Livre           : %s\n", bib->livres[idx_livre].titre);
    } else {
        printf("Livre           : [inconnu]\n");
    }

    if (idx_user != -1) {
        printf("Utilisateur     : %s %s (%s)\n",
               bib->utilisateurs[idx_user].prenom,
               bib->utilisateurs[idx_user].nom,
               bib->utilisateurs[idx_user].id_utilisateur);
    } else {
        printf("Utilisateur     : [inconnu]\n");
    }

    printf("Date emprunt    : %s\n", emp->date_emprunt);
    printf("Retour prevu    : %s\n", emp->date_retour_prevue);

    if (emp->actif) {
        char date_actuelle[MAX_DATE];
        obtenir_date_actuelle(date_actuelle);
        int jours = calculer_jours_difference(emp->date_retour_prevue, date_actuelle);

        if (jours < 0) {
            printf("Statut          : Emprunt en cours (dans les delais)\n");
        } else if (jours == 0) {
            printf("Statut          : Dernier jour avant retard\n");
        } else {
            printf("Statut          : EN RETARD de %d jour(s)\n", jours);
        }
    } else {
        printf("Retour effectif : %s\n", emp->date_retour_effective);
        int jours = calculer_jours_difference(emp->date_retour_prevue,
                                              emp->date_retour_effective);
        if (jours > 0) {
            printf("Statut          : Retour en retard (%d jour(s))\n", jours);
        } else {
            printf("Statut          : Retour dans les delais\n");
        }
    }

    printf("------------------------------------------------------------\n");
}

// ---------------------------------------------------------------------------
//  Afficher tous les emprunts actifs
// ---------------------------------------------------------------------------
void afficher_emprunts_en_cours(Bibliotheque* bib) {
    printf("\n=== EMPRUNTS EN COURS ===\n");

    int nb = 0;
    for (int i = 0; i < bib->nb_emprunts; i++) {
        if (bib->emprunts[i].actif) {
            afficher_un_emprunt(&bib->emprunts[i], bib);
            nb++;
        }
    }

    if (nb == 0) {
        printf("-> Aucun emprunt en cours.\n");
    } else {
        printf("Total: %d emprunt(s) en cours.\n", nb);
    }
}
void afficher_emprunts_actifs(Bibliotheque* bib) {
    afficher_emprunts_en_cours(bib);
}

// ---------------------------------------------------------------------------
//  EMPRUNTER UN EXEMPLAIRE
//  (fonction garde le nom emprunter_livre mais travaille sur la table Exemplaire)
// ---------------------------------------------------------------------------
void emprunter_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];
    char id_etudiant[MAX_ID];

    printf("\n=== EMPRUNTER UN EXEMPLAIRE ===\n");

    printf("ISBN du livre (pour l'exemplaire): ");
    scanf("%13s", isbn);
    vider_buffer();

    // Recherche d'un exemplaire correspondant à cet ISBN
    int idx_ex = trouver_exemplaire_par_isbn(bib, isbn);
    if (idx_ex == -1) {
        printf("Erreur: aucun exemplaire enregistre pour cet ISBN !\n");
        return;
    }

    // Vérifier le stock / disponibilité
    if (!bib->exemplaires[idx_ex].disponible ||
        bib->exemplaires[idx_ex].stock_expemplaire <= 0) {
        printf("Erreur: aucun exemplaire disponible pour cet ISBN !\n");
        return;
    }

    printf("ID etudiant: ");
    scanf("%19s", id_etudiant);
    vider_buffer();

    int idx_user = trouver_utilisateur(bib, id_etudiant);
    if (idx_user == -1) {
        printf("Erreur: Utilisateur non trouve !\n");
        return;
    }

    if (bib->utilisateurs[idx_user].nb_emprunts_actifs >= MAX_EMPRUNTS_PAR_USER) {
        printf("Erreur: L'utilisateur a atteint la limite de %d emprunt(s) !\n",
               MAX_EMPRUNTS_PAR_USER);
        return;
    }

    if (bib->nb_emprunts >= MAX_EMPRUNTS) {
        printf("Erreur: Capacite maximale d'emprunts atteinte !\n");
        return;
    }

    // Création de l'emprunt (on continue d'enregistrer l'ISBN comme avant)
    Emprunt nouveau;
    nouveau.id_emprunt = bib->prochain_id_emprunt++;
    strcpy(nouveau.isbn, isbn);
    strcpy(nouveau.id_utilisateur, id_etudiant);
    obtenir_date_actuelle(nouveau.date_emprunt);
    ajouter_jours(nouveau.date_emprunt, DUREE_EMPRUNT, nouveau.date_retour_prevue);
    strcpy(nouveau.date_retour_effective, "");
    nouveau.actif = 1;

    bib->emprunts[bib->nb_emprunts] = nouveau;
    bib->nb_emprunts++;

    // Mise à jour de la table des exemplaires
    bib->exemplaires[idx_ex].stock_expemplaire--;
    if (bib->exemplaires[idx_ex].stock_expemplaire <= 0) {
        bib->exemplaires[idx_ex].disponible = 0;
    }

    // Mise à jour du compteur d'emprunts de l'utilisateur
    bib->utilisateurs[idx_user].nb_emprunts_actifs++;

    printf("\n-> Emprunt d'exemplaire enregistre avec succes !\n");
    printf("Date de retour prevue: %s\n", nouveau.date_retour_prevue);
}

// ---------------------------------------------------------------------------
//  RETOURNER UN EXEMPLAIRE
//  (fonction garde le nom retourner_livre mais travaille sur Exemplaire)
// ---------------------------------------------------------------------------
void retourner_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];
    char id_etudiant[MAX_ID];

    printf("\n=== RETOURNER UN EXEMPLAIRE ===\n");

    printf("ISBN du livre (de l'exemplaire): ");
    scanf("%13s", isbn);
    vider_buffer();

    printf("ID etudiant: ");
    scanf("%19s", id_etudiant);
    vider_buffer();

    int trouve = 0;

    for (int i = 0; i < bib->nb_emprunts; i++) {
        if (bib->emprunts[i].actif &&
            strcmp(bib->emprunts[i].isbn, isbn) == 0 &&
            strcmp(bib->emprunts[i].id_utilisateur, id_etudiant) == 0) {

            // Marquer le retour
            obtenir_date_actuelle(bib->emprunts[i].date_retour_effective);
            bib->emprunts[i].actif = 0;

            // Mise à jour de la table des exemplaires
            int idx_ex = trouver_exemplaire_par_isbn(bib, isbn);
            if (idx_ex != -1) {
                bib->exemplaires[idx_ex].stock_expemplaire++;
                bib->exemplaires[idx_ex].disponible = 1;
            }

            // Mise à jour du compteur d'emprunts de l'utilisateur
            int idx_user = trouver_utilisateur(bib, id_etudiant);
            if (idx_user != -1) {
                bib->utilisateurs[idx_user].nb_emprunts_actifs--;
            }

            // Gestion du retard
            int jours_retard = calculer_jours_difference(
                bib->emprunts[i].date_retour_prevue,
                bib->emprunts[i].date_retour_effective
            );

            printf("\n-> Retour d'exemplaire enregistre avec succes !\n");

            if (jours_retard > 0) {
                printf("!! RETARD: %d jour(s)\n", jours_retard);
                printf("(Fonctionnalite penalites a implementer)\n");
            } else {
                printf("Retour dans les delais.\n");
            }

            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Erreur: Aucun emprunt actif trouve pour cet exemplaire et cet utilisateur !\n");
    }
}

// ---------------------------------------------------------------------------
//  Vérifier les retards (sur les emprunts actifs)
// ---------------------------------------------------------------------------
void verifier_retards(Bibliotheque* bib) {
    printf("\n=== VERIFICATION DES RETARDS ===\n");

    char date_actuelle[MAX_DATE];
    obtenir_date_actuelle(date_actuelle);

    int nb_retards = 0;

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
