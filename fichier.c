
#include "fichier.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livre.h"
#include "exemplaire.h"

void charger_donnees(Bibliotheque* bib) {
    // Initialiser les compteurs à 0
    bib->nb_livres = 0;
    bib->nb_exemplaires = 0;
    bib->nb_utilisateurs = 0;
    bib->nb_emprunts = 0;
    bib->prochain_id_emprunt = 1;
    // Ouvrir chaque fichier en lecture
    FILE* fLivres = fopen("livres.txt", "r");
    if (fLivres) {
        char line[512];
        while (fgets(line, sizeof(line), fLivres)) {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) == 0) continue;
            Livre lv;
            char annee_str[20];
            char* token = strtok(line, ";");
            if (!token) continue;
            strncpy(lv.isbn, token, MAX_ISBN);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(lv.titre, token, MAX_TITRE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(lv.auteur, token, MAX_AUTEUR);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(lv.categorie, token, MAX_CATEGORIE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(annee_str, token, sizeof(annee_str));
            lv.annee = atoi(annee_str);
            bib->livres[bib->nb_livres++] = lv;
            if (bib->nb_livres >= MAX_LIVRES) break;
        }
        fclose(fLivres);
    }
    FILE* fEx = fopen("exemplaires.txt", "r");
    int max_ex_id = 0;
    if (fEx) {
        char line[256];
        while (fgets(line, sizeof(line), fEx)) {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) == 0) continue;
            Exemplaire ex;
            char num_str[20], dispo_str[5];
            char* token = strtok(line, ";");
            if (!token) continue;
            strncpy(num_str, token, sizeof(num_str));
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(ex.isbn, token, MAX_ISBN);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(ex.date_achat, token, MAX_DATE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(dispo_str, token, sizeof(dispo_str));
            ex.num_exemplaire = atoi(num_str);
            ex.disponible = atoi(dispo_str);
            bib->exemplaires[bib->nb_exemplaires++] = ex;
            if (ex.num_exemplaire > max_ex_id) {
                max_ex_id = ex.num_exemplaire;
            }
            if (bib->nb_exemplaires >= MAX_EXEMPLAIRES) break;
        }
        fclose(fEx);
    }
    // Initialiser le prochain numéro d'exemplaire
    if (max_ex_id < 1) {
        initialiser_prochain_num_exemplaire(1);
    } else {
        initialiser_prochain_num_exemplaire(max_ex_id + 1);
    }
    FILE* fUsers = fopen("utilisateurs.txt", "r");
    if (fUsers) {
        char line[512];
        while (fgets(line, sizeof(line), fUsers)) {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) == 0) continue;
            Utilisateur user;
            char nb_str[10];
            char* token = strtok(line, ";");
            if (!token) continue;
            strncpy(user.id_utilisateur, token, MAX_ID);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(user.nom, token, MAX_NOM);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(user.prenom, token, MAX_NOM);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(user.email, token, MAX_EMAIL);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(nb_str, token, sizeof(nb_str));
            user.nb_emprunts_actifs = atoi(nb_str);
            bib->utilisateurs[bib->nb_utilisateurs++] = user;
            if (bib->nb_utilisateurs >= MAX_UTILISATEURS) break;
        }
        fclose(fUsers);
    }
    FILE* fEmp = fopen("emprunts.txt", "r");
    int max_emp_id = 0;
    if (fEmp) {
        char line[512];
        while (fgets(line, sizeof(line), fEmp)) {
            line[strcspn(line, "\n")] = '\0';
            if (strlen(line) == 0) continue;
            Emprunt emp;
            char id_str[10], num_ex_str[10], actif_str[5];
            char* token = strtok(line, ";");
            if (!token) continue;
            strncpy(id_str, token, sizeof(id_str));
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(emp.id_utilisateur, token, MAX_ID);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(num_ex_str, token, sizeof(num_ex_str));
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(emp.isbn, token, MAX_ISBN);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(emp.date_emprunt, token, MAX_DATE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(emp.date_retour_prevue, token, MAX_DATE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(emp.date_retour_effective, token, MAX_DATE);
            token = strtok(NULL, ";");
            if (!token) continue;
            strncpy(actif_str, token, sizeof(actif_str));
            emp.id_emprunt = atoi(id_str);
            emp.num_exemplaire = atoi(num_ex_str);
            emp.actif = atoi(actif_str);
            bib->emprunts[bib->nb_emprunts++] = emp;
            if (emp.id_emprunt > max_emp_id) {
                max_emp_id = emp.id_emprunt;
            }
            if (bib->nb_emprunts >= MAX_EMPRUNTS) break;
        }
        fclose(fEmp);
    }
    // Initialiser le prochain ID d'emprunt
    if (max_emp_id < 1) {
        bib->prochain_id_emprunt = 1;
    } else {
        bib->prochain_id_emprunt = max_emp_id + 1;
    }
    printf("Donnees chargees : %d livre(s), %d exemplaire(s), %d utilisateur(s), %d emprunt(s).\n",
           bib->nb_livres, bib->nb_exemplaires, bib->nb_utilisateurs, bib->nb_emprunts);
}

void sauvegarder_donnees(Bibliotheque* bib) {
    FILE* fLivres = fopen("livres.txt", "w");
    if (fLivres) {
        for (int i = 0; i < bib->nb_livres; ++i) {
            Livre* lv = &bib->livres[i];
            fprintf(fLivres, "%s;%s;%s;%s;%d\n", lv->isbn, lv->titre, lv->auteur, lv->categorie, lv->annee);
        }
        fclose(fLivres);
    }
    FILE* fEx = fopen("exemplaires.txt", "w");
    if (fEx) {
        for (int i = 0; i < bib->nb_exemplaires; ++i) {
            Exemplaire* ex = &bib->exemplaires[i];
            fprintf(fEx, "%d;%s;%s;%d\n", ex->num_exemplaire, ex->isbn, ex->date_achat, ex->disponible);
        }
        fclose(fEx);
    }
    FILE* fUsers = fopen("utilisateurs.txt", "w");
    if (fUsers) {
        for (int i = 0; i < bib->nb_utilisateurs; ++i) {
            Utilisateur* u = &bib->utilisateurs[i];
            fprintf(fUsers, "%s;%s;%s;%s;%d\n", u->id_utilisateur, u->nom, u->prenom, u->email, u->nb_emprunts_actifs);
        }
        fclose(fUsers);
    }
    FILE* fEmp = fopen("emprunts.txt", "w");
    if (fEmp) {
        for (int i = 0; i < bib->nb_emprunts; ++i) {
            Emprunt* emp = &bib->emprunts[i];
            fprintf(fEmp, "%d;%s;%d;%s;%s;%s;%s;%d\n", emp->id_emprunt, emp->id_utilisateur,
                    emp->num_exemplaire, emp->isbn, emp->date_emprunt, emp->date_retour_prevue,
                    emp->date_retour_effective, emp->actif);
        }
        fclose(fEmp);
    }
    printf("Donnees sauvegardees dans les fichiers.\n");
}
