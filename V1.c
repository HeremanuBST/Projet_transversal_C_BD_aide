// ============================================================================
// FICHIER: structures.h
// Description: Définition des structures de données
// ============================================================================

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_LIVRES 100
#define MAX_UTILISATEURS 50
#define MAX_EMPRUNTS 200

#define MAX_TITRE 200
#define MAX_AUTEUR 100
#define MAX_ISBN 14
#define MAX_CATEGORIE 50
#define MAX_NOM 50
#define MAX_EMAIL 100
#define MAX_ID 20
#define MAX_DATE 11

#define MAX_EMPRUNTS_PAR_USER 3
#define DUREE_EMPRUNT 15

typedef struct {
    char isbn[MAX_ISBN];
    char titre[MAX_TITRE];
    char auteur[MAX_AUTEUR];
    int annee;
    char categorie[MAX_CATEGORIE];
    int disponible; // 1 = disponible, 0 = emprunté
} Livre;

typedef struct {
    char id_etudiant[MAX_ID];
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char email[MAX_EMAIL];
    int nb_emprunts_actifs;
} Utilisateur;

typedef struct {
    int id_emprunt;
    char isbn[MAX_ISBN];
    char id_etudiant[MAX_ID];
    char date_emprunt[MAX_DATE];
    char date_retour_prevue[MAX_DATE];
    char date_retour_effective[MAX_DATE];
    int actif; // 1 = en cours, 0 = retourné
} Emprunt;

typedef struct {
    Livre livres[MAX_LIVRES];
    int nb_livres;
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int nb_utilisateurs;
    Emprunt emprunts[MAX_EMPRUNTS];
    int nb_emprunts;
    int prochain_id_emprunt;
} Bibliotheque;

#endif

// ============================================================================
// FICHIER: utils.h
// Description: Fonctions utilitaires
// ============================================================================

#ifndef UTILS_H
#define UTILS_H

#include <time.h>

void vider_buffer();
void obtenir_date_actuelle(char* date);
void ajouter_jours(const char* date_depart, int jours, char* date_arrivee);
int comparer_dates(const char* date1, const char* date2);
int calculer_jours_difference(const char* date1, const char* date2);
void pause_ecran();

#endif

// ============================================================================
// FICHIER: utils.c
// Description: Implémentation des fonctions utilitaires
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void obtenir_date_actuelle(char* date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void ajouter_jours(const char* date_depart, int jours, char* date_arrivee) {
    struct tm tm = {0};
    int annee, mois, jour;

    sscanf(date_depart, "%d-%d-%d", &annee, &mois, &jour);

    tm.tm_year = annee - 1900;
    tm.tm_mon = mois - 1;
    tm.tm_mday = jour + jours;

    mktime(&tm);

    sprintf(date_arrivee, "%04d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int comparer_dates(const char* date1, const char* date2) {
    return strcmp(date1, date2);
}

int calculer_jours_difference(const char* date1, const char* date2) {
    struct tm tm1 = {0}, tm2 = {0};
    int a1, m1, j1, a2, m2, j2;

    sscanf(date1, "%d-%d-%d", &a1, &m1, &j1);
    sscanf(date2, "%d-%d-%d", &a2, &m2, &j2);

    tm1.tm_year = a1 - 1900;
    tm1.tm_mon = m1 - 1;
    tm1.tm_mday = j1;

    tm2.tm_year = a2 - 1900;
    tm2.tm_mon = m2 - 1;
    tm2.tm_mday = j2;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return (int)difftime(t2, t1) / (60 * 60 * 24);
}

void pause_ecran() {
    printf("\nAppuyez sur Entrée pour continuer...");
    vider_buffer();
    getchar();
}

// ============================================================================
// FICHIER: livres.h
// Description: Fonctions de gestion des livres
// ============================================================================

#ifndef LIVRES_H
#define LIVRES_H

#include "structures.h"

void ajouter_livre(Bibliotheque* bib);
void supprimer_livre(Bibliotheque* bib);
void modifier_livre(Bibliotheque* bib);
void rechercher_livre(Bibliotheque* bib);
void afficher_livres(Bibliotheque* bib);
void trier_livres(Bibliotheque* bib);
int trouver_livre_par_isbn(Bibliotheque* bib, const char* isbn);
void afficher_un_livre(Livre* livre);

#endif

// ============================================================================
// FICHIER: livres.c
// Description: Implémentation de la gestion des livres
// ============================================================================

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "livres.h"
#include "utils.h"

void afficher_un_livre(Livre* livre) {
    printf("ISBN: %s\n", livre->isbn);
    printf("Titre: %s\n", livre->titre);
    printf("Auteur: %s\n", livre->auteur);
    printf("Année: %d\n", livre->annee);
    printf("Catégorie: %s\n", livre->categorie);
    printf("Disponibilité: %s\n", livre->disponible ? "Disponible" : "Emprunté");
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
        printf("Erreur: Capacité maximale atteinte!\n");
        return;
    }

    Livre nouveau;

    printf("\n=== AJOUTER UN LIVRE ===\n");

    printf("ISBN (13 chiffres): ");
    scanf("%13s", nouveau.isbn);
    vider_buffer();

    if (trouver_livre_par_isbn(bib, nouveau.isbn) != -1) {
        printf("Erreur: Un livre avec cet ISBN existe déjà!\n");
        return;
    }

    printf("Titre: ");
    fgets(nouveau.titre, MAX_TITRE, stdin);
    nouveau.titre[strcspn(nouveau.titre, "\n")] = 0;

    printf("Auteur: ");
    fgets(nouveau.auteur, MAX_AUTEUR, stdin);
    nouveau.auteur[strcspn(nouveau.auteur, "\n")] = 0;

    printf("Année: ");
    scanf("%d", &nouveau.annee);
    vider_buffer();

    printf("Catégorie: ");
    fgets(nouveau.categorie, MAX_CATEGORIE, stdin);
    nouveau.categorie[strcspn(nouveau.categorie, "\n")] = 0;

    nouveau.disponible = 1;

    bib->livres[bib->nb_livres] = nouveau;
    bib->nb_livres++;

    printf("\n✓ Livre ajouté avec succès!\n");
}

void supprimer_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];

    printf("\n=== SUPPRIMER UN LIVRE ===\n");
    printf("ISBN du livre à supprimer: ");
    scanf("%13s", isbn);
    vider_buffer();

    int index = trouver_livre_par_isbn(bib, isbn);

    if (index == -1) {
        printf("Erreur: Livre non trouvé!\n");
        return;
    }

    if (!bib->livres[index].disponible) {
        printf("Erreur: Le livre est actuellement emprunté!\n");
        return;
    }

    for (int i = index; i < bib->nb_livres - 1; i++) {
        bib->livres[i] = bib->livres[i + 1];
    }

    bib->nb_livres--;
    printf("\n✓ Livre supprimé avec succès!\n");
}

void modifier_livre(Bibliotheque* bib) {
    char isbn[MAX_ISBN];

    printf("\n=== MODIFIER UN LIVRE ===\n");
    printf("ISBN du livre à modifier: ");
    scanf("%13s", isbn);
    vider_buffer();

    int index = trouver_livre_par_isbn(bib, isbn);

    if (index == -1) {
        printf("Erreur: Livre non trouvé!\n");
        return;
    }

    Livre* livre = &bib->livres[index];

    printf("\nLivre actuel:\n");
    afficher_un_livre(livre);

    printf("\nQue souhaitez-vous modifier?\n");
    printf("1. Titre\n");
    printf("2. Auteur\n");
    printf("3. Année\n");
    printf("4. Catégorie\n");
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
            printf("Nouvelle année: ");
            scanf("%d", &livre->annee);
            vider_buffer();
            break;
        case 4:
            printf("Nouvelle catégorie: ");
            fgets(livre->categorie, MAX_CATEGORIE, stdin);
            livre->categorie[strcspn(livre->categorie, "\n")] = 0;
            break;
        case 0:
            return;
        default:
            printf("Choix invalide!\n");
            return;
    }

    printf("\n✓ Livre modifié avec succès!\n");
}

void rechercher_livre(Bibliotheque* bib) {
    printf("\n=== RECHERCHER UN LIVRE ===\n");
    printf("1. Par ISBN\n");
    printf("2. Par titre\n");
    printf("3. Par auteur\n");
    printf("4. Par catégorie\n");
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
                    printf("\nRésultat:\n");
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        case 2:
            printf("Titre (ou partie): ");
            fgets(critere, MAX_TITRE, stdin);
            critere[strcspn(critere, "\n")] = 0;

            printf("\nRésultats:\n");
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

            printf("\nRésultats:\n");
            for (int i = 0; i < bib->nb_livres; i++) {
                if (strstr(bib->livres[i].auteur, critere) != NULL) {
                    afficher_un_livre(&bib->livres[i]);
                    trouve = 1;
                }
            }
            break;

        case 4:
            printf("Catégorie: ");
            fgets(critere, MAX_CATEGORIE, stdin);
            critere[strcspn(critere, "\n")] = 0;

            printf("\nRésultats:\n");
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
        printf("Aucun livre trouvé.\n");
    }
}

void afficher_livres(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("\nAucun livre dans la bibliothèque.\n");
        return;
    }

    printf("\n=== LISTE DES LIVRES (%d) ===\n\n", bib->nb_livres);

    for (int i = 0; i < bib->nb_livres; i++) {
        printf("%d. ", i + 1);
        afficher_un_livre(&bib->livres[i]);
    }
}

void trier_livres(Bibliotheque* bib) {
    if (bib->nb_livres == 0) {
        printf("\nAucun livre à trier.\n");
        return;
    }

    printf("\n=== TRIER LES LIVRES ===\n");
    printf("1. Par titre\n");
    printf("2. Par auteur\n");
    printf("3. Par année\n");
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

    printf("\n✓ Livres triés avec succès!\n");
    afficher_livres(bib);
}

// ============================================================================
// FICHIER: utilisateurs.h
// Description: Fonctions de gestion des utilisateurs
// ============================================================================

#ifndef UTILISATEURS_H
#define UTILISATEURS_H

#include "structures.h"

void ajouter_utilisateur(Bibliotheque* bib);
void supprimer_utilisateur(Bibliotheque* bib);
void modifier_utilisateur(Bibliotheque* bib);
void afficher_utilisateurs(Bibliotheque* bib);
int trouver_utilisateur(Bibliotheque* bib, const char* id_etudiant);
void afficher_un_utilisateur(Utilisateur* user);

#endif

// ============================================================================
// FICHIER: utilisateurs.c
// Description: Implémentation de la gestion des utilisateurs
// ============================================================================

#include <stdio.h>
#include <string.h>
#include "utilisateurs.h"
#include "utils.h"

void afficher_un_utilisateur(Utilisateur* user) {
    printf("ID: %s\n", user->id_etudiant);
    printf("Nom: %s %s\n", user->prenom, user->nom);
    printf("Email: %s\n", user->email);
    printf("Emprunts actifs: %d/%d\n", user->nb_emprunts_actifs, MAX_EMPRUNTS_PAR_USER);
    printf("----------------------------------------\n");
}

int trouver_utilisateur(Bibliotheque* bib, const char* id_etudiant) {
    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        if (strcmp(bib->utilisateurs[i].id_etudiant, id_etudiant) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_utilisateur(Bibliotheque* bib) {
    if (bib->nb_utilisateurs >= MAX_UTILISATEURS) {
        printf("Erreur: Capacité maximale atteinte!\n");
        return;
    }

    Utilisateur nouveau;

    printf("\n=== AJOUTER UN UTILISATEUR ===\n");

    printf("ID étudiant: ");
    scanf("%19s", nouveau.id_etudiant);
    vider_buffer();

    if (trouver_utilisateur(bib, nouveau.id_etudiant) != -1) {
        printf("Erreur: Cet ID étudiant existe déjà!\n");
        return;
    }

    printf("Nom: ");
    fgets(nouveau.nom, MAX_NOM, stdin);
    nouveau.nom[strcspn(nouveau.nom, "\n")] = 0;

    printf("Prénom: ");
    fgets(nouveau.prenom, MAX_NOM, stdin);
    nouveau.prenom[strcspn(nouveau.prenom, "\n")] = 0;

    printf("Email: ");
    fgets(nouveau.email, MAX_EMAIL, stdin);
    nouveau.email[strcspn(nouveau.email, "\n")] = 0;

    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        if (strcmp(bib->utilisateurs[i].email, nouveau.email) == 0) {
            printf("Erreur: Cet email est déjà utilisé!\n");
            return;
        }
    }

    nouveau.nb_emprunts_actifs = 0;

    bib->utilisateurs[bib->nb_utilisateurs] = nouveau;
    bib->nb_utilisateurs++;

    printf("\n✓ Utilisateur ajouté avec succès!\n");
}

void supprimer_utilisateur(Bibliotheque* bib) {
    char id[MAX_ID];

    printf("\n=== SUPPRIMER UN UTILISATEUR ===\n");
    printf("ID étudiant: ");
    scanf("%19s", id);
    vider_buffer();

    int index = trouver_utilisateur(bib, id);

    if (index == -1) {
        printf("Erreur: Utilisateur non trouvé!\n");
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
    printf("\n✓ Utilisateur supprimé avec succès!\n");
}

void modifier_utilisateur(Bibliotheque* bib) {
    char id[MAX_ID];

    printf("\n=== MODIFIER UN UTILISATEUR ===\n");
    printf("ID étudiant: ");
    scanf("%19s", id);
    vider_buffer();

    int index = trouver_utilisateur(bib, id);

    if (index == -1) {
        printf("Erreur: Utilisateur non trouvé!\n");
        return;
    }

    Utilisateur* user = &bib->utilisateurs[index];

    printf("\nUtilisateur actuel:\n");
    afficher_un_utilisateur(user);

    printf("\nQue souhaitez-vous modifier?\n");
    printf("1. Nom\n");
    printf("2. Prénom\n");
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
            printf("Nouveau prénom: ");
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

    printf("\n✓ Utilisateur modifié avec succès!\n");
}

void afficher_utilisateurs(Bibliotheque* bib) {
    if (bib->nb_utilisateurs == 0) {
        printf("\nAucun utilisateur enregistré.\n");
        return;
    }

    printf("\n=== LISTE DES UTILISATEURS (%d) ===\n\n", bib->nb_utilisateurs);

    for (int i = 0; i < bib->nb_utilisateurs; i++) {
        printf("%d. ", i + 1);
        afficher_un_utilisateur(&bib->utilisateurs[i]);
    }
}

// ============================================================================
// FICHIER: emprunts.h
// Description: Fonctions de gestion des emprunts
// ============================================================================

#ifndef EMPRUNTS_H
#define EMPRUNTS_H

#include "structures.h"

void emprunter_livre(Bibliotheque* bib);
void retourner_livre(Bibliotheque* bib);
void afficher_emprunts_actifs(Bibliotheque* bib);
void verifier_retards(Bibliotheque* bib);
void afficher_un_emprunt(Emprunt* emp, Bibliotheque* bib);

#endif

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
    printf("Date retour prévue: %s\n", emp->date_retour_prevue);

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
        printf("Erreur: Livre non trouvé!\n");
        return;
    }

    if (!bib->livres[idx_livre].disponible) {
        printf("Erreur: Le livre est déjà emprunté!\n");
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
        printf("Erreur: Capacité maximale d'emprunts atteinte!\n");
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

    printf("\n✓ Emprunt enregistré avec succès!\n");
    printf("Date de retour prévue: %s\n", nouveau.date_retour_prevue);
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
            strcmp(bib->emprunts[i].id_etudiant, id_etudiant) == 0)
    }