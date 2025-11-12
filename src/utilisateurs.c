// ============================================================================
// FICHIER: utilisateurs.c
// Description: Implémentation de la gestion des utilisateurs
// ============================================================================
// TEST 1 heremanou
#include <stdio.h>
#include <string.h>
#include "../include/utilisateurs.h"
#include "../include/utils.h"

void afficher_un_utilisateur(Utilisateur* user) {
    printf("ID: %s\n", user->id_utilisateur);
    printf("Nom: %s %s\n", user->prenom, user->nom);
    printf("Email: %s\n", user->email);
    printf("Emprunts actifs: %d/%d\n", user->nb_emprunts_actifs, MAX_EMPRUNTS_PAR_USER);
    printf("----------------------------------------\n");
}

int trouver_utilisateur(Bibliotheque* bib, const char* id_etudiant) {
    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        if (strcmp(bib->utilisateurs[i].id_utilisateur, id_etudiant) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_utilisateur(Bibliotheque* bib) {
    if (bib->nb_utilisateurs >= MAX_UTILISATEURS) {
        printf("Erreur: Capacite maximale atteinte!\n");
        return;
    }

    Utilisateur nouveau;

    printf("\n=== AJOUTER UN UTILISATEUR ===\n");

    printf("ID etudiant: ");
    scanf("%19s", nouveau.id_utilisateur);
    vider_buffer();

    if (trouver_utilisateur(bib, nouveau.id_utilisateur) != -1) {
        printf("Erreur: Cet ID etudiant existe deja!\n");
        return;
    }

    printf("Nom: ");
    fgets(nouveau.nom, MAX_NOM, stdin);
    nouveau.nom[strcspn(nouveau.nom, "\n")] = 0;

    printf("Prenom: ");
    fgets(nouveau.prenom, MAX_NOM, stdin);
    nouveau.prenom[strcspn(nouveau.prenom, "\n")] = 0;

    printf("Email: ");
    fgets(nouveau.email, MAX_EMAIL, stdin);
    nouveau.email[strcspn(nouveau.email, "\n")] = 0;

    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        if (strcmp(bib->utilisateurs[i].email, nouveau.email) == 0) {
            printf("Erreur: Cet email est deja utilise!\n");
            return;
        }
    }

    nouveau.nb_emprunts_actifs = 0;

    bib->utilisateurs[bib->nb_utilisateurs] = nouveau;
    bib->nb_utilisateurs++;

    printf("\n-> Utilisateur ajoute avec succes!\n");
}

void supprimer_utilisateur(Bibliotheque* bib) {
    char id[MAX_ID];

    printf("\n=== SUPPRIMER UN UTILISATEUR ===\n");
    printf("ID etudiant: ");
    scanf("%19s", id);
    vider_buffer();

    int index = trouver_utilisateur(bib, id);

    if (index == -1) {
        printf("Erreur: Utilisateur non trouve!\n");
        return;
    }

    if (bib->utilisateurs[index].nb_emprunts_actifs > 0) {
        printf("Erreur: L'utilisateur a des emprunts en cours!\n");
        return;
    }

    for (int i = index; i < bib->nb_utilisateurs - 1; i++) {
        bib->utilisateurs[i] = bib->utilisateurs[i + 1];
    }

    bib->nb_utilisateurs--;
    printf("\n-> Utilisateur supprime avec succes!\n");
}

void modifier_utilisateur(Bibliotheque* bib) {
    char id[MAX_ID];

    printf("\n=== MODIFIER UN UTILISATEUR ===\n");
    printf("ID etudiant: ");
    scanf("%19s", id);
    vider_buffer();

    int index = trouver_utilisateur(bib, id);

    if (index == -1) {
        printf("Erreur: Utilisateur non trouve!\n");
        return;
    }

    Utilisateur* user = &bib->utilisateurs[index];

    printf("\nUtilisateur actuel:\n");
    afficher_un_utilisateur(user);

    printf("\nQue souhaitez-vous modifier?\n");
    printf("1. Nom\n");
    printf("2. Prenom\n");
    printf("3. Email\n");
    printf("0. Annuler\n");
    printf("Choix: ");

    int choix;
    scanf("%d", &choix);
    vider_buffer();

    switch (choix) {
        case 1:
            printf("Nouveau nom: ");
            fgets(user->nom, MAX_NOM, stdin);
            user->nom[strcspn(user->nom, "\n")] = 0;
            break;
        case 2:
            printf("Nouveau prenom: ");
            fgets(user->prenom, MAX_NOM, stdin);
            user->prenom[strcspn(user->prenom, "\n")] = 0;
            break;
        case 3:
            printf("Nouvel email: ");
            fgets(user->email, MAX_EMAIL, stdin);
            user->email[strcspn(user->email, "\n")] = 0;
            break;
        case 0:
            return;
        default:
            printf("Choix invalide!\n");
            return;
    }

    printf("\n-> Utilisateur modifie avec succes!\n");
}

void afficher_utilisateurs(Bibliotheque* bib) {
    if (bib->nb_utilisateurs == 0) {
        printf("\nAucun utilisateur enregistre.\n");
        return;
    }

    printf("\n=== LISTE DES UTILISATEURS (%d) ===\n\n", bib->nb_utilisateurs);

    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        printf("%d. ", i + 1);
        afficher_un_utilisateur(&bib->utilisateurs[i]);
    }
}
