#ifndef THE_HEAD_OF_THE_PROJECT_H
#define THE_HEAD_OF_THE_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_CYAN    "\033[94m"
#define COLOR_RESET   "\033[0m"
#define MAX_ITEMS 50

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
    bool etat; // true (1) = Actif, false (0) = En panne
} Conteneur;

// Structure 3 : Camion de collecte
typedef struct {
    int id_cam;
    char matricule[20];
    float max_occup_cam;
    float val_occup_cam;
    int id_zone;
    bool etat_dispo; // true (1) = Disponible, false (0) = Indisponible
} Camion;

// ==========================================
// 2. PROTOTYPES DES FONCTIONS
// ==========================================

void afficherMenuPrincipal(void);
void gererMenuPrincipal(void);


void menuGestionCamions(void);
void menuOperationsCollecte(void);
void menuStatistiquesAlertes(void);

//choix 1:
void menuGestionZonesConteneurs(Zone Tab_Zone[], int *nb_zones, Conteneur Tab_Cont[], int *nb_cont);
void ajouterZoneTab(Zone TabZone[], Zone nouvelle_zone, int *n);

void ajouterZone(Zone Tab_Zone[], int *n);
void afficherZones(Zone Tab_Zone[], int nbrZ);

void ajouterConteneurTab(Conteneur Tab_Cont[], Conteneur nouveau_cont, int *nb_c);
void ajouterConteneur(Conteneur Tab_Cont[], int *nb_c, Zone Tab_Zone[], int nb_z);

void modifierConteneur(Conteneur Tab_Cont[], int nb_c);
void supprimerConteneur(Conteneur Tab_Cont[], int *nb_c);
void afficherConteneurs(Conteneur Tab_Cont[], int nb_c);
void afficherConteneursParZone(Conteneur Tab_Cont[], int nb_c, Zone Tab_Zone[], int nb_z);
void changerEtatConteneur(Conteneur Tab_Cont[], int nb_c);


#endif // THE_HEAD_OF_THE_PROJECT_H
