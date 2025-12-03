
#ifndef BIBILOTHEQUE_NUMERIQUE_STRUCTURE_H
#define BIBILOTHEQUE_NUMERIQUE_STRUCTURE_H

#define MAX_LIVRES          10
#define MAX_UTILISATEURS    5
#define MAX_EMPRUNTS        200
#define MAX_EXEMPLAIRES     50   // nombre max d'exemplaires
#define MAX_TITRE       200
#define MAX_AUTEUR      100
#define MAX_ISBN        13       // 13 caractères pour l'ISBN (chaîne)
#define MAX_CATEGORIE   10
#define MAX_NOM         50
#define MAX_EMAIL       100
#define MAX_ID          10
#define MAX_DATE        11       // "JJ/MM/AAAA" + '\0'
#define MAX_EMPRUNTS_PAR_USER 3
#define DUREE_EMPRUNT        15  // en jours

// Structure représentant un livre (oeuvre) dans la bibliothèque
typedef struct {
    char isbn[MAX_ISBN];              // ISBN du livre
    char titre[MAX_TITRE];            // Titre du livre
    char auteur[MAX_AUTEUR];          // Auteur du livre
    char categorie[MAX_CATEGORIE];    // Catégorie du livre
    int  annee;                       // Année de parution
} Livre;

// Structure représentant un exemplaire physique d'un livre
typedef struct {
    int  num_exemplaire;             // Numéro de l'exemplaire (identifiant interne)
    char isbn[MAX_ISBN];             // ISBN du livre associé
    char date_achat[MAX_DATE];       // Date d'achat de l'exemplaire
    int  disponible;                 // 1 = disponible, 0 = emprunté
} Exemplaire;

// Structure représentant un utilisateur de la bibliothèque
typedef struct {
    char id_utilisateur[MAX_ID];      // Id de l'utilisateur (identifiant unique)
    char nom[MAX_NOM];                // Nom
    char prenom[MAX_NOM];             // Prénom
    char email[MAX_EMAIL];            // Email
    int  nb_emprunts_actifs;          // Nombre d'emprunts en cours (actifs)
} Utilisateur;

// Structure représentant un emprunt (prêt d'un exemplaire à un utilisateur)
typedef struct {
    int  num_exemplaire;              // Numéro de l'exemplaire emprunté
    char id_utilisateur[MAX_ID];      // Id de l'utilisateur qui emprunte
    char date_emprunt[MAX_DATE];      // Date d'emprunt
    char date_retour_prevue[MAX_DATE];// Date de retour prévue
    int  actif;                       // 1 = emprunt en cours, 0 = retourné
    int  id_emprunt;                  // Id unique de l'emprunt
    char isbn[MAX_ISBN];              // ISBN du livre emprunté
    char date_retour_effective[MAX_DATE]; // Date réelle de retour (ou "N/A" si pas encore retourné)
} Emprunt;

// Structure globale représentant la bibliothèque
typedef struct {
    // Liste des livres (œuvres)
    Livre livres[MAX_LIVRES];
    int   nb_livres;

    // Liste des exemplaires (copies physiques)
    Exemplaire exemplaires[MAX_EXEMPLAIRES];
    int        nb_exemplaires;

    // Liste des utilisateurs
    Utilisateur utilisateurs[MAX_UTILISATEURS];
    int         nb_utilisateurs;

    // Liste des emprunts
    Emprunt emprunts[MAX_EMPRUNTS];
    int     nb_emprunts;

    // Prochain ID à utiliser pour un nouvel emprunt (auto-incrément)
    int prochain_id_emprunt;
} Bibliotheque;

#endif //BIBILOTHEQUE_NUMERIQUE_STRUCTURE_H