#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"

void jeu();
void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void choixBoiteAoutil(ALLEGRO_EVENT event, int* curseur,int* route ,int* habitation ,int* eau, int* electricite);
void calculCaseTabPixel(int* i,int* j,int x1,int y1);
void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], long long compteurMaison);
void initialiserInfoJeu(InformationJeu* informationJeu);

#endif //ECE_CITY_1_I_JEU_H
