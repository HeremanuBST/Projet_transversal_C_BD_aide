//
// Created by Heremanu on 07/11/2025.
//

// ============================================================================
// FICHIER: structures.h
// Description: Définition des structures de données
// ============================================================================

#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_LIVRES 10
#define MAX_UTILISATEURS 5
#define MAX_EMPRUNTS 200

#define MAX_TITRE 200
#define MAX_AUTEUR 100
#define MAX_ISBN 5
#define MAX_CATEGORIE 10
#define MAX_NOM 50
#define MAX_EMAIL 100
#define MAX_ID 10
#define MAX_DATE 11

#define MAX_EMPRUNTS_PAR_USER 3
#define DUREE_EMPRUNT 15

typedef struct {
    char isbn[MAX_ISBN];
    char titre[MAX_TITRE];
    char auteur[MAX_AUTEUR];
    int annee;
    char categorie[MAX_CATEGORIE];
} Livre;

typedef struct {
    int num_expemplaire;
    int stock_expemplaire;
    char date_achat[MAX_DATE];
    int disponible; // 1 = disponible, 0 = emprunté
} Exemplaire;

typedef struct {
    char id_utilisateur[MAX_ID];
    char nom[MAX_NOM];
    char prenom[MAX_NOM];
    char email[MAX_EMAIL];
    int nb_emprunts_actifs;
} Utilisateur;

typedef struct {
    int id_emprunt;
    char isbn[MAX_ISBN];
    char id_utilisateur[MAX_ID];
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