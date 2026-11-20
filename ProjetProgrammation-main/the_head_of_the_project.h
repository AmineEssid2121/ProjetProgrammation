#ifndef THE_HEAD_OF_THE_PROJECT_H
#define THE_HEAD_OF_THE_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Codes de couleurs ANSI pour les alertes dans la console (Bonus)
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_ROSE    "\033[1;38;5;213m"

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
    bool etat; // 1 = Actif, 0 = En panne
} Conteneur;

// Structure 3 : Camion de collecte
typedef struct {
    int id_cam;
    char matricule[20];
    float max_occup_cam;
    float val_occup_cam;
    int id_zone;
    bool etat_dispo; // 1 = Disponible, 0 = Indisponible
} Camion;
typedef struct {
    int id_collect;
    int id_cont;
    int id_cam;
    char date_hr_collecte[100];
    float volume_collecte;
}Historique;

// ==========================================
// 2. PROTOTYPES DES FONCTIONS D'INTERFACE
// ==========================================

void afficherMenuPrincipal(void);
void gererMenuPrincipal(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion);
void menuGestionZonesConteneurs(void);
void menuGestionCamions(void);
void menuOperations_De_Collecte_Et_Vidage(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion);
void menuStatistiquesAlertes(void);
// fonction du choix 3
//fonction pour vidage
void OperationVidage(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion);
void les_conteneur_disponible(Conteneur les_conteneur[],int nombre_conteneur,int *k);
void fonction_entree_id_conteneur(Conteneur les_conteneur[],int nombre_conteneur,int *id_c,int *ind_c);
void les_camion_disponible(Camion les_camion[],int nombre_camion,float val_oc_con,int*dispo);
void fonction_entree_id_camion(Camion les_camion[],int nombre_camion,int *id_cm,int val_oc_con,int *ind_cam);
void confirmation_operation_vidage(Conteneur les_conteneur[],int id_c,int id_cm,int ind_c,char ch[]);
//fonction pour decharge
void operationdecharge(Camion les_camion[],int nombre_camion);
void les_camion_peut_etre_vider(Camion les_camion[],int nombre_camion,int *k);
void fonction_entree_id_camion_pour_decharge(Camion les_camion[],int nombre_camion,int*id_cm,int *ind_cam);
void confirmation_operation_decharge(Camion les_camion[],int id_cm,char ch[],int ind_cam);
#endif // THE_HEAD_OF_THE_PROJECT_H
