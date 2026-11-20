#include "the_head_of_the_project.h"
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


void gererMenuPrincipal(void) {
    Zone Tab_Zone[MAX_ITEMS];
    int nb_zones = 0;

    Conteneur Tab_Cont[MAX_ITEMS];
    int nb_cont = 0;

    int choix = -1;

    while (choix != 0) {
        afficherMenuPrincipal();

        if (scanf("%d", &choix) != 1) {
            printf(COLOR_RED "Erreur : Veuillez entrer un nombre valide !\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1:
                menuGestionZonesConteneurs(Tab_Zone, &nb_zones, Tab_Cont, &nb_cont);
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
void menuGestionZonesConteneurs(Zone Tab_Zone[], int *nb_zones, Conteneur Tab_Cont[], int *nb_cont) {
    int choix = -1;

    while (choix != 0) {
        printf("\n" COLOR_CYAN "--- GESTION DES ZONES ET CONTENEURS ---" COLOR_RESET "\n");
        printf("1. Ajouter une zone\n");
        printf("2. Afficher la liste des zones\n");
        printf("3. Ajouter un conteneur\n");
        printf("4. Modifier les informations d'un conteneur\n");
        printf("5. Supprimer un conteneur\n");
        printf("6. Afficher tous les conteneurs (avec alertes)\n");
        printf("7. Afficher les conteneurs filtres par zone\n");
        printf("8. Signaler une panne / Reactiver un conteneur\n");
        printf("0. Retour au menu principal\n");
        printf("-----------------------------------------\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf(COLOR_RED "Saisie invalide.\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1:
                ajouterZone(Tab_Zone, nb_zones);
                break;
            case 2:
                afficherZones(Tab_Zone, *nb_zones);
                break;
            case 3:
                ajouterConteneur(Tab_Cont, nb_cont, Tab_Zone, *nb_zones);
                break;
            case 4:
                modifierConteneur(Tab_Cont, *nb_cont);
                break;
            case 5:
                supprimerConteneur(Tab_Cont, nb_cont);
                break;
            case 6:
                afficherConteneurs(Tab_Cont, *nb_cont);
                break;
            case 7:
                afficherConteneursParZone(Tab_Cont, *nb_cont, Tab_Zone, *nb_zones);
                break;
            case 8:
                changerEtatConteneur(Tab_Cont, *nb_cont);
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf(COLOR_RED "Option invalide ! (0 a 8)\n" COLOR_RESET);
        }
    }
}
void ajouterZoneTab(Zone TabZone[], Zone nouvelle_zone, int *n) {
    if (*n >= MAX_ITEMS) {
        printf(COLOR_RED "Tableau des Zones est plein\n" COLOR_RESET);
        return;
    }
    TabZone[*n] = nouvelle_zone;
    (*n)++;
    printf(COLOR_GREEN "Zone ajoutee avec succes !\n" COLOR_RESET);
}

void ajouterZone(Zone Tab_Zone[], int *n) {
    Zone nouvelle_zone;
    printf("Choisir l'id de la zone : ");
    scanf("%d", &nouvelle_zone.id_zone);
    printf("Choisir le nom de la zone : ");
    scanf(" %[^\n]", nouvelle_zone.nom_zone);
    printf("Choisir la description de la zone : ");
    scanf(" %[^\n]", nouvelle_zone.description);

    ajouterZoneTab(Tab_Zone, nouvelle_zone, n);
}

void afficherZones(Zone Tab_Zone[], int nbrZ) {
    if (nbrZ == 0) {
        printf(COLOR_RED "\nAucune zone enregistree pour le moment.\n" COLOR_RESET);
        return;
    }

    printf("\n" COLOR_CYAN "--- LISTE DES ZONES (%d) ---" COLOR_RESET "\n", nbrZ);
    for (int i = 0; i < nbrZ; i++) {
        printf("ID: %d | Nom: %s | Description: %s\n",
               Tab_Zone[i].id_zone,
               Tab_Zone[i].nom_zone,
               Tab_Zone[i].description);
    }
    printf("-----------------------------\n");
}

void ajouterConteneurTab(Conteneur Tab_Cont[], Conteneur nouveau_cont, int *nb_c) {
    if (*nb_c >= MAX_ITEMS) {
        printf(COLOR_RED "Erreur : Le tableau des conteneurs est plein !\n" COLOR_RESET);
        return;
    }
    Tab_Cont[*nb_c] = nouveau_cont;
    (*nb_c)++;
    printf(COLOR_GREEN "Conteneur ajoute avec succes !\n" COLOR_RESET);
}

void ajouterConteneur(Conteneur Tab_Cont[], int *nb_c, Zone Tab_Zone[], int nb_z) {
    if (nb_z == 0) {
        printf(COLOR_RED "\nImpossible : Vous devez d'abord ajouter au moins une zone !\n" COLOR_RESET);
        return;
    }

    Conteneur nouveau_cont;
    printf("\n--- AJOUT D'UN CONTENEUR ---\n");
    printf("ID du conteneur : ");
    scanf("%d", &nouveau_cont.id_cont);

    for (int i = 0; i < *nb_c; i++) {
        if (Tab_Cont[i].id_cont == nouveau_cont.id_cont) {
            printf(COLOR_RED "Erreur : Un conteneur avec cet ID existe deja !\n" COLOR_RESET);
            return;
        }
    }

    afficherZones(Tab_Zone, nb_z);
    printf("ID de la zone d'affectation : ");
    scanf("%d", &nouveau_cont.id_zone);

    bool zone_existe = false;
    for (int i = 0; i < nb_z; i++) {
        if (Tab_Zone[i].id_zone == nouveau_cont.id_zone) {
            zone_existe = true;
            break;
        }
    }

    if (!zone_existe) {
        printf(COLOR_RED "Erreur : Cette zone n'existe pas !\n" COLOR_RESET);
        return;
    }

    printf("Emplacement precis (ex: Avenue Habib Bourguiba) : ");
    scanf(" %[^\n]", nouveau_cont.emplacement);

    printf("Capacite maximale (en Litres) : ");
    scanf("%f", &nouveau_cont.max_occup_cont);

    printf("Seuil d'alerte de remplissage (en Litres) : ");
    scanf("%f", &nouveau_cont.val_notif_cont);

    printf("Niveau d'occupation actuel (en Litres) : ");
    scanf("%f", &nouveau_cont.val_occup_cont);

    nouveau_cont.etat = true;

    ajouterConteneurTab(Tab_Cont, nouveau_cont, nb_c);
}

// Case 4 : Modifier les informations d'un conteneur
void modifierConteneur(Conteneur Tab_Cont[], int nb_c) {
    if (nb_c == 0) {
        printf(COLOR_RED "\nAucun conteneur enregistre a modifier.\n" COLOR_RESET);
        return;
    }

    int id;
    printf("\nEntrez l'ID du conteneur a modifier : ");
    scanf("%d", &id);

    for (int i = 0; i < nb_c; i++) {
        if (Tab_Cont[i].id_cont == id) {
            printf("\n--- MODIFICATION DU CONTENEUR ID %d ---\n", id);

            printf("Nouvel emplacement (actuel : %s) : ", Tab_Cont[i].emplacement);
            scanf(" %[^\n]", Tab_Cont[i].emplacement);

            printf("Nouvelle capacite maximale en L (actuelle : %.1f) : ", Tab_Cont[i].max_occup_cont);
            scanf("%f", &Tab_Cont[i].max_occup_cont);

            printf("Nouveau seuil d'alerte en L (actuel : %.1f) : ", Tab_Cont[i].val_notif_cont);
            scanf("%f", &Tab_Cont[i].val_notif_cont);

            printf("Nouveau niveau d'occupation actuel en L (actuel : %.1f) : ", Tab_Cont[i].val_occup_cont);
            scanf("%f", &Tab_Cont[i].val_occup_cont);

            printf(COLOR_GREEN "Conteneur ID %d modifie avec succes !\n" COLOR_RESET, id);
            return;
        }
    }
    printf(COLOR_RED "Erreur : Aucun conteneur trouve avec l'ID %d.\n" COLOR_RESET, id);
}

void supprimerConteneur(Conteneur Tab_Cont[], int *nb_c) {
    if (*nb_c == 0) {
        printf(COLOR_RED "\nAucun conteneur enregistre a supprimer.\n" COLOR_RESET);
        return;
    }

    int id;
    printf("\nEntrez l'ID du conteneur a supprimer : ");
    scanf("%d", &id);

    for (int i = 0; i < *nb_c; i++) {
        if (Tab_Cont[i].id_cont == id) {
            for (int j = i; j < (*nb_c) - 1; j++) {
                Tab_Cont[j] = Tab_Cont[j + 1];
            }
            (*nb_c)--;
            printf(COLOR_GREEN "Conteneur ID %d supprime avec succes !\n" COLOR_RESET, id);
            return;
        }
    }
    printf(COLOR_RED "Erreur : Aucun conteneur trouve avec l'ID %d.\n" COLOR_RESET, id);
}

void afficherConteneurs(Conteneur Tab_Cont[], int nb_c) {
    if (nb_c == 0) {
        printf(COLOR_RED "\nAucun conteneur enregistre.\n" COLOR_RESET);
        return;
    }

    printf("\n==================== LISTE DES CONTENEURS (%d) ====================\n", nb_c);
    for (int i = 0; i < nb_c; i++) {
        float taux = (Tab_Cont[i].val_occup_cont / Tab_Cont[i].max_occup_cont) * 100.0;

        printf("ID: %d | Zone: %d | Lieu: %s | Remplissage: %.1f/%.1f L (%.0f%%) | Etat: %s",
               Tab_Cont[i].id_cont,
               Tab_Cont[i].id_zone,
               Tab_Cont[i].emplacement,
               Tab_Cont[i].val_occup_cont,
               Tab_Cont[i].max_occup_cont,
               taux,
               Tab_Cont[i].etat ? "Actif" : "En panne");

        if (Tab_Cont[i].val_occup_cont >= Tab_Cont[i].val_notif_cont) {
            printf(COLOR_RED "  [ALERTE : VIDAGE REQUIS !]\n" COLOR_RESET);
        } else {
            printf(COLOR_GREEN "  [OK]\n" COLOR_RESET);
        }
    }
    printf("===================================================================\n");
}

void afficherConteneursParZone(Conteneur Tab_Cont[], int nb_c, Zone Tab_Zone[], int nb_z) {
    if (nb_c == 0 || nb_z == 0) {
        printf(COLOR_RED "\nDonnees insuffisantes pour filtrer (verifiez vos zones et conteneurs).\n" COLOR_RESET);
        return;
    }

    afficherZones(Tab_Zone, nb_z);
    int id_z;
    printf("\nEntrez l'ID de la zone a filtrer : ");
    scanf("%d", &id_z);

    int trouve = 0;
    printf("\n--- CONTENEURS DE LA ZONE %d ---\n", id_z);
    for (int i = 0; i < nb_c; i++) {
        if (Tab_Cont[i].id_zone == id_z) {
            printf("ID: %d | Lieu: %s | Occupation: %.1f/%.1f L | Etat: %s",
                   Tab_Cont[i].id_cont,
                   Tab_Cont[i].emplacement,
                   Tab_Cont[i].val_occup_cont,
                   Tab_Cont[i].max_occup_cont,
                   Tab_Cont[i].etat ? "Actif" : "En panne");

            if (Tab_Cont[i].val_occup_cont >= Tab_Cont[i].val_notif_cont) {
                printf(COLOR_RED " [ALERTE SATURATION]\n" COLOR_RESET);
            } else {
                printf(COLOR_GREEN " [OK]\n" COLOR_RESET);
            }
            trouve++;
        }
    }

    if (trouve == 0) {
        printf("Aucun conteneur trouve dans cette zone.\n");
    }
}

void changerEtatConteneur(Conteneur Tab_Cont[], int nb_c) {
    if (nb_c == 0) {
        printf(COLOR_RED "\nAucun conteneur disponible.\n" COLOR_RESET);
        return;
    }

    int id;
    printf("\nEntrez l'ID du conteneur a basculer (Actif <-> En panne) : ");
    scanf("%d", &id);

    for (int i = 0; i < nb_c; i++) {
        if (Tab_Cont[i].id_cont == id) {
            Tab_Cont[i].etat = !Tab_Cont[i].etat;
            printf(COLOR_GREEN "Nouvel etat du conteneur %d : %s\n" COLOR_RESET,
                   id, Tab_Cont[i].etat ? "Actif" : "En panne");
            return;
        }
    }
    printf(COLOR_RED "Conteneur ID %d introuvable.\n" COLOR_RESET, id);
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
