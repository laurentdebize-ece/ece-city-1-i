#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include "Structure.h"

void affichageMap(Fonts fonts,InformationJeu informationJeu,Images images);
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu* informationJeu);
void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison,InformationJeu* informationJeu,long long compteur, long long* compteurMaison);
void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void definirCaseChateauDeau(ALLEGRO_EVENT event, int eau, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu);
void afficherChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherCaseCurseur(int x1, int x2, int y1, int y2, int curseur, int route, int habitation, int eau, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], Images images,int electricite);
void afficherCompteur(Fonts fonts, long long * compteur, int* chrono);
void definirCaseCentraleElectrique(ALLEGRO_EVENT event, int electricite, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu);
void afficherCentraleElectrique(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);

void affichageMenuPrincipal(Images images,Fonts fonts);

void choixMenuPrincipal(Etats *etats,int x,int y);

void affichageMode(Images images,Fonts fonts);

void choixMode(Etats *etats,int x,int y);

void afficherMenuEchap(Fonts fonts);

void choixMenuEchap(Etats *etats,int x,int y);

void afficherDetailsConstruction(Fonts fonts,int x ,int y);

#endif //ECE_CITY_1_I_AFFICHAGE_H
