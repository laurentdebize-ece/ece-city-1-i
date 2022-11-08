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
#define LARGEUR_FE 1436
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
    ALLEGRO_BITMAP *menuPrincipal
}Images;

#include "affichage.h"
#include "menu.h"

#endif //ECE_CITY_1_I_STRUCTURE_H
