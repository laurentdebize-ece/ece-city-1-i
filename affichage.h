#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include "Structure.h"

void affichageMap();
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(int route, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE],int xMouse,int yMouse);
void afficherRoute(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);
void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);
void afficherBatiment(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]);

void affichageMenuPrincipal(Images images,Fonts fonts);

void choixMenuPrincipal(Etats *etats,int x,int y);

void affichageMode(Images images,Fonts fonts);

void choixMode(Etats *etats,int x,int y);

#endif //ECE_CITY_1_I_AFFICHAGE_H
