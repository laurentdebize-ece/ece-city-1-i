#ifndef ECE_CITY_1_I_JEU_H
#define ECE_CITY_1_I_JEU_H
#include "Structure.h"
CoutBatiment lire_fichier_texte(char *nomFichier);
//Case lecture_fichier_texte2(char *nomFichier);
InformationJeu sauvegarde_information_joueur( InformationJeu joueur);
InformationJeu lire_information_Joueur(InformationJeu joueur);
InformationJeu lirePlateauDeBase();
void sauvegarderNouveauPlateau(Case tabcase[NBHAUTEURCASE][NBLARGEURCASE]);
void liresauvegardeDuplateau(Case tabcase[NBHAUTEURCASE][NBLARGEURCASE]);
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
