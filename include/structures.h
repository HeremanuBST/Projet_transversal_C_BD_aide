//
// Created by Heremanu on 07/11/2025.
//
// ============================================================================
// FICHIER: structures.h
// Description: Définition des structures de données
// ============================================================================

#ifndef STRUCTURES_H
#define STRUCTURES_H

// -------------------- TAILLES MAX --------------------
#define MAX_LIVRES          10
#define MAX_UTILISATEURS    5
#define MAX_EMPRUNTS        200
#define MAX_EXEMPLAIRES     50   // <-- nouveau : nombre max d'exemplaires

#define MAX_TITRE       200
#define MAX_AUTEUR      100
#define MAX_ISBN        13       // 13 caractères pour l'ISBN
#define MAX_CATEGORIE   10
#define MAX_NOM         50
#define MAX_EMAIL       100
#define MAX_ID          10
#define MAX_DATE        11       // "JJ/MM/AAAA" + '\0'

#define MAX_EMPRUNTS_PAR_USER 3
#define DUREE_EMPRUNT        15  // en jours

// -------------------- STRUCTURE LIVRE --------------------
// Représente l'œuvre en général (pas un exemplaire physique)
typedef struct {
    char isbn[MAX_ISBN];              // ISBN du livre
    char titre[MAX_TITRE];            // Titre du livre
    char auteur[MAX_AUTEUR];          // Auteur du livre
    char categorie[MAX_CATEGORIE];    // Catégorie du livre
    int  annee;                       // Année de parution
} Livre;

// -------------------- STRUCTURE EXEMPLAIRE --------------------
// Représente un exemplaire physique d'un livre
typedef struct {
    int  num_expemplaire;             // Numéro de l'exemplaire (identifiant interne)
    char ISBN[MAX_ISBN];              // ISBN du livre associé
    char date_achat[MAX_DATE];        // Date d'achat de l'exemplaire
    int  stock_expemplaire;           // Nombre d'exemplaires en stock pour cet ISBN
    int  disponible;                  // 1 = au moins un en stock, 0 = plus rien
} Exemplaire;

// -------------------- STRUCTURE UTILISATEUR --------------------
typedef struct {
    char id_utilisateur[MAX_ID];      // Id de l'utilisateur
    char nom[MAX_NOM];                // Nom
    char prenom[MAX_NOM];             // Prénom
    char email[MAX_EMAIL];            // Email
    int  nb_emprunts_actifs;          // Nombre d'emprunts en cours
} Utilisateur;

// -------------------- STRUCTURE EMPRUNT --------------------
typedef struct {
    int  num_exemplaire;              // Numéro de l'exemplaire emprunté (non encore utilisé dans notre code)
    char id_utilisateur[MAX_ID];      // Id de l'utilisateur qui emprunte
    char date_emprunt[MAX_DATE];      // Date d'emprunt
    char date_retour_prevue[MAX_DATE];// Date de retour prévue
    int  actif;                       // 1 = emprunt en cours, 0 = retourné
    int  id_emprunt;                  // Id unique de l'emprunt
    char isbn[MAX_ISBN];              // ISBN du livre emprunté
    char date_retour_effective[MAX_DATE]; // Date réelle de retour
} Emprunt;

// -------------------- STRUCTURE BIBLIOTHEQUE --------------------
typedef struct {
    // LIVRES (œuvres)
    Livre livres[MAX_LIVRES];
    int   nb_livres;

    // EXEMPLAIRES (physiques)
    Exemplaire exemplaires[MAX_EXEMPLAIRES];
    int        nb_exemplaires;

    // UTILISATEURS
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int         nb_utilisateurs;

    // EMPRUNTS
    Emprunt emprunts[MAX_EMPRUNTS];
    int     nb_emprunts;

    // Id auto-incrémenté pour les emprunts
    int prochain_id_emprunt;
} Bibliotheque;

#endif // STRUCTURES_H
