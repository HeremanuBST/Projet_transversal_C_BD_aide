#include "utilisateur.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"

int trouver_utilisateur(Bibliotheque* bib, const char* id) {
    for (int i = 0; i < bib->nb_utilisateurs; ++i) {
        if (strcmp(bib->utilisateurs[i].id_utilisateur, id) == 0) {
            return i;
        }
    }
    return -1;
}

void afficher_un_utilisateur(const Utilisateur* user) {
    if (user == NULL) {
        return;
    }
    printf("ID: %s | Nom: %s %s | Email: %s | Emprunts actifs: %d\n",
           user->id_utilisateur, user->prenom, user->nom, user->email, user->nb_emprunts_actifs);
}

void ajouter_utilisateur(Bibliotheque* bib) {
    if (bib->nb_utilisateurs >= MAX_UTILISATEURS) {
        printf("Nombre maximum d'utilisateurs atteint.\n");
        return;
    }
    Utilisateur newUser;
    printf("=== Ajouter un utilisateur ===\n");
    printf("ID utilisateur: ");
    scanf("%9s", newUser.id_utilisateur);
    vider_buffer();
    // Vérifier unicité de l'ID
    if (trouver_utilisateur(bib, newUser.id_utilisateur) != -1) {
        printf("Un utilisateur avec cet ID existe deja.\n");
        return;
    }
    printf("Nom: ");
    fgets(newUser.nom, MAX_NOM, stdin);
    newUser.nom[strcspn(newUser.nom, "\n")] = '\0';
    printf("Prenom: ");
    fgets(newUser.prenom, MAX_NOM, stdin);
    newUser.prenom[strcspn(newUser.prenom, "\n")] = '\0';
    printf("Email: ");
    fgets(newUser.email, MAX_EMAIL, stdin);
    newUser.email[strcspn(newUser.email, "\n")] = '\0';
    newUser.nb_emprunts_actifs = 0;
    bib->utilisateurs[bib->nb_utilisateurs] = newUser;
    bib->nb_utilisateurs++;
    printf("Utilisateur ajoute avec succes.\n");
}

void supprimer_utilisateur(Bibliotheque* bib) {
    if (bib->nb_utilisateurs == 0) {
        printf("Aucun utilisateur a supprimer.\n");
        return;
    }
    char id[MAX_ID];
    printf("=== Supprimer un utilisateur ===\n");
    printf("ID de l'utilisateur a supprimer: ");
    scanf("%9s", id);
    vider_buffer();
    int idx = trouver_utilisateur(bib, id);
    if (idx == -1) {
        printf("Utilisateur non trouve.\n");
        return;
    }
    Utilisateur* user = &bib->utilisateurs[idx];
    if (user->nb_emprunts_actifs > 0) {
        printf("Impossible de supprimer : cet utilisateur a des emprunts en cours.\n");
        return;
    }
    // Décaler le tableau pour supprimer l'utilisateur
    for (int j = idx; j < bib->nb_utilisateurs - 1; ++j) {
        bib->utilisateurs[j] = bib->utilisateurs[j+1];
    }
    bib->nb_utilisateurs--;
    printf("Utilisateur supprime avec succes.\n");
}

void modifier_utilisateur(Bibliotheque* bib) {
    if (bib->nb_utilisateurs == 0) {
        printf("Aucun utilisateur a modifier.\n");
        return;
    }
    char id[MAX_ID];
    printf("=== Modifier un utilisateur ===\n");
    printf("ID de l'utilisateur a modifier: ");
    scanf("%9s", id);
    vider_buffer();
    int idx = trouver_utilisateur(bib, id);
    if (idx == -1) {
        printf("Utilisateur non trouve.\n");
        return;
    }
    Utilisateur* user = &bib->utilisateurs[idx];
    char buffer[256];
    printf("Nouveau nom (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(user->nom, buffer, MAX_NOM);
    }
    printf("Nouveau prenom (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(user->prenom, buffer, MAX_NOM);
    }
    printf("Nouvel email (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = '\0';
        strncpy(user->email, buffer, MAX_EMAIL);
    }
    printf("Utilisateur modifie avec succes.\n");
}

void afficher_utilisateurs(Bibliotheque* bib) {
    printf("=== Liste des utilisateurs (%d utilisateurs) ===\n", bib->nb_utilisateurs);
    if (bib->nb_utilisateurs == 0) {
        printf("Aucun utilisateur.\n");
        return;
    }
    for (int i = 0; i < bib->nb_utilisateurs; ++i) {
        printf("%d. ", i+1);
        afficher_un_utilisateur(&bib->utilisateurs[i]);
    }
}
