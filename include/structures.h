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
    int disponible; // 1 = disponible, 0 = emprunté
} Livre;

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



/*typedef struct {
    char isbn[MAX_ISBN]; // ISBN du livre
    char titre[MAX_TITRE]; // Titre du livre
    char auteur[MAX_AUTEUR]; // Auteur du livre
    char categorie[MAX_CATEGORIE]; // Catégorie du livre
    int annee; // Année de parution
} Livre;

typedef struct {
    int num_expemplaire; // Numéro de l'exemplaie (équivaut à l'ISBN pour les livres)
    int ISBN[MAX_ISBN]; // ISBN du livre
    char date_achat[MAX_DATE]; // Date d'achat de l'exemplaire
    int stock_expemplaire; // Nombre d'exemplaire en stock
    int disponible; // 1 = exemplaire disponible, 0 = exemplaire emprunté
} Exemplaire;

typedef struct {
    char id_utilisateur[MAX_ID]; // Id de l'utilisateur
    char nom[MAX_NOM]; // Nom de l'utilisateur
    char prenom[MAX_NOM]; // Prénom de l'utilisateur
    char email[MAX_EMAIL]; // Email de l'utilisateur
    int nb_emprunts_actifs; // Nombre d'emprunt en cours fait par l'utilisateur
} Utilisateur;

typedef struct {
    int num_exemplaire; // Numéro de l'exemplaire du livre emprunté
    char id_utilisateur[MAX_ID]; // Id de l'utilisateur qui réalise l'emprunt
    char date_emprunt[MAX_DATE]; // Date d'emprunt
    char date_retour_prevue[MAX_DATE]; // Date de retour de l'exemplaire prévu
    int actif; // 1 = emprunt en cours, 0 = exemplaire retourné
    int id_emprunt; // Id d'emprunt
    char isbn[MAX_ISBN]; // ISBN du livre emprunté
    char date_retour_effective[MAX_DATE]; // Date de retour réel du livre par l'utilisateur
} Emprunt;

typedef struct {
    Livre livres[MAX_LIVRES]; // Tableau des livres
    int nb_livres; // Nombre actuel de livre
    Utilisateur utilisateurs[MAX_UTILISATEURS]; // Tableau des utilisateurs
    int nb_utilisateurs; // Nombre actuel d'utilisateur
    Emprunt emprunts[MAX_EMPRUNTS]; // Tableau des emprunts
    int nb_emprunts; // Nombre d'emprunt actuepl
    int prochain_id_emprunt; // Prochain Id d'emprunt pour évité de le rentrer manuellement
} Bibliotheque;

#endif */