#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"
#include "fifo.h"

void jeu();
void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void calculCaseTabPixel(int* i,int* j,int x1,int y1);
void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu* informationJeu, Centrale tabCentrale[65], ChateauDeau tabChateauDeau[65]);
void initialiserInfoJeu(InformationJeu* informationJeu);
void impotTaxe(InformationJeu* informationJeu, long long compteur);
void initialisationCoutBatiment(CoutBatiment* coutBatiment);

void centraleConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu *informationJeu, Centrale tabCentrale[65]);
void chateauDeauConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu *informationJeu, ChateauDeau tabChateauDeau[65]);
void rechercherRouteChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], int i, int j, int* chateauDeauConnexeRoute,int* iDuChateau,int* jDuChateau);
void rechercherRouteCentrale(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], int i, int j, int* centraleConnexe,int* iDeLaCentrale,int* jDeLaCentrale);

#endif //ECE_CITY_1_I_JEU_H
