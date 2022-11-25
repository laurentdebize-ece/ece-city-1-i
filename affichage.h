#ifndef ECE_CITY_1_I_AFFICHAGE_H
#define ECE_CITY_1_I_AFFICHAGE_H
#include "Structure.h"

void affichageMap(Images images,Etats etats,Fonts fonts,int x,int y,InformationJeu informationJeu,long long *compteur,int *chrono);
void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2);
void definirCaseRoute(int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,int bouton,InformationJeu* informationJeu,CoutBatiment coutBatiment);
void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison,InformationJeu* informationJeu,long long compteur, long long* compteurMaison,CoutBatiment coutBatiment);
void definirCaseChateauDeau(ALLEGRO_EVENT event, int eau, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu,CoutBatiment coutBatiment,int* nbChateauDeau);
void afficherChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void afficherCaseCurseur(int x1, int x2, int y1, int y2,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], Images images, Etats etats);
void afficherCompteur(Fonts fonts, long long * compteur, int* chrono);
void definirCaseCentraleElectrique(ALLEGRO_EVENT event, int electricite, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu,CoutBatiment coutBatiment,int* nbCentrale);
void afficherCentraleElectrique(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images);
void demolir(int bouton,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,InformationJeu* informationJeu,int demolir);
void afficherModeDeJeu(Etats etats,Fonts fonts);

void affichageMenuPrincipal(Images images,Fonts fonts,int x, int y);

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

void demolir(int bouton,Case tabCase [NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,InformationJeu* informationJeu,int demolir);


#endif //ECE_CITY_1_I_AFFICHAGE_H