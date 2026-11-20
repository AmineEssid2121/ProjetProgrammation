#include "the_head_of_the_project.h"
#include <string.h>
#include <time.h>

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
void gererMenuPrincipal(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion) {
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
                menuOperations_De_Collecte_Et_Vidage(les_conteneur,nombre_conteneur,les_camion,nombre_camion);
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

void menuOperations_De_Collecte_Et_Vidage(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion) {
    int choix3 = -1;

    while (choix3 != 0) {
    printf(COLOR_CYAN "\n[Sous-menu : Operations de collecte et vidage]\n" COLOR_RESET);
    printf("1. Vider un conteneur\n");
    printf("2. Decharger un camion\n");
    printf("3. Afficher l'historique complet des operation de collecte\n");
    printf("0. Retour au menu principal\n");
    printf("Votre choix : ");


        // Sécurisation de la saisie utilisateur
        if (scanf("%d", &choix3) != 1) {
            printf(COLOR_RED "Erreur : Veuillez entrer un nombre valide !\n" COLOR_RESET);
            while (getchar() != '\n'); // Vider le buffer de saisie en cas de mauvaise frappe
            continue;
        }
        switch (choix3){
            case 1:
                OperationVidage(les_conteneur,nombre_conteneur,les_camion,nombre_camion);
                break;
            case 2:
                operationdecharge(les_camion,nombre_camion);
                break;
            case 3:
                printf("affichage de l'historique");
                break;
            case 0:
                break;
            default:
                printf(COLOR_RED "\nChoix invalide ! Veuillez choisir une option entre 0 et 3.\n" COLOR_RESET);
        }

}
}

void menuStatistiquesAlertes(void) {
    printf(COLOR_CYAN "\n[Sous-menu : Statistiques et alertes]\n" COLOR_RESET);
}
// Les fonction du choix 3
//fonction pour vidage
void OperationVidage(Conteneur les_conteneur[],int nombre_conteneur,Camion les_camion[],int nombre_camion){
    int id_c,id_cm,ind_c,ind_cam,bool_affich_id_cam,bool_affich_id_con;
    float val_oc_con;
    char ch[4];
    printf("ID des conteneurs disponibles:\n");
    les_conteneur_disponible(les_conteneur,nombre_conteneur,&bool_affich_id_con);
    if(bool_affich_id_con==1){
            fonction_entree_id_conteneur(les_conteneur,nombre_conteneur,&id_c,&ind_c);
            val_oc_con=les_conteneur[ind_c].val_occup_cont;
            printf(COLOR_ROSE "\nLes id des camions disponibles:" COLOR_RESET);
            les_camion_disponible(les_camion,nombre_camion,val_oc_con,&bool_affich_id_cam);
            if(bool_affich_id_cam==1){
                 fonction_entree_id_camion(les_camion,nombre_camion,&id_cm,val_oc_con,&ind_cam);
                 confirmation_operation_vidage(les_conteneur,id_c,id_cm,ind_c,ch);
                 while(1){
                 if (strcmp(ch,"non")==0){
                    printf( COLOR_RED "operation de vidage annule" COLOR_RESET);
                    break;
                 }
                 les_camion[ind_cam].val_occup_cam+=les_conteneur[ind_c].val_occup_cont;
                 les_conteneur[ind_c].val_occup_cont=0;
                 printf( COLOR_GREEN "operation de vidage validee" COLOR_RESET);
                 break;
               }
            }
    }


}
void les_conteneur_disponible(Conteneur les_conteneur[],int nombre_conteneur,int *k){ //afficher l'id des conteneurs disponible
    int i;
    *k=0;
    for (i=0;i< nombre_conteneur;i++){
        if (les_conteneur[i].val_occup_cont!=0){
            printf("%i\n",les_conteneur[i].id_cont);
            *k=1;
        }

    }
    if(*k==0){
        printf(COLOR_GREEN "Tout les conteneurs sont vide" COLOR_RESET);
    }
}
void fonction_entree_id_conteneur(Conteneur les_conteneur[],int nombre_conteneur,int *id_c,int *ind_c){ // assurer que l'id du conteneur qui a ete donner est juste
    int i, k=0;
    while(1){
    printf(COLOR_ROSE "\nChoisissez l'ID du conteneur que vous souhaitez vider:" COLOR_RESET);
    if (scanf("%i",id_c)==0){
        printf(COLOR_RED "\nErreur : Veuillez entrer un id invalide !\n" COLOR_RESET);
        while ( getchar() !='\n');
        continue;
    }
    for (i=0;i<nombre_conteneur;i++){
        if ((les_conteneur[i].id_cont==*id_c)&&(les_conteneur[i].etat== false)){
            k=1;
            *ind_c=i;
            break;

        }
    }
    if(k==0){
                printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
                continue;
        }
    break;
    }
}
void les_camion_disponible(Camion les_camion[],int nombre_camion,float val_oc_con,int*dispo){  // affiche les camion disponible
    int i;
    *dispo=0;
    for (i=0;i<nombre_camion;i++){
        if ((les_camion[i].max_occup_cam - les_camion[i].val_occup_cam >= val_oc_con)&& (les_camion[i].etat_dispo==1)){
            printf("\n%i\n",les_camion[i].id_cam);
            *dispo=1;
        }
    }
     if(*dispo==0){
            printf(COLOR_RED "\nAucun camion disponible avec une capacite suffisante !\n" COLOR_RESET);
             }
}
void fonction_entree_id_camion(Camion les_camion[],int nombre_camion,int *id_cm,int val_oc_con,int *ind_cam){ // assurer que l'id du camion qui a ete donner est juste
    int i,rr=0;
    while(1){
        printf(COLOR_ROSE "\nChoisissez l'ID du camion que vous voulez :" COLOR_RESET);
        if (scanf("%i",id_cm)==0){
            printf(COLOR_RED "\nErreur : Veuillez entrer un id valide !\n" COLOR_RESET);
            while ( getchar() !='\n');
            continue;
        }
        for (i=0;i<nombre_camion;i++){
            if ((les_camion[i].id_cam==*id_cm)&&(les_camion[i].etat_dispo==1)&&(les_camion[i].max_occup_cam - les_camion[i].val_occup_cam >= val_oc_con)){
                rr=1;
                *ind_cam=i;
                break;
            }
        }
        if(rr==0){
                    printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
                    continue;
            }
        break;
        }
}
void confirmation_operation_vidage(Conteneur les_conteneur[],int id_c,int id_cm,int ind_c,char ch[]){// confirmation de l operation de vidage
    printf(COLOR_ROSE "\nVoulez vous vider le conteneur d'id :%i\nqui admet un volume de dechet egale a:%f\npar le camion d'id :%i\n" COLOR_RESET,id_c,les_conteneur[ind_c].val_occup_cont,id_cm);
    printf(COLOR_CYAN "oui/non:" COLOR_RESET);
    scanf("%s",ch);
    while ((strcmp(ch,"non")&&strcmp(ch,"oui"))!=0){
           while ( getchar() !='\n');
           printf(COLOR_RED "\nentree: oui ou non\n" COLOR_RESET);
           printf(COLOR_ROSE "\nVoulez vous vider le conteneur d'id :%i\nqui admet un volume de dechet egale a:%f\npar le camion d'id :%i\n" COLOR_RESET,id_c,les_conteneur[ind_c].val_occup_cont,id_cm);
           printf(COLOR_CYAN "oui/non:" COLOR_RESET);
           scanf("%s",ch);
           }

}
//fonction pour decharge
void operationdecharge(Camion les_camion[],int nombre_camion){
    int id_cm,bool_id_cam,ind_cam;
    char ch[4];
    printf("\nles camion qui peut etre decharge:\n");
    les_camion_peut_etre_vider(les_camion,nombre_camion,&bool_id_cam);
    if(bool_id_cam==1){
        fonction_entree_id_camion_pour_decharge(les_camion,nombre_camion,&id_cm,&ind_cam);
        confirmation_operation_decharge(les_camion,id_cm,ch,ind_cam);
        while(1){
                 if (strcmp(ch,"non")==0){
                    printf( COLOR_RED "operation de decharge annule" COLOR_RESET);
                    break;
                 }
                 les_camion[ind_cam].val_occup_cam=0;
                 les_camion[ind_cam].etat_dispo=1;
                 printf( COLOR_GREEN "operation de decharge validee" COLOR_RESET);
                 break;
               }
    }
}
void les_camion_peut_etre_vider(Camion les_camion[],int nombre_camion,int *k){ // affiche les camion qui peut etre videe
    int i;
    *k=0;
    for (i=0;i<nombre_camion;i++){
        if (les_camion[i].val_occup_cam > 0){
            printf("\nl'id:%i\n",les_camion[i].id_cam);
            printf("\nle valeur occupe dans le camion est :%f\nle valeur maximale que le camion peut l'importe:%f\n",les_camion[i].val_occup_cam,les_camion[i].max_occup_cam);
            *k=1;
        }
    }
    if(*k==0){
        printf(COLOR_GREEN "tout les camions sont decharge" COLOR_RESET);
    }
}
void fonction_entree_id_camion_pour_decharge(Camion les_camion[],int nombre_camion,int*id_cm,int *ind_cam){ // assurer que l'id du camion qui a ete donner est juste
    int i,rr=0;
    while(1){
        printf(COLOR_ROSE "\nChoisissez l'ID du camion que vous voulez :" COLOR_RESET);
        if (scanf("%i",id_cm)==0){
            printf(COLOR_RED "\nErreur : Veuillez entrer un id valide !\n" COLOR_RESET);
            while ( getchar() !='\n');
            continue;
        }
        for (i=0;i<nombre_camion;i++){
            if ((les_camion[i].id_cam==*id_cm)&&(les_camion[i].val_occup_cam >0)){
                rr=1;
                *ind_cam=i;
                break;
            }
            if ((les_camion[i].id_cam==*id_cm)&&(les_camion[i].val_occup_cam ==0)){
                printf(COLOR_GREEN "\nCe camion est decharger\n" COLOR_RESET);
                rr=1;
                break;
        }}
        if(rr==0){
                    printf(COLOR_RED "\nl'id que vous avez entree n'est pas disponible\n" COLOR_RESET);
                    continue;


        }


   break; }
 }
void confirmation_operation_decharge(Camion les_camion[],int id_cm,char ch[],int ind_cam){// confirmation de l operation de vidage
    printf(COLOR_ROSE "\nVoulez vous decharger le camion d'id :%i\nqui admet un volume de dechet egale a:%f\nest qui peut etre rempit jusqu a  :%f\n" COLOR_RESET,id_cm,les_camion[ind_cam].val_occup_cam,les_camion[ind_cam].max_occup_cam);
    printf(COLOR_CYAN "oui/non:" COLOR_RESET);
    scanf("%s",ch);
    while ((strcmp(ch,"non")&&strcmp(ch,"oui"))!=0){
           while ( getchar() !='\n');
           printf(COLOR_RED "\nentree: oui ou non\n" COLOR_RESET);
           printf(COLOR_ROSE "\nVoulez vous decharger le camion d'id :%i\nqui admet un volume de dechet egale a:%f\nest qui peut etre rempit jusqu a  :%f\n" COLOR_RESET,id_cm,les_camion[ind_cam].val_occup_cam,les_camion[ind_cam].max_occup_cam);
           printf(COLOR_CYAN "oui/non:" COLOR_RESET);
           scanf("%s",ch);
           }

}
void enregitrement_historrique_collecte(Historique tab_histo[],int id_c,int id_cm,int *id_coll,char date_heur_collect[],float val_oc_con){// enregistremnt d'historique
    tab_histo[*id_coll -1].id_cont=id_c;
    tab_histo[*id_coll -1].id_cam=id_cm;
    tab_histo[*id_coll -1].id_collect=*id_coll;
    tab_histo[*id_coll -1].volume_collecte=val_oc_con;
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant= *localtime(&secondes);


}
