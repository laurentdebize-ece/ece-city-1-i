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
#define HAUTEUR_FE 864
#define LARGEUR_FE 1464
#define NBHAUTEURCASE 35
#define NBLARGEURCASE 45
#define XDepart 50
#define YDepart 50
#define LARGEURCASE 20

typedef struct {
    int chateauDeau;
    int centraleElectrique;
    int route;
    int terrainVague;
    int caserne;
}CoutBatiment;

typedef struct {
    int argent;
    int habitant;
    int capaciteEau;
    int capaciteElectricite;
}InformationJeu;

typedef struct {
    bool routePresente;
    bool habitationPresente;
    bool chateauDeauPresent;
    bool centraleElectriquePresente;
    bool construisibilite;
    int niveauBatiment;
    int numeroMaison;
}Case;


typedef struct {
    ALLEGRO_BITMAP *menuPrincipal,*staline,*trump,*map,*route1,*route2,*maison,*roue,*eclair,*eau,*herbe,*couches,*boutonCouches,
    *chateau,*usine,*bulldozer,*terrain0,*terrain1,*terrain2,*terrain3,*terrain4;
}Images;

typedef struct{
    bool fin,etatMenuPrincipal,etatMode,modeCommuniste,modeCapitaliste,etatEchap,couche1,couche2,couche3,etatBoutonReglage,
    etatCouche,route,etatNoClick,habitation,electricite,curseur,eau,demolir;
}Etats;


typedef struct{
    ALLEGRO_FONT *font1,*font2;
}Fonts;

#include "affichage.h"
#include "menu.h"
#include "jeu.h"

#endif //ECE_CITY_1_I_STRUCTURE_H
