#include <stdio.h>
#include <stdlib.h>
#include "the_head_of_the_project.h"
#include <string.h>

int main() {
    // Lancement de la boucle d'interface
    Conteneur les_conteneur[50];
    Camion les_camion[50];
    Historique tab_hist[50];
    int nombre_conteneur=1,nombre_camion=1;
    strcpy(les_conteneur[0].emplacement,"test");
    les_conteneur[0].etat=false;
    les_conteneur[0].id_cont=478;
    les_conteneur[0].id_zone=692;
    les_conteneur[0].max_occup_cont=2000;
    les_conteneur[0].val_notif_cont=1500;
    les_conteneur[0].val_occup_cont=1000;
    les_camion[0].etat_dispo=true;
    les_camion[0].id_cam=500;
    les_camion[0].id_zone=201;
    strcpy(les_camion[0].matricule,"mat");
    les_camion[0].max_occup_cam=12000;
    les_camion[0].val_occup_cam=2000;
    gererMenuPrincipal(les_conteneur,nombre_conteneur,les_camion,nombre_camion);


    return 0;
}
