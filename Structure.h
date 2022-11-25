#ifndef ECE_CITY_1_I_STRUCTURE_H
#define ECE_CITY_1_I_STRUCTURE_H



#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#define HAUTEUR_FE 768
#define LARGEUR_FE 1264
#define NBHAUTEURCASE 35
#define NBLARGEURCASE 45
#define NOMBRE_DE_COLLONNE 45
#define NOMBRE_DE_LIGNE 35
#define XDepart 25
#define YDepart 50
#define LARGEURCASE 20

typedef struct {
    int route;
    int canalisation;
    int ligneelectrique;
    int cabane;
    int maison;
    int immeuble;
    int gratteciel;
    int chateauDeau;
    int centraleElectrique;
    int terrainVague;
    int caserne;
    int nombrehabitantsroute;
    int nombrehabitantscanalisation;
    int nombrehabitantsligneelectrique;
    int nombrehabitantscabane;
    int nombrehabitantsmaison;
    int nombrehabitantsimmeuble;
    int nombrehabitantsgratteciel;
    int nombrehabitantschateauDeau;
    int nombrehabitantscentraleElectrique;
    int nombrehabitantsterrainVague;
    int nombrehabitantscaserne;


}CoutBatiment;


typedef struct {
    int argent;
    int habitant;
    int capaciteEau;
    int capaciteElectricite;

}InformationJeu;

typedef struct {
    int routePresente;
    int habitationPresente;
    int chateauDeauPresent;
    int centraleElectriquePresente;
    int construisibilite;
    int niveauBatiment;
    int numeroMaison;
    int numeroChateauDeau;
    int numeroCentrale;
    int valeurDansLeFichierTexte;
    int caseConnexeRoute;
    int niveauMaxHabitation;
    int couleur;
    int pred;

}Case;


typedef struct {
    ALLEGRO_BITMAP *menuPrincipal,*staline,*trump,*map,*route1,*route2,*maison,*roue,*eclair,*eau,*herbe,*couches,*boutonCouches,
    *chateau,*usine,*bulldozer,*curseur,*terrain0,*terrain1,*terrain2,*terrain3,*terrain4,*watertower,*centrale,*sauvegarde;
}Images;

typedef struct{
    bool fin,etatMenuPrincipal,etatMode,modeCommuniste,modeCapitaliste,etatEchap,couche1,couche2,couche3,etatBoutonReglage,
            etatCouche,route,etatNoClick,habitation,electricite,curseur,eau,demolir;
}Etats;


typedef struct{
    ALLEGRO_FONT *font1,*font2,*font3;
}Fonts;


typedef struct {
    int argent;
    InformationJeu info;
} Joueur;

#include "affichage.h"
#include "jeu.h"

#endif //ECE_CITY_1_I_STRUCTURE_H