// ============================================================================
// FICHIER: main.c
// Description: Programme principal avec menu interactif
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include "../structures.h"
#include "../include/livres.h"
#include "../include/utilisateurs.h"
#include "../include/emprunts.h"
#include "../fichiers.h"
#include "../utils.h"

void afficher_menu_principal() {
    printf("\n");
    printf("---------------------------------------\n");
    printf("---  BIBLIOTHEQUE NUMERIQUE - MENU  ---\n");
    printf("---------------------------------------\n");
    printf("  1. Gestion des livres\n");
    printf("  2. Gestion des utilisateurs\n");
    printf("  3. Gestion des emprunts\n");
    printf("  4. Sauvegarder les donnees\n");
    printf("  0. Quitter\n");
    printf("--------------------------------------\n");
    printf("Choix: ");
}

void menu_livres(Bibliotheque* bib) {
    int choix;

    do {
        printf("\n");
        printf("--------------------------------------\n");
        printf("------    GESTION DES LIVRES    ------\n");
        printf("--------------------------------------\n");
        printf("  1. Ajouter un livre\n");
        printf("  2. Supprimer un livre\n");
        printf("  3. Modifier un livre\n");
        printf("  4. Rechercher un livre\n");
        printf("  5. Afficher tous les livres\n");
        printf("  6. Trier les livres\n");
        printf("  0. Retour au menu principal\n");
        printf("--------------------------------------\n");
        printf("Choix: ");

        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                ajouter_livre(bib);
                break;
            case 2:
                supprimer_livre(bib);
                break;
            case 3:
                modifier_livre(bib);
                break;
            case 4:
                rechercher_livre(bib);
                break;
            case 5:
                afficher_livres(bib);
                break;
            case 6:
                trier_livres(bib);
                break;
            case 0:
                break;
            default:
                printf("Choix invalide!\n");
        }

        if (choix != 0) {
            pause_ecran();
        }

    } while (choix != 0);
}

void menu_utilisateurs(Bibliotheque* bib) {
    int choix;

    do {
        printf("\n");
        printf("--------------------------------------\n");
        printf("---   GESTION DES UTILISATEURS     ---\n");
        printf("--------------------------------------\n");
        printf("  1. Ajouter un utilisateur\n");
        printf("  2. Supprimer un utilisateur\n");
        printf("  3. Modifier un utilisateur\n");
        printf("  4. Afficher tous les utilisateurs\n");
        printf("  0. Retour au menu principal\n");
        printf("--------------------------------------\n");
        printf("Choix: ");

        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                ajouter_utilisateur(bib);
                break;
            case 2:
                supprimer_utilisateur(bib);
                break;
            case 3:
                modifier_utilisateur(bib);
                break;
            case 4:
                afficher_utilisateurs(bib);
                break;
            case 0:
                break;
            default:
                printf("Choix invalide!\n");
        }

        if (choix != 0) {
            pause_ecran();
        }

    } while (choix != 0);
}

void menu_emprunts(Bibliotheque* bib) {
    int choix;

    do {
        printf("\n");
        printf("--------------------------------------\n");
        printf("---     GESTION DES EMPRUNTS       ---\n");
        printf("--------------------------------------\n");
        printf("  1. Emprunter un livre\n");
        printf("  2. Retourner un livre\n");
        printf("  3. Afficher les emprunts en cours\n");
        printf("  4. Verifier les retards\n");
        printf("  0. Retour au menu principal\n");
        printf("--------------------------------------\n");
        printf("Choix: ");

        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                emprunter_livre(bib);
                break;
            case 2:
                retourner_livre(bib);
                break;
            case 3:
                afficher_emprunts_actifs(bib);
                break;
            case 4:
                verifier_retards(bib);
                break;
            case 0:
                break;
            default:
                printf("Choix invalide!\n");
        }

        if (choix != 0) {
            pause_ecran();
        }

    } while (choix != 0);
}

void initialiser_bibliotheque(Bibliotheque* bib) {
    bib->nb_livres = 0;
    bib->nb_utilisateurs = 0;
    bib->nb_emprunts = 0;
    bib->prochain_id_emprunt = 1;
}

int main() {
    Bibliotheque bib;
    int choix;

    printf("------------------------------------------\n");
    printf("---   BIBLIOTHEQUE NUMERIQUE AVANCEE   ---\n");
    printf("--- Projet C & Base de Donnees 2025/26 ---\n");
    printf("------------------------------------------\n");

    initialiser_bibliotheque(&bib);
    charger_donnees(&bib);

    do {
        afficher_menu_principal();
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1:
                menu_livres(&bib);
                break;
            case 2:
                menu_utilisateurs(&bib);
                break;
            case 3:
                menu_emprunts(&bib);
                break;
            case 4:
                sauvegarder_donnees(&bib);
                pause_ecran();
                break;
            case 0:
                printf("\nSauvegarde automatique...\n");
                sauvegarder_donnees(&bib);
                printf("\n-> Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
                pause_ecran();
        }

    } while (choix != 0);

    return 0;
}