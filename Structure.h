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
#define XDepart 25
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
    int etatAmelioration;
    bool chateauDeauConnexe;
    bool centraleConnexe;
    int chateauDeauQuiAlimente;
}Case;

typedef struct {
    int capaciteDuChateauDeau;
}ChateauDeau;

typedef struct {
    int capaciteDeLaCentrale;
}Centrale;


typedef struct {
    ALLEGRO_BITMAP *menuPrincipal,*staline,*trump,*map,*route1,*route2,*maison,*roue,*eclair,*eau,*herbe,*couches,*boutonCouches,
    *chateau,*usine,*bulldozer,*curseur,*terrain0,*terrain1,*terrain2,*terrain3,*terrain4,*watertower,*centrale;
}Images;

typedef struct{
    bool fin,etatMenuPrincipal,etatMode,modeCommuniste,modeCapitaliste,etatEchap,couche1,couche2,couche3,etatBoutonReglage,
    etatCouche,route,etatNoClick,habitation,electricite,curseur,eau,demolir;
}Etats;


typedef struct{
    ALLEGRO_FONT *font1,*font2,*font3;
}Fonts;

#include "affichage.h"
#include "menu.h"
#include "jeu.h"

#endif //ECE_CITY_1_I_STRUCTURE_H
