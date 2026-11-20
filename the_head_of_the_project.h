#ifndef THE_HEAD_OF_THE_PROJECT_H
#define THE_HEAD_OF_THE_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Codes de couleurs ANSI pour les alertes dans la console
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_ROSE    "\033[1;38;5;213m"

#define MAX_ITEMS 50
#define MAX_CAMIONS 100
#define MAX_HISTO 100

// ==========================================
// 1. DÉFINITION DES STRUCTURES DU PROJET
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

typedef struct {
    char ch_date[100];
} ch_d;

typedef struct {
    int id_collect;
    int id_cont;
    int id_cam;
    ch_d date_hr_collecte;
    float volume_collecte;
} Historique;

// ==========================================
// 2. PROTOTYPES DES FONCTIONS
// ==========================================

// Menu Principal
void afficherMenuPrincipal(void);
void gererMenuPrincipal(void);
void menuStatistiquesAlertes(void);

// Choix 1 : Gestion des zones et conteneurs
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

// Choix 2 : Gestion des camions de collecte
void menuGestionCamions(Camion Tab_Cam[], int *nb_cam, Zone Tab_Zone[], int nb_zones);
int SaisirIdCamion(Camion Tab[], int n);
float SaisirCapacite(void);
float SaisirOccupation(float capacite);
int SaisirIdzone(Zone Tab_Zone[], int nb_zones);
int SaisirDisponibilite(void);
Camion saisirCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones);
int AjouterCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones);
void AffichierCamionettaux(Camion Tab[], int n);
void ModifierCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones);
int SupprimerCamion(Camion Tab[], int n);
int verifierIdCamion(Camion Tab[], int n, int id);
int rechercherCamion(Camion Tab[], int n, int id);
int verfierZone(int id, Zone Tab_Zone[], int nb_zones);

// Choix 3 : Operations de collecte et vidage
void menuOperations_De_Collecte_Et_Vidage(Conteneur les_conteneur[], int nombre_conteneur, Camion les_camion[], int nombre_camion, Historique tab_histo[], int *id_coll);
void OperationVidage(Conteneur les_conteneur[], int nombre_conteneur, Camion les_camion[], int nombre_camion, Historique tab_histo[], int *id_coll);
void les_conteneur_disponible(Conteneur les_conteneur[], int nombre_conteneur, int *k);
void fonction_entree_id_conteneur(Conteneur les_conteneur[], int nombre_conteneur, int *id_c, int *ind_c);
void les_camion_disponible(Camion les_camion[], int nombre_camion, float val_oc_con, int *dispo);
void fonction_entree_id_camion(Camion les_camion[], int nombre_camion, int *id_cm, float val_oc_con, int *ind_cam);
void confirmation_operation_vidage(Conteneur les_conteneur[], int id_c, int id_cm, int ind_c, char ch[]);
void enregitrement_historrique_collecte(Historique tab_histo[], int id_c, int id_cm, int *id_coll, float val_oc_con);
void operationdecharge(Camion les_camion[], int nombre_camion);
void les_camion_peut_etre_vider(Camion les_camion[], int nombre_camion, int *k);
void fonction_entree_id_camion_pour_decharge(Camion les_camion[], int nombre_camion, int *id_cm, int *ind_cam);
void confirmation_operation_decharge(Camion les_camion[], int id_cm, char ch[], int ind_cam);
void affichage_historique(Historique tab_histo[], int *id_coll);

#endif // THE_HEAD_OF_THE_PROJECT_H
