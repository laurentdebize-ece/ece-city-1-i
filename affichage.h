#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include "Structure.h"

void affichageMap(Images images,Etats etats,Fonts fonts,int x,int y);
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,int bouton);
void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison);
void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherBatiment(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void afficherCaseCurseur(int x1,int x2,int y1,int y2,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Etats etats);
void afficherCompteur(Fonts fonts, long long *compteur, int* chrono);

void affichageMenuPrincipal(Images images,Fonts fonts);

void choixMenuPrincipal(Etats *etats,int x,int y);

void affichageMode(Images images,Fonts fonts);

void choixMode(Etats *etats,int x,int y);

void afficherMenuEchap(Fonts fonts);

void choixMenuEchap(Etats *etats,int x,int y);

void afficherPremiereCouche(Images images,Fonts fonts);

void afficherDeuxiemeCouche(Images images,Fonts fonts);

void afficherTroisiemeCouche(Images images,Fonts fonts);

void afficherMenuBoutonOutil(Images images,Etats *etats,Fonts fonts,int x,int y);

void choixJeu(Etats *etats,int x,int y);

void choixMenuBoutonCouches(Etats *etats,int x,int y);

void choixBoutonOutil(Etats *etats,int x,int y);


#endif //ECE_CITY_1_I_AFFICHAGE_H
