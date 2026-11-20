#include "the_head_of_the_project.h"
#include <string.h>
#include <time.h>

// ==========================================
// MENU PRINCIPAL
// ==========================================

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

    Camion Tab_Cam[MAX_CAMIONS];
    int nb_cam = 0;

    Historique tab_histo[MAX_HISTO];
    int id_coll = 0;

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
                menuGestionCamions(Tab_Cam, &nb_cam, Tab_Zone, nb_zones);
                break;
            case 3:
                menuOperations_De_Collecte_Et_Vidage(Tab_Cont, nb_cont, Tab_Cam, nb_cam, tab_histo, &id_coll);
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

// ==========================================
// CHOIX 1 : GESTION DES ZONES ET CONTENEURS
// ==========================================

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

    do {
        printf("Capacite maximale (en Litres) : ");
        scanf("%f", &nouveau_cont.max_occup_cont);
        if (nouveau_cont.max_occup_cont <= 0) {
            printf(COLOR_RED "Erreur : La capacite maximale doit etre superieure a 0 !\n" COLOR_RESET);
        }
    } while (nouveau_cont.max_occup_cont <= 0);

    do {
        printf("Seuil d'alerte de remplissage (en Litres) : ");
        scanf("%f", &nouveau_cont.val_notif_cont);
        if (nouveau_cont.val_notif_cont < 0 || nouveau_cont.val_notif_cont > nouveau_cont.max_occup_cont) {
            printf(COLOR_RED "Erreur : Le seuil doit etre compris entre 0 et %.1f L !\n" COLOR_RESET, nouveau_cont.max_occup_cont);
        }
    } while (nouveau_cont.val_notif_cont < 0 || nouveau_cont.val_notif_cont > nouveau_cont.max_occup_cont);

    do {
        printf("Niveau d'occupation actuel (en Litres) : ");
        scanf("%f", &nouveau_cont.val_occup_cont);
        if (nouveau_cont.val_occup_cont < 0 || nouveau_cont.val_occup_cont > nouveau_cont.max_occup_cont) {
            printf(COLOR_RED "Erreur : L'occupation doit etre comprise entre 0 et %.1f L !\n" COLOR_RESET, nouveau_cont.max_occup_cont);
        }
    } while (nouveau_cont.val_occup_cont < 0 || nouveau_cont.val_occup_cont > nouveau_cont.max_occup_cont);

    nouveau_cont.etat = true;

    ajouterConteneurTab(Tab_Cont, nouveau_cont, nb_c);
}

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

            do {
                printf("Nouvelle capacite maximale en L (actuelle : %.1f) : ", Tab_Cont[i].max_occup_cont);
                scanf("%f", &Tab_Cont[i].max_occup_cont);
                if (Tab_Cont[i].max_occup_cont <= 0) {
                    printf(COLOR_RED "Erreur : La capacite maximale doit etre superieure a 0 !\n" COLOR_RESET);
                }
            } while (Tab_Cont[i].max_occup_cont <= 0);

            do {
                printf("Nouveau seuil d'alerte en L (actuel : %.1f) : ", Tab_Cont[i].val_notif_cont);
                scanf("%f", &Tab_Cont[i].val_notif_cont);
                if (Tab_Cont[i].val_notif_cont < 0 || Tab_Cont[i].val_notif_cont > Tab_Cont[i].max_occup_cont) {
                    printf(COLOR_RED "Erreur : Le seuil doit etre compris entre 0 et %.1f L !\n" COLOR_RESET, Tab_Cont[i].max_occup_cont);
                }
            } while (Tab_Cont[i].val_notif_cont < 0 || Tab_Cont[i].val_notif_cont > Tab_Cont[i].max_occup_cont);

            do {
                printf("Nouveau niveau d'occupation actuel en L (actuel : %.1f) : ", Tab_Cont[i].val_occup_cont);
                scanf("%f", &Tab_Cont[i].val_occup_cont);
                if (Tab_Cont[i].val_occup_cont < 0 || Tab_Cont[i].val_occup_cont > Tab_Cont[i].max_occup_cont) {
                    printf(COLOR_RED "Erreur : L'occupation doit etre comprise entre 0 et %.1f L !\n" COLOR_RESET, Tab_Cont[i].max_occup_cont);
                }
            } while (Tab_Cont[i].val_occup_cont < 0 || Tab_Cont[i].val_occup_cont > Tab_Cont[i].max_occup_cont);

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

// ==========================================
// CHOIX 2 : GESTION DES CAMIONS DE COLLECTE
// ==========================================

void menuGestionCamions(Camion Tab_Cam[], int *nb_cam, Zone Tab_Zone[], int nb_zones) {
    int choix;

    do {
        printf(COLOR_CYAN);
        printf("\n=============================================\n");
        printf("             GESTION DES CAMIONS\n");
        printf("=============================================\n");
        printf(COLOR_RESET);

        printf(COLOR_YELLOW);
        printf("\n");
        printf("       1. Ajouter un camion\n");
        printf("       2. Modifier un camion\n");
        printf("       3. Supprimer un camion\n");
        printf("       4. Afficher les camions et taux\n");
        printf("       0. Retour au menu principal\n");
        printf(COLOR_RESET);

        printf(COLOR_CYAN);
        printf("\n=============================================\n");
        printf(COLOR_RESET);
        printf(COLOR_GREEN);
        printf("Votre choix : ");
        printf(COLOR_RESET);

        if (scanf("%d", &choix) != 1) {
            printf(COLOR_RED "Saisie invalide.\n" COLOR_RESET);
            while (getchar() != '\n');
            choix = -1;
            continue;
        }

        switch (choix) {
            case 1:
                *nb_cam = AjouterCamion(Tab_Cam, *nb_cam, Tab_Zone, nb_zones);
                break;
            case 2:
                ModifierCamion(Tab_Cam, *nb_cam, Tab_Zone, nb_zones);
                break;
            case 3:
                *nb_cam = SupprimerCamion(Tab_Cam, *nb_cam);
                break;
            case 4:
                AffichierCamionettaux(Tab_Cam, *nb_cam);
                break;
            case 0:
                printf(COLOR_GREEN "\nRetour au menu principal...\n" COLOR_RESET);
                break;
            default:
                printf(COLOR_RED "\nChoix invalide !\n" COLOR_RESET);
        }
    } while (choix != 0);
}

Camion saisirCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones) {
    printf(COLOR_CYAN "\n===== SAISIE D'UN CAMION =====\n" COLOR_RESET);

    Camion c;
    c.id_cam = SaisirIdCamion(Tab, n);

    printf(COLOR_CYAN "Donner la matricule du camion : " COLOR_RESET);
    scanf("%19s", c.matricule);

    c.max_occup_cam = SaisirCapacite();
    c.val_occup_cam = SaisirOccupation(c.max_occup_cam);
    c.id_zone = SaisirIdzone(Tab_Zone, nb_zones);
    c.etat_dispo = SaisirDisponibilite();

    return c;
}

int SaisirIdCamion(Camion Tab[], int n) {
    int id;
    do {
        printf(COLOR_YELLOW "\nDonner l'identifiant du camion : " COLOR_RESET);
        scanf("%d", &id);
        if (id <= 0) {
            printf(COLOR_RED "\nErreur : l'identifiant doit etre positif !\n");
            printf("Veuillez entrer un identifiant different.\n" COLOR_RESET);
        } else if (verifierIdCamion(Tab, n, id) == 0) {
            printf(COLOR_RED "\nCet identifiant existe deja !\n");
            printf("Veuillez entrer un identifiant different.\n" COLOR_RESET);
        }
    } while (id <= 0 || verifierIdCamion(Tab, n, id) == 0);

    return id;
}

float SaisirCapacite(void) {
    float capacite;
    do {
        printf(COLOR_CYAN "Donner le volume maximal du camion : " COLOR_RESET);
        scanf("%f", &capacite);
        if (capacite <= 0) {
            printf(COLOR_RED "Erreur : la capacite doit etre positive !\n");
            printf("Veuillez saisir une autre valeur.\n" COLOR_RESET);
        }
    } while (capacite <= 0);

    return capacite;
}

float SaisirOccupation(float capacite) {
    float occupation;
    do {
        printf(COLOR_CYAN "Donner l'occupation actuelle : " COLOR_RESET);
        scanf("%f", &occupation);
        if (occupation < 0 || occupation > capacite) {
            printf(COLOR_RED);
            printf("Erreur : occupation invalide !\n");
            printf("Elle doit etre comprise entre 0 et %.2f.\n", capacite);
            printf("Veuillez saisir une autre valeur.\n");
            printf(COLOR_RESET);
        }
    } while (occupation < 0 || occupation > capacite);

    return occupation;
}

int SaisirIdzone(Zone Tab_Zone[], int nb_zones) {
    int id_zone;
    afficherZones(Tab_Zone, nb_zones);
    do {
        printf(COLOR_CYAN "Donner l'identifiant de la zone : " COLOR_RESET);
        scanf("%d", &id_zone);
        if (id_zone <= 0) {
            printf(COLOR_RED "Erreur : identifiant de zone invalide !\n");
            printf("Veuillez saisir un autre identifiant.\n" COLOR_RESET);
        } else if (verfierZone(id_zone, Tab_Zone, nb_zones) == 0) {
            printf(COLOR_RED "Erreur : cette zone n'existe pas !\n");
            printf("Veuillez saisir un identifiant existant.\n" COLOR_RESET);
        }
    } while (id_zone <= 0 || verfierZone(id_zone, Tab_Zone, nb_zones) == 0);

    return id_zone;
}

int SaisirDisponibilite(void) {
    int etat;
    do {
        printf(COLOR_CYAN "\nEtat (1 = Disponible, 0 = Non disponible) : " COLOR_RESET);
        scanf("%d", &etat);
        if (etat != 0 && etat != 1) {
            printf(COLOR_RED "Erreur : choisir uniquement 0 ou 1 !\n" COLOR_RESET);
        }
    } while (etat != 0 && etat != 1);

    return etat;
}

int AjouterCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones) {
    if (nb_zones == 0) {
        printf(COLOR_RED "\nImpossible : Vous devez d'abord ajouter au moins une zone (Choix 1) !\n" COLOR_RESET);
        return n;
    }
    if (n >= MAX_CAMIONS) {
        printf(COLOR_RED "\nLe tableau des camions est plein !\n" COLOR_RESET);
        return n;
    }
    Tab[n] = saisirCamion(Tab, n, Tab_Zone, nb_zones);
    n++;
    printf(COLOR_GREEN "\nCamion ajoute avec succes !\n" COLOR_RESET);
    return n;
}

void AffichierCamionettaux(Camion Tab[], int n) {
    float taux;
    if (n == 0) {
        printf(COLOR_RED "\nAucun camion enregistre !\n" COLOR_RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (Tab[i].max_occup_cam > 0) {
            taux = (Tab[i].val_occup_cam / Tab[i].max_occup_cam) * 100.0;
        } else {
            taux = 0;
            printf("Taux de remplissage : Impossible a calculer\n");
        }

        printf(COLOR_CYAN);
        printf("\n======================================================\n");
        printf("    INFORMATIONS DU CAMION\n");
        printf("======================================================\n");
        printf(COLOR_RESET);

        printf(COLOR_YELLOW "\n---------- Camion %d ----------\n" COLOR_RESET, i + 1);
        printf(COLOR_YELLOW "Identifiant camion   : %d\n" COLOR_RESET, Tab[i].id_cam);
        printf(COLOR_YELLOW "Matricule            : %s\n" COLOR_RESET, Tab[i].matricule);
        printf(COLOR_YELLOW "Capacite maximale    : %.2f\n" COLOR_RESET, Tab[i].max_occup_cam);
        printf(COLOR_YELLOW "Occupation actuelle  : %.2f\n" COLOR_RESET, Tab[i].val_occup_cam);
        printf(COLOR_YELLOW "Identifiant zone     : %d\n" COLOR_RESET, Tab[i].id_zone);

        if (Tab[i].etat_dispo) {
            printf(COLOR_GREEN "Etat                 : Disponible\n" COLOR_RESET);
        } else {
            printf(COLOR_RED "Etat                 : Non disponible\n" COLOR_RESET);
        }

        printf(COLOR_MAGENTA "Taux de remplissage  : %.2f%%\n" COLOR_RESET, taux);
        printf(COLOR_CYAN "-----------------------------------------------------------\n" COLOR_RESET);
    }
}

void ModifierCamion(Camion Tab[], int n, Zone Tab_Zone[], int nb_zones) {
    int id, i, choix;
    if (n == 0) {
        printf(COLOR_RED "\nAucun camion enregistre !\n" COLOR_RESET);
        return;
    }

    printf(COLOR_CYAN "\nDonner l'identifiant du camion a modifier : " COLOR_RESET);
    scanf("%d", &id);
    i = rechercherCamion(Tab, n, id);

    if (i == -1) {
        printf(COLOR_RED "\nCamion introuvable !\n" COLOR_RESET);
        return;
    }

    printf(COLOR_YELLOW);
    printf("\n============================\n");
    printf("   MODIFICATION CAMION\n");
    printf("============================\n");
    printf(COLOR_RESET);

    printf(COLOR_CYAN);
    printf("\n1. Modifier la capacite maximale\n");
    printf("2. Modifier les autres informations\n");
    printf("Votre choix : ");
    printf(COLOR_RESET);
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            Tab[i].max_occup_cam = SaisirCapacite();
            printf(COLOR_GREEN "\nCapacite modifiee avec succes !\n" COLOR_RESET);
            break;
        case 2:
            printf(COLOR_CYAN "\nNouveau matricule : " COLOR_RESET);
            scanf("%19s", Tab[i].matricule);
            Tab[i].val_occup_cam = SaisirOccupation(Tab[i].max_occup_cam);
            Tab[i].id_zone = SaisirIdzone(Tab_Zone, nb_zones);
            Tab[i].etat_dispo = SaisirDisponibilite();
            printf(COLOR_GREEN "\nInformations modifiees avec succes !\n" COLOR_RESET);
            break;
        case 0:
            printf("\nRetour au menu de gestion des camions...\n");
            break;
        default:
            printf(COLOR_RED "\nChoix invalide ! Veuillez choisir 1 ou 2\n" COLOR_RESET);
    }
}

int SupprimerCamion(Camion Tab[], int n) {
    int id;
    if (n == 0) {
        printf(COLOR_RED "\nAucun camion enregistre !\n" COLOR_RESET);
        return n;
    }

    printf(COLOR_CYAN "\nDonner l'identifiant du camion a supprimer : " COLOR_RESET);
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (Tab[i].id_cam == id) {
            for (int j = i; j < n - 1; j++) {
                Tab[j] = Tab[j + 1];
            }
            n--;
            printf(COLOR_GREEN "\nCamion supprime avec succes !\n" COLOR_RESET);
            return n;
        }
    }

    printf(COLOR_RED "\nCamion introuvable !\n" COLOR_RESET);
    return n;
}

int verifierIdCamion(Camion Tab[], int n, int id) {
    return (rechercherCamion(Tab, n, id) == -1);
}

int rechercherCamion(Camion Tab[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (Tab[i].id_cam == id) {
            return i;
        }
    }
    return -1;
}

int verfierZone(int id, Zone Tab_Zone[], int nb_zones) {
    for (int i = 0; i < nb_zones; i++) {
        if (Tab_Zone[i].id_zone == id) {
            return 1; // Zone existe
        }
    }
    return 0; // Zone inexistante
}

// ==========================================
// CHOIX 3 : OPERATIONS DE COLLECTE ET VIDAGE
// ==========================================

void menuOperations_De_Collecte_Et_Vidage(Conteneur les_conteneur[], int nombre_conteneur, Camion les_camion[], int nombre_camion, Historique tab_histo[], int *id_coll) {
    int choix3 = -1;

    while (choix3 != 0) {
        printf(COLOR_CYAN "\n[Sous-menu : Operations de collecte et vidage]\n" COLOR_RESET);
        printf("1. Vider un conteneur\n");
        printf("2. Decharger un camion\n");
        printf("3. Afficher l'historique complet des operation de collecte\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix3) != 1) {
            printf(COLOR_RED "Erreur : Veuillez entrer un nombre valide !\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }
        switch (choix3) {
            case 1:
                OperationVidage(les_conteneur, nombre_conteneur, les_camion, nombre_camion, tab_histo, id_coll);
                break;
            case 2:
                operationdecharge(les_camion, nombre_camion);
                break;
            case 3:
                affichage_historique(tab_histo, id_coll);
                break;
            case 0:
                break;
            default:
                printf(COLOR_RED "\nChoix invalide ! Veuillez choisir une option entre 0 et 3.\n" COLOR_RESET);
        }
    }
}

void OperationVidage(Conteneur les_conteneur[], int nombre_conteneur, Camion les_camion[], int nombre_camion, Historique tab_histo[], int *id_coll) {
    if (nombre_conteneur==0){
        printf(COLOR_RED"\nil y a aucun conteneur a vider\n"COLOR_RESET);
    }

    else if (nombre_conteneur!=0){ printf(COLOR_CYAN "\n=====================\n" COLOR_RESET);
    printf(COLOR_CYAN "\nvidage d'un conteneur\n" COLOR_RESET);
    printf(COLOR_CYAN "\n=====================\n" COLOR_RESET);
    int id_c, id_cm, ind_c, ind_cam, bool_affich_id_cam, bool_affich_id_con;
    float val_oc_con;
    char ch[4];
    printf(COLOR_CYAN "\nID des conteneurs disponibles:\n" COLOR_RESET);
    les_conteneur_disponible(les_conteneur, nombre_conteneur, &bool_affich_id_con);
    if (bool_affich_id_con == 1) {
        fonction_entree_id_conteneur(les_conteneur, nombre_conteneur, &id_c, &ind_c);
        val_oc_con = les_conteneur[ind_c].val_occup_cont;
        printf(COLOR_ROSE "\nLes id des camions disponibles:" COLOR_RESET);
        les_camion_disponible(les_camion, nombre_camion, val_oc_con, &bool_affich_id_cam);
        if (bool_affich_id_cam == 1) {
            fonction_entree_id_camion(les_camion, nombre_camion, &id_cm, val_oc_con, &ind_cam);
            confirmation_operation_vidage(les_conteneur, id_c, id_cm, ind_c, ch);
            while (1) {
                if (strcmp(ch, "non") == 0) {
                    printf(COLOR_RED "operation de vidage annule" COLOR_RESET);
                    break;
                }
                les_camion[ind_cam].val_occup_cam += les_conteneur[ind_c].val_occup_cont;
                les_conteneur[ind_c].val_occup_cont = 0;
                enregitrement_historrique_collecte(tab_histo, id_c, id_cm, id_coll, val_oc_con);
                printf(COLOR_GREEN "operation de vidage validee" COLOR_RESET);
                break;
            }
        }
    }
}
}

void les_conteneur_disponible(Conteneur les_conteneur[], int nombre_conteneur, int *k) {
    int i;
    *k = 0;
    for (i = 0; i < nombre_conteneur; i++) {
        if (les_conteneur[i].val_occup_cont != 0 && les_conteneur[i].etat == true) {
            printf("%i\n", les_conteneur[i].id_cont);
            *k = 1;
        }
    }
    if (*k == 0) {
        printf(COLOR_GREEN "Tout les conteneurs sont vide" COLOR_RESET);
    }
}

void fonction_entree_id_conteneur(Conteneur les_conteneur[], int nombre_conteneur, int *id_c, int *ind_c) {
    int i, k = 0;
    while (1) {
        printf(COLOR_ROSE "\nChoisissez l'ID du conteneur que vous souhaitez vider:" COLOR_RESET);
        if (scanf("%i", id_c) == 0) {
            printf(COLOR_RED "\nErreur : Veuillez entrer un id invalide !\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }
        for (i = 0; i < nombre_conteneur; i++) {
            if ((les_conteneur[i].id_cont == *id_c) && (les_conteneur[i].etat == true) && (les_conteneur[i].val_occup_cont > 0)) {
                k = 1;
                *ind_c = i;
                break;
            }
        }
        if (k == 0) {
            printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
            continue;
        }
        break;
    }
}

void les_camion_disponible(Camion les_camion[], int nombre_camion, float val_oc_con, int *dispo) {
    int i;
    *dispo = 0;
    for (i = 0; i < nombre_camion; i++) {
        if ((les_camion[i].max_occup_cam - les_camion[i].val_occup_cam >= val_oc_con) && (les_camion[i].etat_dispo == 1)) {
            printf("\n%i\n", les_camion[i].id_cam);
            *dispo = 1;
        }
    }
    if (*dispo == 0) {
        printf(COLOR_RED "\nAucun camion disponible avec une capacite suffisante !\n" COLOR_RESET);
    }
}

void fonction_entree_id_camion(Camion les_camion[], int nombre_camion, int *id_cm, float val_oc_con, int *ind_cam) {
    int i, rr = 0;
    while (1) {
        printf(COLOR_ROSE "\nChoisissez l'ID du camion que vous voulez utiliser :" COLOR_RESET);
        if (scanf("%i", id_cm) == 0) {
            printf(COLOR_RED "\nErreur : Veuillez entrer un id valide!\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }
        for (i = 0; i < nombre_camion; i++) {
            if ((les_camion[i].id_cam == *id_cm) && (les_camion[i].etat_dispo == 1) && (les_camion[i].max_occup_cam - les_camion[i].val_occup_cam >= val_oc_con)) {
                rr = 1;
                *ind_cam = i;
                break;
            }
        }
        if (rr == 0) {
            printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
            continue;
        }
        break;
    }
}

void confirmation_operation_vidage(Conteneur les_conteneur[], int id_c, int id_cm, int ind_c, char ch[]) {
    printf(COLOR_YELLOW "\nVoulez vous vider le conteneur d'id :%i\nqui admet un volume de dechet egale a:%f\npar le camion d'id :%i\n" COLOR_RESET, id_c, les_conteneur[ind_c].val_occup_cont, id_cm);
    printf(COLOR_CYAN "oui/non:" COLOR_RESET);
    scanf("%s", ch);
    while ((strcmp(ch, "non") && strcmp(ch, "oui")) != 0) {
        while (getchar() != '\n');
        printf(COLOR_RED "\nentree: oui ou non\n" COLOR_RESET);
        printf(COLOR_YELLOW "\nVoulez vous vider le conteneur d'id :%i\nqui admet un volume de dechet egale a:%f\npar le camion d'id :%i\n" COLOR_RESET, id_c, les_conteneur[ind_c].val_occup_cont, id_cm);
        printf(COLOR_CYAN "oui/non:" COLOR_RESET);
        scanf("%s", ch);
    }
}

void enregitrement_historrique_collecte(Historique tab_histo[], int id_c, int id_cm, int *id_coll, float val_oc_con) {
    (*id_coll)++;
    Historique *h = &tab_histo[*id_coll - 1];

    time_t secondes = time(NULL);
    struct tm *instant = localtime(&secondes);

    h->id_collect      = *id_coll;
    h->id_cont         = id_c;
    h->id_cam          = id_cm;
    h->volume_collecte = val_oc_con;

    snprintf(h->date_hr_collecte.ch_date, sizeof(h->date_hr_collecte.ch_date),
             "Date : %02d/%02d/%04d\nHeure : %02d:%02d:%02d\n",
             instant->tm_mday, instant->tm_mon + 1, instant->tm_year + 1900,
             instant->tm_hour, instant->tm_min, instant->tm_sec);
}

void operationdecharge(Camion les_camion[], int nombre_camion) {
     if (nombre_camion==0){
        printf(COLOR_RED"\nil y a aucun camion a decharger\n"COLOR_RESET);
    }
    if(nombre_camion!=0){ printf(COLOR_CYAN "\n====================\n" COLOR_RESET);
    printf(COLOR_CYAN "\ndecharge d un camion\n" COLOR_RESET);
    printf(COLOR_CYAN "\n====================\n" COLOR_RESET);
    int id_cm, bool_id_cam, ind_cam;
    char ch[4];
    printf("\nles camion qui peut etre decharge:\n");
    les_camion_peut_etre_vider(les_camion, nombre_camion, &bool_id_cam);
    if (bool_id_cam == 1) {
        fonction_entree_id_camion_pour_decharge(les_camion, nombre_camion, &id_cm, &ind_cam);
        confirmation_operation_decharge(les_camion, id_cm, ch, ind_cam);
        while (1) {
            if (strcmp(ch, "non") == 0) {
                printf(COLOR_RED "operation de decharge annule" COLOR_RESET);
                break;
            }
            les_camion[ind_cam].val_occup_cam = 0;
            les_camion[ind_cam].etat_dispo = 1;
            printf(COLOR_GREEN "operation de decharge validee" COLOR_RESET);
            break;
        }
    }
}
}

void les_camion_peut_etre_vider(Camion les_camion[], int nombre_camion, int *k) {
    int i;
    *k = 0;
    for (i = 0; i < nombre_camion; i++) {
        if (les_camion[i].val_occup_cam > 0) {
            printf("\nl'id:%i\n", les_camion[i].id_cam);
            printf("\nle valeur occupe dans le camion est :%.2f\nle valeur maximale que le camion peut l'importe:%.2f\n", les_camion[i].val_occup_cam, les_camion[i].max_occup_cam);
            *k = 1;
        }
    }
    if (*k == 0) {
        printf(COLOR_GREEN "tout les camions sont decharge" COLOR_RESET);
    }
}

void fonction_entree_id_camion_pour_decharge(Camion les_camion[], int nombre_camion, int *id_cm, int *ind_cam) {
    int i, rr = 0;
    while (1) {
        printf(COLOR_ROSE "\nChoisissez l'ID du camion que vous voulez :" COLOR_RESET);
        if (scanf("%i", id_cm) == 0) {
            printf(COLOR_RED "\nErreur : Veuillez entrer un id valide !\n" COLOR_RESET);
            while (getchar() != '\n');
            continue;
        }
        for (i = 0; i < nombre_camion; i++) {
            if ((les_camion[i].id_cam == *id_cm) && (les_camion[i].val_occup_cam > 0)) {
                rr = 1;
                *ind_cam = i;
                break;
            }
            if ((les_camion[i].id_cam == *id_cm) && (les_camion[i].val_occup_cam == 0)) {
                printf(COLOR_GREEN "\nCe camion est deja decharge\n" COLOR_RESET);
                break;
            }
        }
        if (rr == 0) {
            printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
            continue;
        }
        break;
    }
}

void confirmation_operation_decharge(Camion les_camion[], int id_cm, char ch[], int ind_cam) {
    printf(COLOR_YELLOW "\nVoulez vous decharger le camion d'id :%i\nqui admet un volume de dechet egale a:%f\nest qui peut etre rempit jusqu a  :%f\n" COLOR_RESET, id_cm, les_camion[ind_cam].val_occup_cam, les_camion[ind_cam].max_occup_cam);
    printf(COLOR_CYAN "oui/non:" COLOR_RESET);
    scanf("%s", ch);
    while ((strcmp(ch, "non") && strcmp(ch, "oui")) != 0) {
        while (getchar() != '\n');
        printf(COLOR_RED "\nentree: oui ou non\n" COLOR_RESET);
        printf(COLOR_YELLOW "\nVoulez vous decharger le camion d'id :%i\nqui admet un volume de dechet egale a:%f\nest qui peut etre rempit jusqu a  :%f\n" COLOR_RESET, id_cm, les_camion[ind_cam].val_occup_cam, les_camion[ind_cam].max_occup_cam);
        printf(COLOR_CYAN "oui/non:" COLOR_RESET);
        scanf("%s", ch);
    }
}

void affichage_historique(Historique tab_histo[], int *n) {
    if (*n == 0) {
        printf(COLOR_RED "aucun operation de vidage a ete effectue" COLOR_RESET);
    }
    int i;
    if (*n != 0) {
        printf(COLOR_CYAN "\n=========================================================\n" COLOR_RESET);
        printf(COLOR_CYAN "\nAffichage d'historique complet des operations de collecte\n" COLOR_RESET);
        printf(COLOR_CYAN "\n=========================================================\n" COLOR_RESET);
        for (i = 0; i < *n; i++) {
            printf(COLOR_ROSE "\n===========\n" COLOR_RESET);
            printf(COLOR_ROSE "\ncollecte %i\n" COLOR_RESET, i + 1);
            printf(COLOR_ROSE "\n===========\n" COLOR_RESET);
            printf("\nid collecte :%i\n", tab_histo[i].id_collect);
            printf("\nid conteneur :%i\n", tab_histo[i].id_cont);
            printf("\nvaleur occupe du conteneur :%.2f\n", tab_histo[i].volume_collecte);
            printf("\nid camion :%i\n", tab_histo[i].id_cam);
            printf("\n%s\n", tab_histo[i].date_hr_collecte.ch_date);
        }
    }
}

// ==========================================
//            CHOIX 4
// ==========================================

void menuStatistiquesAlertes(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Statistiques et alertes]\n" COLOR_RESET);
}
