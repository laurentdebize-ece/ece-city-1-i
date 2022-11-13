#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"
#include "affichage.h"

void jeu();
void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void choixBoiteAoutil(ALLEGRO_EVENT event, int* curseur,int* route ,int* habitation ,int* batiment);
void calculCaseTabPixel(int* i,int* j,int x1,int y1);
void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);

#endif //ECE_CITY_1_I_JEU_H
