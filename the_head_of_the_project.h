#ifndef THE_HEAD_OF_THE_PROJECT_H_INCLUDED
#define THE_HEAD_OF_THE_PROJECT_H_INCLUDED
typedef struct conteneurs_de_dechets{
    int id_cont;
    char emplacement[100];
    float max_occup_cont;
    float val_notif_cont;
    float val_occup_cont;
    int id_zone;
    int etat;


}CONT;
typedef struct camions_de_collecte{
    int id_cam;
    char matricule[100];
    float max_occup_cam;
    float val_occup_cam;
    int id_zone;
    int etat_dispo;

}CAM;
typedef struct zones_de_collecte{
    int id_zone;
    char nom_zone[100];
    char description[100];

}ZONE;


#endif // THE_HEAD_OF_THE_PROJECT_H_INCLUDED
