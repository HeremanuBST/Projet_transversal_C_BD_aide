
#include "emprunt.h"
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "livre.h"
#include "utilisateur.h"
#include "exemplaire.h"

void afficher_un_emprunt(const Emprunt* emp, Bibliotheque* bib) {
    if (emp == NULL) return;
    // Trouver le titre du livre et le nom de l'utilisateur pour affichage
    int livre_idx = trouver_livre_par_isbn(bib, emp->isbn);
    int utilisateur_idx = trouver_utilisateur(bib, emp->id_utilisateur);
    char titre[MAX_TITRE];
    char userNomPrenom[101];
    if (livre_idx != -1) {
        strncpy(titre, bib->livres[livre_idx].titre, MAX_TITRE);
    } else {
        strcpy(titre, "(Livre inconnu)");
    }
    if (utilisateur_idx != -1) {
        snprintf(userNomPrenom, sizeof(userNomPrenom), "%s %s",
                 bib->utilisateurs[utilisateur_idx].prenom, bib->utilisateurs[utilisateur_idx].nom);
    } else {
        strcpy(userNomPrenom, "(Utilisateur inconnu)");
    }
    if (emp->actif) {
        // Emprunt en cours (non retourné)
        printf("Emprunt %d: Livre \"%s\" (ISBN %s, Ex. %d) emprunte par %s le %s, retour prevu le %s.\n",
               emp->id_emprunt, titre, emp->isbn, emp->num_exemplaire, userNomPrenom,
               emp->date_emprunt, emp->date_retour_prevue);
    } else {
        // Emprunt déjà retourné
        printf("Emprunt %d: Livre \"%s\" (ISBN %s, Ex. %d) emprunte par %s le %s, retourne le %s.\n",
               emp->id_emprunt, titre, emp->isbn, emp->num_exemplaire, userNomPrenom,
               emp->date_emprunt, emp->date_retour_effective);
    }
}

void emprunter_exemplaire(Bibliotheque* bib) {
    if (bib->nb_livres == 0 || bib->nb_exemplaires == 0 || bib->nb_utilisateurs == 0) {
        printf("Assurez-vous qu'il y a au moins un livre, un exemplaire et un utilisateur enregistres avant d'emprunter.\n");
        return;
    }
    char userId[MAX_ID];
    char isbn[MAX_ISBN];
    printf("=== Emprunter un exemplaire ===\n");
    printf("ID de l'utilisateur: ");
    scanf("%9s", userId);
    vider_buffer();
    int user_idx = trouver_utilisateur(bib, userId);
    if (user_idx == -1) {
        printf("Utilisateur introuvable.\n");
        return;
    }
    Utilisateur* user = &bib->utilisateurs[user_idx];
    if (user->nb_emprunts_actifs >= MAX_EMPRUNTS_PAR_USER) {
        printf("Cet utilisateur a atteint la limite de %d emprunt(s) actif(s).\n", MAX_EMPRUNTS_PAR_USER);
        return;
    }
    printf("ISBN du livre a emprunter: ");
    scanf("%12s", isbn);
    vider_buffer();
    int livre_idx = trouver_livre_par_isbn(bib, isbn);
    if (livre_idx == -1) {
        printf("Livre introuvable.\n");
        return;
    }
    // Trouver un exemplaire disponible de ce livre
    int exemplar_index = -1;
    for (int i = 0; i < bib->nb_exemplaires; ++i) {
        if (strcmp(bib->exemplaires[i].isbn, isbn) == 0 && bib->exemplaires[i].disponible == 1) {
            exemplar_index = i;
            break;
        }
    }
    if (exemplar_index == -1) {
        printf("Aucun exemplaire disponible pour ce livre.\n");
        return;
    }
    Exemplaire* ex = &bib->exemplaires[exemplar_index];
    // Créer l'emprunt
    if (bib->nb_emprunts >= MAX_EMPRUNTS) {
        printf("Nombre maximum d'emprunts atteint, impossible d'enregistrer un nouvel emprunt.\n");
        return;
    }
    Emprunt emp;
    emp.id_emprunt = bib->prochain_id_emprunt;
    bib->prochain_id_emprunt++;
    emp.num_exemplaire = ex->num_exemplaire;
    strncpy(emp.id_utilisateur, userId, MAX_ID);
    obtenir_date_actuelle(emp.date_emprunt);
    ajouter_jours(emp.date_emprunt, DUREE_EMPRUNT, emp.date_retour_prevue);
    emp.actif = 1;
    strncpy(emp.isbn, isbn, MAX_ISBN);
    strcpy(emp.date_retour_effective, "N/A");
    // Ajouter l'emprunt à la liste
    bib->emprunts[bib->nb_emprunts] = emp;
    bib->nb_emprunts++;
    // Mettre à jour l'exemplaire et l'utilisateur
    ex->disponible = 0;
    user->nb_emprunts_actifs++;
    printf("Emprunt enregistre avec succes (ID emprunt %d). Date de retour prevue : %s\n",
           emp.id_emprunt, emp.date_retour_prevue);
}

void retourner_exemplaire(Bibliotheque* bib) {
    if (bib->nb_emprunts == 0) {
        printf("Aucun emprunt enregistre.\n");
        return;
    }
    printf("=== Retourner un exemplaire ===\n");
    printf("ID de l'emprunt a cloturer: ");
    int empId;
    if (scanf("%d", &empId) != 1) {
        printf("Entree invalide.\n");
        vider_buffer();
        return;
    }
    vider_buffer();
    // Chercher l'emprunt actif correspondant à cet ID
    int emp_index = -1;
    for (int i = 0; i < bib->nb_emprunts; ++i) {
        if (bib->emprunts[i].id_emprunt == empId && bib->emprunts[i].actif == 1) {
            emp_index = i;
            break;
        }
    }
    if (emp_index == -1) {
        printf("Emprunt introuvable ou deja retourne.\n");
        return;
    }
    Emprunt* emp = &bib->emprunts[emp_index];
    // Marquer l'emprunt comme retourne
    emp->actif = 0;
    obtenir_date_actuelle(emp->date_retour_effective);
    // Mettre à jour le compteur de l'utilisateur
    int user_idx = trouver_utilisateur(bib, emp->id_utilisateur);
    if (user_idx != -1) {
        if (bib->utilisateurs[user_idx].nb_emprunts_actifs > 0) {
            bib->utilisateurs[user_idx].nb_emprunts_actifs--;
        }
    }
    // Mettre à jour l'exemplaire (rendre disponible)
    int ex_idx = trouver_exemplaire_par_num(bib, emp->num_exemplaire);
    if (ex_idx != -1) {
        bib->exemplaires[ex_idx].disponible = 1;
    }
    printf("Retour de l'emprunt ID %d enregistre. Livre rendu disponible.\n", empId);
}

void afficher_emprunts_actifs(Bibliotheque* bib) {
    printf("=== Emprunts actifs ===\n");
    int count = 0;
    for (int i = 0; i < bib->nb_emprunts; ++i) {
        if (bib->emprunts[i].actif == 1) {
            afficher_un_emprunt(&bib->emprunts[i], bib);
            count++;
        }
    }
    if (count == 0) {
        printf("Aucun emprunt en cours.\n");
    }
}

void afficher_emprunts_en_cours(Bibliotheque* bib) {
    // Identique à afficher_emprunts_actifs (alias)
    afficher_emprunts_actifs(bib);
}

void verifier_retards(Bibliotheque* bib) {
    printf("=== Verification des retards ===\n");
    int count = 0;
    char today[MAX_DATE];
    obtenir_date_actuelle(today);
    for (int i = 0; i < bib->nb_emprunts; ++i) {
        if (bib->emprunts[i].actif == 1) {
            // Emprunt en cours
            if (comparer_dates(bib->emprunts[i].date_retour_prevue, today) < 0) {
                // La date de retour prévue est avant aujourd'hui => retard
                Emprunt* emp = &bib->emprunts[i];
                int user_idx = trouver_utilisateur(bib, emp->id_utilisateur);
                char userName[100];
                if (user_idx != -1) {
                    snprintf(userName, sizeof(userName), "%s %s",
                             bib->utilisateurs[user_idx].prenom, bib->utilisateurs[user_idx].nom);
                } else {
                    strcpy(userName, emp->id_utilisateur);
                }
                printf("Retard : Emprunt %d du livre %s (Exemplaire %d) par %s devait etre rendu le %s.\n",
                       emp->id_emprunt, emp->isbn, emp->num_exemplaire, userName, emp->date_retour_prevue);
                count++;
            }
        }
    }
    if (count == 0) {
        printf("Aucun emprunt en retard.\n");
    }
}

void afficher_statistiques(Bibliotheque* bib) {
    printf("=== Statistiques ===\n");
    if (bib->nb_emprunts == 0) {
        printf("Aucune statistique disponible (aucun emprunt enregistre).\n");
    } else {
        // Statistiques sur les livres
        int maxCount = 0;
        char topISBN[MAX_ISBN] = "";
        printf("- Nombre d'emprunts par livre :\n");
        for (int i = 0; i < bib->nb_livres; ++i) {
            int count = 0;
            for (int j = 0; j < bib->nb_emprunts; ++j) {
                if (strcmp(bib->emprunts[j].isbn, bib->livres[i].isbn) == 0) {
                    count++;
                }
            }
            printf("   %s (ISBN %s) : %d emprunt(s)\n", bib->livres[i].titre, bib->livres[i].isbn, count);
            if (count > maxCount) {
                maxCount = count;
                strncpy(topISBN, bib->livres[i].isbn, MAX_ISBN);
            }
        }
        if (strlen(topISBN) > 0) {
            int li = trouver_livre_par_isbn(bib, topISBN);
            if (li != -1) {
                printf("-> Livre le plus emprunte : %s (ISBN %s) avec %d emprunt(s).\n",
                       bib->livres[li].titre, topISBN, maxCount);
            } else {
                printf("-> Livre le plus emprunte : ISBN %s avec %d emprunt(s).\n", topISBN, maxCount);
            }
        }
        // Statistiques sur les utilisateurs
        int maxLoans = 0;
        char topUserId[MAX_ID] = "";
        printf("- Nombre total d'emprunts par utilisateur :\n");
        for (int u = 0; u < bib->nb_utilisateurs; ++u) {
            int total = 0;
            for (int j = 0; j < bib->nb_emprunts; ++j) {
                if (strcmp(bib->emprunts[j].id_utilisateur, bib->utilisateurs[u].id_utilisateur) == 0) {
                    total++;
                }
            }
            printf("   %s %s (ID %s) : %d emprunt(s) au total\n",
                   bib->utilisateurs[u].prenom, bib->utilisateurs[u].nom,
                   bib->utilisateurs[u].id_utilisateur, total);
            if (total > maxLoans) {
                maxLoans = total;
                strncpy(topUserId, bib->utilisateurs[u].id_utilisateur, MAX_ID);
            }
        }
        if (strlen(topUserId) > 0) {
            int ui = trouver_utilisateur(bib, topUserId);
            if (ui != -1) {
                printf("-> Utilisateur le plus actif : %s %s (ID %s) avec %d emprunt(s) au total.\n",
                       bib->utilisateurs[ui].prenom, bib->utilisateurs[ui].nom,
                       topUserId, maxLoans);
            } else {
                printf("-> Utilisateur le plus actif : ID %s avec %d emprunt(s) au total.\n",
                       topUserId, maxLoans);
            }
        }
    }
}

void historique_emprunts_utilisateur(Bibliotheque* bib) {
    if (bib->nb_emprunts == 0) {
        printf("Aucun emprunt n'a ete effectue dans la bibliotheque.\n");
        return;
    }
    char userId[MAX_ID];
    printf("=== Historique des emprunts par utilisateur ===\n");
    printf("ID de l'utilisateur : ");
    scanf("%9s", userId);
    vider_buffer();
    int found = 0;
    for (int i = 0; i < bib->nb_emprunts; ++i) {
        if (strcmp(bib->emprunts[i].id_utilisateur, userId) == 0) {
            if (!found) {
                // Afficher l'en-tête avec le nom de l'utilisateur si possible
                int ui = trouver_utilisateur(bib, userId);
                if (ui != -1) {
                    printf("Historique de %s %s (ID %s) :\n",
                           bib->utilisateurs[ui].prenom, bib->utilisateurs[ui].nom, userId);
                } else {
                    printf("Historique de l'utilisateur ID %s :\n", userId);
                }
            }
            afficher_un_emprunt(&bib->emprunts[i], bib);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucun emprunt trouve pour l'utilisateur %s.\n", userId);
    }
}
