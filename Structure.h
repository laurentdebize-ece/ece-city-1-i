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
#define HAUTEUR_FE 764
#define LARGEUR_FE 1024
#define NBLARGEURCASE 35
#define NBLONGUEURCASE 45
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
}informationJeu;

typedef struct {
    bool routePresente;
    bool batimentPresent;
    bool construisibilite;
    int niveauBatiment;
}Case;


typedef struct {
    ALLEGRO_BITMAP *menuPrincipal,*staline,*trump,*map;
}Images;

typedef struct{
    bool fin,etatMenuPrincipal,etatMode,modeCommuniste,modeCapitaliste,etatEchap;
}Etats;

typedef struct{
    ALLEGRO_FONT *font1;
}Fonts;

#include "affichage.h"
#include "menu.h"
#include "jeu.h"

#endif //ECE_CITY_1_I_STRUCTURE_H
