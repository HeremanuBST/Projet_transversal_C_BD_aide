// ============================================================================
// FICHIER: livres.c
// Description: Implémentation de la gestion des livres
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/livres.h"
#include "../include/utils.h"

void afficher_un_livre(Livre* livre) {
    printf("ISBN: %s\n", livre->isbn);
    printf("Titre: %s\n", livre->titre);
    printf("Auteur: %s\n", livre->auteur);
    printf("Annee: %d\n", livre->annee);
    printf("Categorie: %s\n", livre->categorie);
    printf("Disponibilite: %s\n", livre->disponible ? "Disponible" : "Emprunte");
    printf("----------------------------------------\n");
}

int trouver_livre_par_isbn(Bibliotheque* bib, const char* isbn) {
    for (int i = 0; i < bib->nb_livres; i++) {
        if (strcmp(bib->livres[i].isbn, isbn) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_livre(Bibliotheque* bib) {
    if (bib->nb_livres >= MAX_LIVRES) {
        printf("Erreur: Capacite maximale atteinte!\n");
        return;
    }

    Livre nouveau;

    printf("\n=== AJOUTER UN LIVRE ===\n");

    printf("ISBN (13 chiffres): ");
    scanf("%s", nouveau.isbn);
    vider_buffer();

    if (trouver_livre_par_isbn(bib, nouveau.isbn) != -1) {
        printf("Erreur: Un livre avec cet ISBN existe deja!\n");
        return;
    }

    printf("Titre: ");
    fgets(nouveau.titre, MAX_TITRE, stdin);
    nouveau.titre[strcspn(nouveau.titre, "\n")] = 0;

    printf("Auteur: ");
    fgets(nouveau.auteur, MAX_AUTEUR, stdin);
    nouveau.auteur[strcspn(nouveau.auteur, "\n")] = 0;

    printf("Annee: ");
    scanf("%d", &nouveau.annee);
    vider_buffer();

    printf("Categorie: ");
    fgets(nouveau.categorie, MAX_CATEGORIE, stdin);
    nouveau.categorie[strcspn(nouveau.categorie, "\n")] = 0;

    nouveau.disponible = 1;

    bib->livres[bib->nb_livres] = nouveau;
    bib->nb_livres++;

    printf("\n-> Livre ajoute avec succes!\n");
}

void supprimer_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];

    printf("\n=== SUPPRIMER UN LIVRE ===\n");
    printf("ISBN du livre a supprimer: ");
    scanf("%13s", isbn);
    vider_buffer();

    int index = trouver_livre_par_isbn(bib, isbn);

    if (index == -1) {
        printf("Erreur: Livre non trouve!\n");
        return;
    }

    if (!bib->livres[index].disponible) {
        printf("Erreur: Le livre est actuellement emprunte!\n");
        return;
    }

    for (int i = index; i < bib->nb_livres - 1; i++) {
        bib->livres[i] = bib->livres[i + 1];
    }

    bib->nb_livres--;
    printf("\n-> Livre supprime avec succes!\n");
}

void modifier_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];

    printf("\n=== MODIFIER UN LIVRE ===\n");
    printf("ISBN du livre a modifier: ");
    scanf("%13s", isbn);
    vider_buffer();

    int index = trouver_livre_par_isbn(bib, isbn);

    if (index == -1) {
        printf("Erreur: Livre non trouve!\n");
        return;
    }

    Livre* livre = &bib->livres[index];

    printf("\nLivre actuel:\n");
    afficher_un_livre(livre);

    printf("\nQue souhaitez-vous modifier?\n");
    printf("1. Titre\n");
    printf("2. Auteur\n");
    printf("3. Annee\n");
    printf("4. Categorie\n");
    printf("0. Annuler\n");
    printf("Choix: ");

    int choix;
    scanf("%d", &choix);
    vider_buffer();

    switch (choix) {
        case 1:
            printf("Nouveau titre: ");
            fgets(livre->titre, MAX_TITRE, stdin);
            livre->titre[strcspn(livre->titre, "\n")] = 0;
            break;
        case 2:
            printf("Nouvel auteur: ");
            fgets(livre->auteur, MAX_AUTEUR, stdin);
            livre->auteur[strcspn(livre->auteur, "\n")] = 0;
            break;
        case 3:
            printf("Nouvelle annee: ");
            scanf("%d", &livre->annee);
            vider_buffer();
            break;
        case 4:
            printf("Nouvelle categorie: ");
            fgets(livre->categorie, MAX_CATEGORIE, stdin);
            livre->categorie[strcspn(livre->categorie, "\n")] = 0;
            break;
        case 0:
            return;
        default:
            printf("Choix invalide!\n");
            return;
    }

    printf("\n-> Livre modifie avec succes!\n");
}

void rechercher_livre(Bibliotheque* bib) {
    printf("\n=== RECHERCHER UN LIVRE ===\n");
    printf("1. Par ISBN\n");
    printf("2. Par titre\n");
    printf("3. Par auteur\n");
    printf("4. Par categorie\n");
    printf("Choix: ");

    int choix;
    scanf("%d", &choix);
    vider_buffer();

    char critere[MAX_TITRE];
    int trouve = 0;

    switch (choix) {
        case 1:
            printf("ISBN: ");
            scanf("%13s", critere);
            vider_buffer();

            for (int i = 0; i < bib->nb_livres; i++) {
                if (strcmp(bib->livres[i].isbn, critere) == 0) {
                    printf("\nResultat:\n");
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        case 2:
            printf("Titre (ou partie): ");
            fgets(critere, MAX_TITRE, stdin);
            critere[strcspn(critere, "\n")] = 0;

            printf("\nResultats:\n");
            for (int i = 0; i < bib->nb_livres; i++) {
                if (strstr(bib->livres[i].titre, critere) != NULL) {
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        case 3:
            printf("Auteur (ou partie): ");
            fgets(critere, MAX_AUTEUR, stdin);
            critere[strcspn(critere, "\n")] = 0;

            printf("\nResultats:\n");
            for (int i = 0; i < bib->nb_livres; i++) {
                if (strstr(bib->livres[i].auteur, critere) != NULL) {
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        case 4:
            printf("Categorie: ");
            fgets(critere, MAX_CATEGORIE, stdin);
            critere[strcspn(critere, "\n")] = 0;

            printf("\nResultats:\n");
            for (int i = 0; i < bib->nb_livres; i++) {
                if (strcmp(bib->livres[i].categorie, critere) == 0) {
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        default:
            printf("Choix invalide!\n");
            return;
    }

    if (!trouve) {
        printf("Aucun livre trouve.\n");
    }
}

void afficher_livres(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("\nAucun livre dans la bibliotheque.\n");
        return;
    }

    printf("\n=== LISTE DES LIVRES (%d) ===\n\n", bib->nb_livres);

    for (int i = 0; i < bib->nb_livres; i++) {
        printf("%d. ", i + 1); // Pour pouvoir
        afficher_un_livre(&bib->livres[i]);
    }
}

void trier_livres(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("\nAucun livre a trier.\n");
        return;
    }

    printf("\n=== TRIER LES LIVRES ===\n");
    printf("1. Par titre\n");
    printf("2. Par auteur\n");
    printf("3. Par annee\n");
    printf("Choix: ");

    int choix;
    scanf("%d", &choix);
    vider_buffer();

    Livre temp;

    for (int i = 0; i < bib->nb_livres - 1; i++) {
        for (int j = 0; j < bib->nb_livres - i - 1; j++) {
            int echanger = 0;

            switch (choix) {
                case 1:
                    echanger = strcmp(bib->livres[j].titre, bib->livres[j + 1].titre) > 0;
                    break;
                case 2:
                    echanger = strcmp(bib->livres[j].auteur, bib->livres[j + 1].auteur) > 0;
                    break;
                case 3:
                    echanger = bib->livres[j].annee > bib->livres[j + 1].annee;
                    break;
                default:
                    printf("Choix invalide!\n");
                    return;
            }

            if (echanger) {
                temp = bib->livres[j];
                bib->livres[j] = bib->livres[j + 1];
                bib->livres[j + 1] = temp;
            }
        }
    }

    printf("\n-> Livres tries avec succes!\n");
    afficher_livres(bib);
}
