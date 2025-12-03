
#include "exemplaire.h"
#include <stdio.h>
#include <string.h>
#include "livre.h"
#include "utils.h"

static int prochain_num_exemplaire = 1;

void initialiser_prochain_num_exemplaire(int prochain_num) {
    if (prochain_num < 1) {
        prochain_num_exemplaire = 1;
    } else {
        prochain_num_exemplaire = prochain_num;
    }
}

int trouver_exemplaire_par_num(Bibliotheque* bib, int num_exemplaire) {
    for (int i = 0; i < bib->nb_exemplaires; ++i) {
        if (bib->exemplaires[i].num_exemplaire == num_exemplaire) {
            return i;
        }
    }
    return -1;
}

void ajouter_exemplaire(Bibliotheque* bib) {
    if (bib->nb_exemplaires >= MAX_EXEMPLAIRES) {
        printf("Nombre maximum d'exemplaires atteint.\n");
        return;
    }
    char isbn[MAX_ISBN];
    printf("=== Ajouter un exemplaire ===\n");
    printf("ISBN du livre correspondant: ");
    scanf("%12s", isbn);
    vider_buffer();
    int livre_index = trouver_livre_par_isbn(bib, isbn);
    if (livre_index == -1) {
        printf("Livre introuvable. Veuillez d'abord ajouter le livre.\n");
        return;
    }
    Exemplaire newEx;
    newEx.num_exemplaire = prochain_num_exemplaire;
    prochain_num_exemplaire++;
    strcpy(newEx.isbn, isbn);
    // Date d'achat
    char date[MAX_DATE];
    printf("Date d'achat (JJ/MM/AAAA, laisser vide pour la date d'aujourd'hui): ");
    fgets(date, MAX_DATE, stdin);
    if (date[0] == '\n') {
        obtenir_date_actuelle(date);
    } else {
        // enlever le '\n'
        date[strcspn(date, "\n")] = '\0';
    }
    strncpy(newEx.date_achat, date, MAX_DATE);
    newEx.disponible = 1;
    // Ajouter à la liste des exemplaires
    bib->exemplaires[bib->nb_exemplaires] = newEx;
    bib->nb_exemplaires++;
    printf("Exemplaire ajoute (ID %d) avec succes.\n", newEx.num_exemplaire);
}

void supprimer_exemplaire(Bibliotheque* bib, int num_exemplaire) {
    int idx = trouver_exemplaire_par_num(bib, num_exemplaire);
    if (idx == -1) {
        printf("Exemplaire introuvable.\n");
        return;
    }
    // Si l'exemplaire est emprunté, on ne peut pas le supprimer
    if (bib->exemplaires[idx].disponible == 0) {
        printf("Impossible de supprimer : l'exemplaire %d est actuellement emprunte.\n", num_exemplaire);
        return;
    }
    // Supprimer l'exemplaire en décalant le tableau
    for (int j = idx; j < bib->nb_exemplaires - 1; ++j) {
        bib->exemplaires[j] = bib->exemplaires[j+1];
    }
    bib->nb_exemplaires--;
    printf("Exemplaire %d supprime.\n", num_exemplaire);
}

void modifier_exemplaire(Bibliotheque* bib) {
    if (bib->nb_exemplaires == 0) {
        printf("Aucun exemplaire a modifier.\n");
        return;
    }
    int num;
    printf("=== Modifier un exemplaire ===\n");
    printf("Numero de l'exemplaire a modifier: ");
    scanf("%d", &num);
    vider_buffer();
    int idx = trouver_exemplaire_par_num(bib, num);
    if (idx == -1) {
        printf("Exemplaire introuvable.\n");
        return;
    }
    Exemplaire* ex = &bib->exemplaires[idx];
    // Afficher les infos actuelles
    printf("Exemplaire %d - ISBN: %s, Date d'achat: %s, ", ex->num_exemplaire, ex->isbn, ex->date_achat);
    if (ex->disponible) {
        printf("Disponibilite: disponible\n");
    } else {
        printf("Disponibilite: emprunte\n");
    }
    // Proposer de modifier la date d'achat
    printf("Nouvelle date d'achat (laisser vide pour ne pas changer): ");
    char newDate[MAX_DATE];
    fgets(newDate, MAX_DATE, stdin);
    if (newDate[0] != '\n') {
        newDate[strcspn(newDate, "\n")] = '\0';
        // On pourrait ajouter une vérification du format ici
        strncpy(ex->date_achat, newDate, MAX_DATE);
    }
    printf("Exemplaire modifie avec succes.\n");
}

void afficher_exemplaires(Bibliotheque* bib) {
    printf("=== Liste des exemplaires (%d exemplaires) ===\n", bib->nb_exemplaires);
    if (bib->nb_exemplaires == 0) {
        printf("Aucun exemplaire.\n");
        return;
    }
    for (int i = 0; i < bib->nb_exemplaires; ++i) {
        Exemplaire* ex = &bib->exemplaires[i];
        // Trouver le titre du livre correspondant à l'ISBN
        int li = trouver_livre_par_isbn(bib, ex->isbn);
        char titre[MAX_TITRE];
        if (li != -1) {
            strncpy(titre, bib->livres[li].titre, MAX_TITRE);
        } else {
            strcpy(titre, "(Livre supprime)");
        }
        printf("Exemplaire %d: ISBN %s | Titre: %s | Date achat: %s | %s\n",
               ex->num_exemplaire, ex->isbn, titre, ex->date_achat,
               ex->disponible ? "Disponible" : "Emprunte");
    }
}
