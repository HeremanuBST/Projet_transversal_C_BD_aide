
#include "livre.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "exemplaire.h"

// Fonction interne : retirer le '\n' final d'une chaîne (si présent)
static void enlever_retour_ligne(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int trouver_livre_par_isbn(Bibliotheque* bib, const char* isbn) {
    for (int i = 0; i < bib->nb_livres; ++i) {
        if (strcmp(bib->livres[i].isbn, isbn) == 0) { //Ici on compare deux chaines de caractères
            return i;
        }
    }
    return -1;
}

void afficher_un_livre(const Livre* livre) {
    if (livre == NULL) {
        return;
    }
    printf("ISBN: %s | Titre: %s | Auteur: %s | Categorie: %s | Annee: %d\n", livre->isbn, livre->titre, livre->auteur, livre->categorie, livre->annee);
}

void ajouter_livre(Bibliotheque* bib) {
    if (bib->nb_livres >= MAX_LIVRES) {
        printf("La bibliotheque a atteint le nombre maximum de livres.\n");
        return;
    }

    Livre nouveau;  // Saisie des infos du livre
    printf("=== Ajouter un livre ===\n");
    printf("ISBN (13 caracteres max): ");
    scanf("%12s", nouveau.isbn);
    vider_buffer();
    // Vérifier si l'ISBN existe déjà
    if (trouver_livre_par_isbn(bib, nouveau.isbn) != -1) {
        printf("Un livre avec cet ISBN existe deja. Ajoutez un exemplaire au lieu d'un nouveau livre.\n");
        return;
    }
    printf("Titre: ");
    fgets(nouveau.titre, MAX_TITRE, stdin);
    enlever_retour_ligne(nouveau.titre);
    printf("Auteur: ");
    fgets(nouveau.auteur, MAX_AUTEUR, stdin);
    enlever_retour_ligne(nouveau.auteur);
    printf("Categorie: ");
    fgets(nouveau.categorie, MAX_CATEGORIE, stdin);
    enlever_retour_ligne(nouveau.categorie);
    printf("Annee de parution: ");
    scanf("%d", &nouveau.annee);
    vider_buffer();
    // Ajouter le livre dans la structure
    bib->livres[bib->nb_livres] = nouveau;
    bib->nb_livres++;
    printf("Livre ajoute avec succes.\n");
}

void supprimer_livre(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("Aucun livre a supprimer.\n");
        return;
    }
    char isbn[MAX_ISBN];
    printf("=== Supprimer un livre ===\n");
    printf("ISBN du livre a supprimer: ");
    scanf("%12s", isbn);
    vider_buffer();
    int idx = trouver_livre_par_isbn(bib, isbn);
    if (idx == -1) {
        printf("Livre non trouve.\n");
        return;
    }
    // Vérifier s'il existe des exemplaires empruntés de ce livre
    for (int i = 0; i < bib->nb_exemplaires; ++i) {
        if (strcmp(bib->exemplaires[i].isbn, isbn) == 0 && bib->exemplaires[i].disponible == 0) {
            printf("Impossible de supprimer ce livre : au moins un exemplaire est emprunte actuellement.\n");
            return;
        }
    }
    // Supprimer tous les exemplaires de ce livre
    for (int i = 0; i < bib->nb_exemplaires; ) {
        if (strcmp(bib->exemplaires[i].isbn, isbn) == 0) {
            // Supprimer cet exemplaire (appel à la fonction correspondante)
            supprimer_exemplaire(bib, bib->exemplaires[i].num_exemplaire);
            // Ne pas incrémenter i ici car la liste a été décalée après suppression
        } else {
            i++;
        }
    }
    // Supprimer le livre de la liste des livres (en décalant le tableau)
    for (int j = idx; j < bib->nb_livres - 1; ++j) {
        bib->livres[j] = bib->livres[j+1];
    }
    bib->nb_livres--;
    printf("Livre supprime avec succes.\n");
}

void modifier_livre(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("Aucun livre a modifier.\n");
        return;
    }
    char isbn[MAX_ISBN];
    printf("=== Modifier un livre ===\n");
    printf("ISBN du livre a modifier: ");
    scanf("%12s", isbn);
    vider_buffer();
    int idx = trouver_livre_par_isbn(bib, isbn);
    if (idx == -1) {
        printf("Livre non trouve.\n");
        return;
    }
    Livre* livre = &bib->livres[idx];
    // Saisie des nouvelles valeurs (laisser vide pour ne pas changer)
    char buffer[256];
    printf("Nouveau titre (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        enlever_retour_ligne(buffer);
        strncpy(livre->titre, buffer, MAX_TITRE);
    }
    printf("Nouvel auteur (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        enlever_retour_ligne(buffer);
        strncpy(livre->auteur, buffer, MAX_AUTEUR);
    }
    printf("Nouvelle categorie (laisser vide pour ne pas changer): ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        enlever_retour_ligne(buffer);
        strncpy(livre->categorie, buffer, MAX_CATEGORIE);
    }
    printf("Nouvelle annee de parution (0 pour ne pas changer): ");
    int an;
    scanf("%d", &an);
    vider_buffer();
    if (an != 0) {
        livre->annee = an;
    }
    printf("Livre modifie avec succes.\n");
}

void rechercher_livre(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }
    char recherche[256];
    printf("=== Rechercher un livre ===\n");
    printf("Entrez un ISBN ou un mot-cle (titre/auteur/categorie): ");
    fgets(recherche, sizeof(recherche), stdin);
    enlever_retour_ligne(recherche);
    if (strlen(recherche) == 0) {
        printf("Recherche vide.\n");
        return;
    }
    // Si la recherche correspond exactement à 13 caractères, on suppose que c'est un ISBN
    if (strlen(recherche) == 13) {
        int idx = trouver_livre_par_isbn(bib, recherche);
        if (idx != -1) {
            printf("Livre trouve:\n");
            afficher_un_livre(&bib->livres[idx]);
            // Afficher la disponibilité (nombre d'exemplaires disponibles/total pour ce livre)
            {
                int total_ex = 0, dispo_ex = 0;
                for (int j = 0; j < bib->nb_exemplaires; ++j) {
                    if (strcmp(bib->exemplaires[j].isbn, recherche) == 0) {
                        total_ex++;
                        if (bib->exemplaires[j].disponible) dispo_ex++;
                    }
                }
                if (total_ex > 0) {
                    printf("   Exemplaires: %d (disponibles: %d)\n", total_ex, dispo_ex);
                } else {
                    printf("   Aucun exemplaire dans la bibliotheque pour ce livre.\n");
                }
            }
        } else {
            printf("Aucun livre trouve avec cet ISBN.\n");
        }
    } else {
        // Recherche par mot-clé dans titre, auteur ou catégorie (insensible à la casse)
        char tablecherche[256];
        strncpy(tablecherche, recherche, sizeof(tablecherche));
        for (char* p = tablecherche; *p; ++p) *p = (char)tolower(*p);
        int found = 0;
        for (int i = 0; i < bib->nb_livres; ++i) {
            char titre[256], auteur[256], categorie[256];
            strncpy(titre, bib->livres[i].titre, sizeof(titre));
            strncpy(auteur, bib->livres[i].auteur, sizeof(auteur));
            strncpy(categorie, bib->livres[i].categorie, sizeof(categorie));
            // Convertir en minuscules pour comparaison insensible à la casse
            for (char* p = titre; *p; ++p) *p = (char)tolower(*p);
            for (char* p = auteur; *p; ++p) *p = (char)tolower(*p);
            for (char* p = categorie; *p; ++p) *p = (char)tolower(*p);
            if (strstr(titre, tablecherche) || strstr(auteur, tablecherche) || strstr(categorie, tablecherche)) {
                if (!found) {
                    printf("Resultats trouves:\n");
                }
                afficher_un_livre(&bib->livres[i]);
                found = 1;
            }
        }
        if (!found) {
            printf("Aucun livre ne correspond a la recherche.\n");
        }
    }
}

void afficher_livres(Bibliotheque* bib) {
    printf("=== Liste des livres (%d livres) ===\n", bib->nb_livres);
    if (bib->nb_livres == 0) {
        printf("Aucun livre a afficher.\n");
        return;
    }
    for (int i = 0; i < bib->nb_livres; ++i) {
        Livre* lv = &bib->livres[i];
        // Compter les exemplaires totaux et disponibles pour ce livre
        int total_ex = 0;
        int dispo_ex = 0;
        for (int j = 0; j < bib->nb_exemplaires; ++j) {
            if (strcmp(bib->exemplaires[j].isbn, lv->isbn) == 0) {
                total_ex++;
                if (bib->exemplaires[j].disponible) dispo_ex++;
            }
        }
        printf("%d. ", i+1);
        afficher_un_livre(lv);
        printf("   Exemplaires: %d (disponibles: %d)\n", total_ex, dispo_ex);
    }
}

void trier_livres(Bibliotheque* bib) {
    if (bib->nb_livres < 2) {
        printf("Pas assez de livres pour trier.\n");
        return;
    }
    printf("=== Trier les livres ===\n");
    printf("1. Par titre\n");
    printf("2. Par auteur\n");
    printf("3. Par categorie\n");
    printf("4. Par annee\n");
    printf("5. Par nombre d'emprunts (popularite)\n");
    printf("Choix du critere: ");
    int choix;
    scanf("%d", &choix);
    vider_buffer();
    if (choix < 1 || choix > 5) {
        printf("Choix invalide.\n");
        return;
    }
    // Pour le critère "nombre d'emprunts", calculer le nombre d'emprunts par livre au préalable
    int emprunts_count[MAX_LIVRES];
    if (choix == 5) {
        for (int i = 0; i < bib->nb_livres; ++i) {
            emprunts_count[i] = 0;
        }
        for (int e = 0; e < bib->nb_emprunts; ++e) {
            Emprunt* emp = &bib->emprunts[e];
            for (int i = 0; i < bib->nb_livres; ++i) {
                if (strcmp(emp->isbn, bib->livres[i].isbn) == 0) {
                    emprunts_count[i]++;
                    break;
                }
            }
        }
    }
    // Tri à bulles en fonction du critère choisi
    for (int i = 0; i < bib->nb_livres - 1; ++i) {
        for (int j = 0; j < bib->nb_livres - 1 - i; ++j) {
            int cmp = 0;
            switch (choix) {
                case 1:
                    cmp = strcmp(bib->livres[j].titre, bib->livres[j+1].titre);
                    break;
                case 2:
                    cmp = strcmp(bib->livres[j].auteur, bib->livres[j+1].auteur);
                    break;
                case 3:
                    cmp = strcmp(bib->livres[j].categorie, bib->livres[j+1].categorie);
                    break;
                case 4:
                    cmp = bib->livres[j].annee - bib->livres[j+1].annee;
                    break;
                case 5:
                    cmp = emprunts_count[j+1] - emprunts_count[j];
                    break;
            }
            if (cmp > 0) {
                // Échanger les livres j et j+1
                Livre temp = bib->livres[j];
                bib->livres[j] = bib->livres[j+1];
                bib->livres[j+1] = temp;
                // Si tri par emprunts, échanger aussi les compteurs correspondants
                if (choix == 5) {
                    int tempCount = emprunts_count[j];
                    emprunts_count[j] = emprunts_count[j+1];
                    emprunts_count[j+1] = tempCount;
                }
            }
        }
    }
    printf("Livres tries avec succes.\n");
}
