#ifndef ECE_CITY_1_I_STRUCTURE_H
#define ECE_CITY_1_I_STRUCTURE_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


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



#endif //ECE_CITY_1_I_STRUCTURE_H
