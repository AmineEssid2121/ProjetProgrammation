#ifndef THE_HEAD_OF_THE_PROJECT_H
#define THE_HEAD_OF_THE_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Codes de couleurs ANSI pour les alertes dans la console (Bonus)
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_CYAN    "\033[1;36m"

// ==========================================
// 1. DÉFINITION DES 3 STRUCTURES DU PROJET
// ==========================================

// Structure 1 : Zone de collecte
typedef struct {
    int id_zone;
    char nom_zone[50];
    char description[100];
} Zone;

// Structure 2 : Conteneur de déchets
typedef struct {
    int id_cont;
    char emplacement[100];
    float max_occup_cont;
    float val_notif_cont;
    float val_occup_cont;
    int id_zone;
    int etat; // 1 = Actif, 0 = En panne
} Conteneur;

// Structure 3 : Camion de collecte
typedef struct {
    int id_cam;
    char matricule[20];
    float max_occup_cam;
    float val_occup_cam;
    int id_zone;
    int etat_dispo; // 1 = Disponible, 0 = Indisponible
} Camion;

// ==========================================
// 2. PROTOTYPES DES FONCTIONS D'INTERFACE
// ==========================================

void afficherMenuPrincipal(void);
void gererMenuPrincipal(void);
void menuGestionZonesConteneurs(void);
void menuGestionCamions(void);
void menuOperationsCollecte(void);
void menuStatistiquesAlertes(void);

#endif // THE_HEAD_OF_THE_PROJECT_H
