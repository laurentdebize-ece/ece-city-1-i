#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"
CoutBatiment lire_fichier_texte(char *nomFichier);
//Case lecture_fichier_texte2(char *nomFichier);
InformationJeu sauvegarde_information_joueur( InformationJeu joueur);
        void jeu();
void jeu1();
void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]);
void choixBoiteAoutil(ALLEGRO_EVENT event, Etats *etats);
void calculCaseTabPixel(int* i,int* j,int x1,int y1);
void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu* informationJeu);
void initialiserInfoJeu(InformationJeu* informationJeu);
void impotTaxe(InformationJeu* informationJeu, long long compteur);

void chateauDeauConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu* informationJeu);



#endif //ECE_CITY_1_I_JEU_H