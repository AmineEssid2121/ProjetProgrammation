#include "the_head_of_the_project.h"

// 1. Affichage visuel du menu principal
void afficherMenuPrincipal(void) {
    printf("\n" COLOR_CYAN "===== MENU PRINCIPAL GESTION DE LA COLLECTE DE DECHETS =====" COLOR_RESET "\n");
    printf("1. Gestion des zones et conteneurs\n");
    printf("2. Gestion des camions de collecte\n");
    printf("3. Operations de collecte et vidage\n");
    printf("4. Statistiques et alertes\n");
    printf("0. Quitter\n");
    printf("-----------------------------------------------------------------\n");
    printf("Votre choix : ");
}

// 2. Traitement de la boucle du menu principal
void gererMenuPrincipal(void) {
    int choix = -1;

    while (choix != 0) {
        afficherMenuPrincipal();

        // Sécurisation de la saisie utilisateur
        if (scanf("%d", &choix) != 1) {
            printf(COLOR_RED "Erreur : Veuillez entrer un nombre valide !\n" COLOR_RESET);
            while (getchar() != '\n'); // Vider le buffer de saisie en cas de mauvaise frappe
            continue;
        }

        switch (choix) {
            case 1:
                menuGestionZonesConteneurs();
                break;
            case 2:
                menuGestionCamions();
                break;
            case 3:
                menuOperationsCollecte();
                break;
            case 4:
                menuStatistiquesAlertes();
                break;
            case 0:
                printf(COLOR_GREEN "\nSauvegarde des donnees et fermeture de l'application. Au revoir !\n" COLOR_RESET);
                break;
            default:
                printf(COLOR_RED "\nChoix invalide ! Veuillez choisir une option entre 0 et 4.\n" COLOR_RESET);
        }
    }
}

// 3. Emplacements temporaires pour les sous-menus
void menuGestionZonesConteneurs(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Gestion des zones et conteneurs]\n" COLOR_RESET);
}

void menuGestionCamions(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Gestion des camions de collecte]\n" COLOR_RESET);
}

void menuOperationsCollecte(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Operations de collecte et vidage]\n" COLOR_RESET);
}

void menuStatistiquesAlertes(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Statistiques et alertes]\n" COLOR_RESET);
}
