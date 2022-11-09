//
// Created by Kevin Le Heurt on 08/11/2022.
//

#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include <allegro5/allegro.h>
#include "Structure.h"


void affichageMap();
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);
void afficherRoute(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);
void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);
void afficherBatiment(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);

#endif //ECE_CITY_1_I_AFFICHAGE_H
