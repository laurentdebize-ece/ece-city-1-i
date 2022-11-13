#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include "Structure.h"

void affichageMap(Fonts fonts);
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison);
void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherBatiment(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherCaseCurseur(int x1,int x2,int y1,int y2, int curseur, int route, int habitation, int batiment,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherCompteur(Fonts fonts, int* compteur, int* chrono);

void affichageMenuPrincipal(Images images,Fonts fonts);

void choixMenuPrincipal(Etats *etats,int x,int y);

void affichageMode(Images images,Fonts fonts);

void choixMode(Etats *etats,int x,int y);

#endif //ECE_CITY_1_I_AFFICHAGE_H
