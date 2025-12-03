#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "livre.h"
#include "utilisateur.h"
#include "exemplaire.h"
#include "emprunt.h"
#include "fichier.h"
#include "utils.h"

// ---------- AFFICHAGE DU MENU PRINCIPAL ----------
void afficher_menu_principal() {
    printf("\n---------------------------------------\n");
    printf("---  BIBLIOTHEQUE NUMERIQUE - MENU  ---\n");
    printf("---------------------------------------\n");
    printf(" 1. Gestion des livres\n");
    printf(" 2. Gestion des exemplaires\n");
    printf(" 3. Gestion des utilisateurs\n");
    printf(" 4. Gestion des emprunts\n");
    printf(" 5. Fonctionnalites avancees\n");
    printf(" 6. Sauvegarder les donnees\n");
    printf(" 0. Quitter\n");
    printf("---------------------------------------\n");
    printf("Choix: ");
}

// ---------- MENU LIVRES ----------
void menu_livres(Bibliotheque* bib) {
    int choix;
    do {
        printf("\n--- GESTION DES LIVRES ---\n");
        printf(" 1. Ajouter un livre\n");
        printf(" 2. Supprimer un livre\n");
        printf(" 3. Modifier un livre\n");
        printf(" 4. Rechercher un livre\n");
        printf(" 5. Afficher tous les livres\n");
        printf(" 6. Trier les livres\n");
        printf(" 0. Retour\n");
        printf("Choix: ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: ajouter_livre(bib); break;
            case 2: supprimer_livre(bib); break;
            case 3: modifier_livre(bib); break;
            case 4: rechercher_livre(bib); break;
            case 5: afficher_livres(bib); break;
            case 6: trier_livres(bib); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 0) pause_ecran();
    } while (choix != 0);
}

// ---------- MENU EXEMPLAIRES ----------
void menu_exemplaires(Bibliotheque* bib) {
    int choix;
    do {
        printf("\n--- GESTION DES EXEMPLAIRES ---\n");
        printf(" 1. Ajouter un exemplaire\n");
        printf(" 2. Supprimer un exemplaire\n");
        printf(" 3. Modifier un exemplaire\n");
        printf(" 4. Afficher tous les exemplaires\n");
        printf(" 0. Retour\n");
        printf("Choix: ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: ajouter_exemplaire(bib); break;
            case 2: {
                int num;
                printf("Numero de l'exemplaire a supprimer: ");
                if (scanf("%d", &num) == 1) {
                    vider_buffer();
                    supprimer_exemplaire(bib, num);
                } else {
                    printf("Entree invalide.\n");
                    vider_buffer();
                }
                break;
            }
            case 3: modifier_exemplaire(bib); break;
            case 4: afficher_exemplaires(bib); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 0) pause_ecran();
    } while (choix != 0);
}

// ---------- MENU UTILISATEURS ----------
void menu_utilisateurs(Bibliotheque* bib) {
    int choix;
    do {
        printf("\n--- GESTION DES UTILISATEURS ---\n");
        printf(" 1. Ajouter un utilisateur\n");
        printf(" 2. Supprimer un utilisateur\n");
        printf(" 3. Modifier un utilisateur\n");
        printf(" 4. Afficher tous les utilisateurs\n");
        printf(" 0. Retour\n");
        printf("Choix: ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: ajouter_utilisateur(bib); break;
            case 2: supprimer_utilisateur(bib); break;
            case 3: modifier_utilisateur(bib); break;
            case 4: afficher_utilisateurs(bib); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 0) pause_ecran();
    } while (choix != 0);
}

// ---------- MENU EMPRUNTS ----------
void menu_emprunts(Bibliotheque* bib) {
    int choix;
    do {
        printf("\n--- GESTION DES EMPRUNTS ---\n");
        printf(" 1. Emprunter un exemplaire\n");
        printf(" 2. Retourner un exemplaire\n");
        printf(" 3. Afficher les emprunts actifs\n");
        printf(" 4. Afficher les emprunts en cours\n");
        printf(" 5. Vérifier les retards\n");
        printf(" 0. Retour\n");
        printf("Choix: ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: emprunter_exemplaire(bib); break;
            case 2: retourner_exemplaire(bib); break;
            case 3: afficher_emprunts_actifs(bib); break;
            case 4: afficher_emprunts_en_cours(bib); break;
            case 5: verifier_retards(bib); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 0) pause_ecran();
    } while (choix != 0);
}

// ---------- MENU STATISTIQUES & HISTORIQUE ----------
void menu_fonctionnalites_avancees(Bibliotheque* bib) {
    int choix;
    do {
        printf("\n--- FONCTIONNALITES AVANCEES ---\n");
        printf(" 1. Statistiques (top livres, utilisateurs actifs...)\n");
        printf(" 2. Historique des emprunts par utilisateur\n");
        printf(" 0. Retour\n");
        printf("Choix: ");
        scanf("%d", &choix);
        vider_buffer();

        switch (choix) {
            case 1: afficher_statistiques(bib); break;
            case 2: historique_emprunts_utilisateur(bib); break;
            case 0: break;
            default: printf("Choix invalide.\n");
        }

        if (choix != 0) pause_ecran();
    } while (choix != 0);
}

// ---------- INITIALISATION DE LA BIBLIOTHEQUE ----------
void initialiser_bibliotheque(Bibliotheque* bib) {
    memset(bib, 0, sizeof(Bibliotheque));
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
            case 1: menu_livres(&bib); break;
            case 2: menu_exemplaires(&bib); break;
            case 3: menu_utilisateurs(&bib); break;
            case 4: menu_emprunts(&bib); break;
            case 5: menu_fonctionnalites_avancees(&bib); break;
            case 6: sauvegarder_donnees(&bib); pause_ecran(); break;
            case 0:
                printf("\nSauvegarde automatique...\n");
                sauvegarder_donnees(&bib);
                printf("-> Fin du programme. À bientôt !\n");
                break;
            default: printf("Choix invalide.\n"); pause_ecran(); break;
        }

    } while (choix != 0);

    return 0;
}
