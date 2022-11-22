#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"

void jeu();
void jeu1();
void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void choixBoiteAoutil(ALLEGRO_EVENT event, Etats *etats);
void calculCaseTabPixel(int* i,int* j,int x1,int y1);
void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void initialiserInfoJeu(InformationJeu* informationJeu);
void impotTaxe(InformationJeu* informationJeu, long long compteur);
void initialisationCoutBatiment(CoutBatiment* coutBatiment);
void chateauDeauConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], long long compteur);

Global lecture_fichier_texte(char *nomFichier);
Global lecture_fichier_texte2(char *nomFichier);
Global sauvegarde_information_joueur(Global Joueur);

#endif //ECE_CITY_1_I_JEU_H
