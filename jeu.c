//
// Created by Kevin Le Heurt on 09/11/2022.
//

#include "jeu.h"

void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]) {
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            tabCase[i][j].routePresente = 0;
            tabCase[i][j].habitationPresente = 0;
            tabCase[i][j].chateauDeauPresent = 0;
            tabCase[i][j].centraleElectriquePresente = 0;
            tabCase[i][j].construisibilite = 0;
            tabCase[i][j].niveauBatiment = 0;
            tabCase[i][j].numeroMaison = 0;
            tabCase[i][j].niveauMaxHabitation = 0;
            tabCase[i][j].couleur = 0;
            tabCase[i][j].etatAmelioration = 0;
            tabCase[i][j].chateauDeauConnexe = 0;
            tabCase[i][j].centraleConnexe = 0;
            tabCase[i][j].chateauDeauQuiAlimente = 0;

        }
    }
}

void initialiserInfoJeu(InformationJeu *informationJeu) {
    informationJeu->argent = 500000;
    informationJeu->capaciteEau = 0;
    informationJeu->capaciteElectricite = 0;
    informationJeu->habitant = 0;
}

void initialisationCoutBatiment(CoutBatiment *coutBatiment) {
    coutBatiment->route = 10;
    coutBatiment->terrainVague = 1000;
    coutBatiment->centraleElectrique = 100000;
    coutBatiment->chateauDeau = 100000;
}

void calculCaseTabPixel(int *i, int *j, int x1, int y1) {
    *i = (y1 - YDepart) / LARGEURCASE;
    *j = (x1 - XDepart) / LARGEURCASE;
}

void rechercherRouteChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], int i, int j, int* chateauDeauConnexeRoute,int* iDuChateau,int* jDuChateau){
    int oooo = 0;
    while (oooo!=1 && *chateauDeauConnexeRoute==0){
        if (tabCase[i][j+1].routePresente == 1 && tabCase[i][j+1].couleur == 0){
            tabCase[i][j+1].couleur = 1;
            rechercherRouteChateauDeau(tabCase, i, j + 1, chateauDeauConnexeRoute,iDuChateau,jDuChateau);
        }else if (tabCase[i][j+1].chateauDeauPresent){
            *chateauDeauConnexeRoute = 1;
            *iDuChateau = i;
            *jDuChateau = j+1;
        }

        if (tabCase[i][j-1].routePresente == 1 && tabCase[i][j-1].couleur == 0){
            tabCase[i][j-1].couleur = 1;
            rechercherRouteChateauDeau(tabCase, i, j - 1, chateauDeauConnexeRoute,iDuChateau,jDuChateau);
        }else if (tabCase[i][j-1].chateauDeauPresent){
            *chateauDeauConnexeRoute = 1;
            *iDuChateau = i;
            *jDuChateau = j-1;
        }


        if (tabCase[i+1][j].routePresente == 1 && tabCase[i+1][j].couleur == 0){
            tabCase[i+1][j].couleur = 1;
            rechercherRouteChateauDeau(tabCase, i + 1, j, chateauDeauConnexeRoute,iDuChateau,jDuChateau);
        }else if (tabCase[i+1][j].chateauDeauPresent){
            *chateauDeauConnexeRoute = 1;
            *iDuChateau = i+1;
            *jDuChateau = j;
        }

        if (tabCase[i-1][j].routePresente == 1 && tabCase[i-1][j].couleur == 0){
            tabCase[i-1][j].couleur = 1;
            rechercherRouteChateauDeau(tabCase, i - 1, j, chateauDeauConnexeRoute,iDuChateau,jDuChateau);
        }else if (tabCase[i-1][j].chateauDeauPresent){
            *chateauDeauConnexeRoute = 1;
            *iDuChateau = i-1;
            *jDuChateau = j;
        }

        if (tabCase[i][j + 1].habitationPresente ||
            tabCase[i][j + 1].routePresente == 0 || tabCase[i][j + 1].centraleElectriquePresente && tabCase[i][j - 1].habitationPresente ||
            tabCase[i][j - 1].routePresente == 0 || tabCase[i][j - 1].centraleElectriquePresente && tabCase[i + 1][j].habitationPresente ||
            tabCase[i + 1][j].routePresente == 0 || tabCase[i+1][j].centraleElectriquePresente && tabCase[i - 1][j].habitationPresente ||
            tabCase[i - 1][j].routePresente == 0 || tabCase[i-1][j].centraleElectriquePresente) {
            oooo = 1;
        }


    }
}

void rechercherRouteCentrale(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], int i, int j, int* centraleConnexe,int* iDeLaCentrale,int* jDeLaCentrale){
    int oooo = 0;
    while (oooo!=1 && *centraleConnexe==0){
        if (tabCase[i][j+1].routePresente == 1 && tabCase[i][j+1].couleur == 0){
            tabCase[i][j+1].couleur = 1;
            rechercherRouteCentrale(tabCase, i, j + 1, centraleConnexe,iDeLaCentrale,jDeLaCentrale);
        }else if (tabCase[i][j+1].centraleElectriquePresente){
            *centraleConnexe = 1;
            *iDeLaCentrale = i;
            *jDeLaCentrale = j+1;

        }

        if (tabCase[i][j-1].routePresente == 1 && tabCase[i][j-1].couleur == 0){
            tabCase[i][j-1].couleur = 1;
            rechercherRouteCentrale(tabCase, i, j - 1, centraleConnexe,iDeLaCentrale,jDeLaCentrale);
        }else if (tabCase[i][j-1].centraleElectriquePresente){
            *centraleConnexe = 1;
            *iDeLaCentrale = i;
            *jDeLaCentrale = j-1;
        }


        if (tabCase[i+1][j].routePresente == 1 && tabCase[i+1][j].couleur == 0){
            tabCase[i+1][j].couleur = 1;
            rechercherRouteCentrale(tabCase, i + 1, j, centraleConnexe,iDeLaCentrale,jDeLaCentrale);
        }else if (tabCase[i+1][j].centraleElectriquePresente){
            *centraleConnexe = 1;
            *iDeLaCentrale = i+1;
            *jDeLaCentrale = j;
        }

        if (tabCase[i-1][j].routePresente == 1 && tabCase[i-1][j].couleur == 0){
            tabCase[i-1][j].couleur = 1;
            rechercherRouteCentrale(tabCase, i - 1, j, centraleConnexe,iDeLaCentrale,jDeLaCentrale);
        }else if (tabCase[i-1][j].centraleElectriquePresente){
            *centraleConnexe = 1;
            *iDeLaCentrale = i-1;
            *jDeLaCentrale = j;
        }

        if (tabCase[i][j + 1].habitationPresente ||
            tabCase[i][j + 1].routePresente == 0 || tabCase[i][j + 1].chateauDeauPresent && tabCase[i][j - 1].habitationPresente ||
            tabCase[i][j - 1].routePresente == 0 || tabCase[i][j - 1].chateauDeauPresent && tabCase[i + 1][j].habitationPresente ||
            tabCase[i + 1][j].routePresente == 0 || tabCase[i+1][j].chateauDeauPresent && tabCase[i - 1][j].habitationPresente ||
            tabCase[i - 1][j].routePresente == 0 || tabCase[i-1][j].chateauDeauPresent) {
            oooo = 1;
        }
    }
}

void ameliorerHabitation(long long compteur, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu *informationJeu, Centrale tabCentrale[65], ChateauDeau tabChateauDeau[65]) {
    int chateauDeauConnexe = 0;
    int centraleConnexe = 0;
    int iDeLaCentrale = 0;
    int jDeLaCentrale = 0;
    int iDuChateau = 0;
    int jDuChateau = 0;

    if ((compteur % 150 == 0)) {
        for (int i = 0; i < NBHAUTEURCASE; i++) {
            for (int j = 0; j < NBLARGEURCASE; j++) {
                if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].construisibilite == 1) {
                    for (int k = 0; k < 3; ++k) {
                        if (tabCase[i+k][j-1].routePresente && tabCase[i+k][j-1].couleur == 0){
                            tabCase[i+k][j-1].couleur = 1;
                            rechercherRouteChateauDeau(tabCase, i + k, j - 1, &chateauDeauConnexe,&iDuChateau,&jDuChateau);
                            for (int o = 0; o < NBHAUTEURCASE; o++) {
                                for (int z = 0; z < NBLARGEURCASE; z++) {
                                    tabCase[o][z].couleur = 0;
                                }
                            }
                            rechercherRouteCentrale(tabCase,i+k,j-1,&centraleConnexe,&iDeLaCentrale,&jDeLaCentrale);
                        }
                        if (tabCase[i+k][j+3].routePresente && tabCase[i+k][j+3].couleur == 0){
                            tabCase[i+k][j+3].couleur = 1;
                            rechercherRouteChateauDeau(tabCase, i + k, j + 3, &chateauDeauConnexe,&iDuChateau,&jDuChateau);
                            for (int o = 0; o < NBHAUTEURCASE; o++) {
                                for (int z = 0; z < NBLARGEURCASE; z++) {
                                    tabCase[o][z].couleur = 0;
                                }
                            }
                            rechercherRouteCentrale(tabCase,i+k,j+3,&centraleConnexe,&iDeLaCentrale,&jDeLaCentrale);
                        }

                    }
                    for (int l = 0; l < 3; ++l) {
                        if (tabCase[i-1][j+l].routePresente && tabCase[i-1][j+l].couleur == 0){
                            tabCase[i-1][j+l].couleur = 1;
                            rechercherRouteChateauDeau(tabCase, i - 1, j + l, &chateauDeauConnexe,&iDuChateau,&jDuChateau);
                            for (int o = 0; o < NBHAUTEURCASE; o++) {
                                for (int z = 0; z < NBLARGEURCASE; z++) {
                                    tabCase[o][z].couleur = 0;
                                }
                            }
                            rechercherRouteCentrale(tabCase,i-1,j+l,&centraleConnexe,&iDeLaCentrale,&jDeLaCentrale);


                        }
                        if (tabCase[i+3][j+l].routePresente && tabCase[i+3][j+l].couleur == 0){
                            tabCase[i+3][j+l].couleur = 1;
                            rechercherRouteChateauDeau(tabCase, i + 3, j + l, &chateauDeauConnexe,&iDuChateau,&jDuChateau);
                            for (int o = 0; o < NBHAUTEURCASE; o++) {
                                for (int z = 0; z < NBLARGEURCASE; z++) {
                                    tabCase[o][z].couleur = 0;
                                }
                            }
                            rechercherRouteCentrale(tabCase,i+3,j+l,&centraleConnexe,&iDeLaCentrale,&jDeLaCentrale);

                        }
                    }



                    if (chateauDeauConnexe==1 && centraleConnexe==1) {
                        tabCase[i][j].chateauDeauQuiAlimente = tabCase[iDuChateau][jDuChateau].numeroChateauDeau;

                        chateauDeauConnexe = 0;
                        centraleConnexe = 0;
                        for (int o = 0; o < NBHAUTEURCASE; o++) {
                            for (int z = 0; z < NBLARGEURCASE; z++) {
                                tabCase[o][z].couleur = 0;
                            }
                        }
                        for (int k = i; k < i + 3; k++) {
                            for (int l = j; l < j + 3; l++) {
                                if (tabCase[k][l].niveauBatiment < 4) {
                                    if (tabCase[i][j].niveauBatiment == 0 &&
                                        tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale >=
                                        10
                                        &&
                                        tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau >=
                                        10 ) {
                                        tabCase[k][l].niveauBatiment++;
                                    } else if (tabCase[i][j].niveauBatiment == 1 &&
                                               tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale >=
                                               40
                                               &&
                                               tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau >=
                                               40 ) {
                                        tabCase[k][l].niveauBatiment++;
                                    } else if (tabCase[i][j].niveauBatiment == 2 &&
                                               tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale >=
                                               50
                                               &&
                                               tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau >=
                                               50 ) {
                                        tabCase[k][l].niveauBatiment++;
                                    } else if (tabCase[i][j].niveauBatiment == 3 &&
                                               tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale >=
                                               900
                                               &&
                                               tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau >=
                                               900) {
                                        tabCase[k][l].niveauBatiment++;
                                    }
                                }
                            }
                        }
                    }
                }

                if (tabCase[i][j].niveauBatiment == 1 && tabCase[i][j].construisibilite == 1 &&
                    tabCase[i][j].niveauMaxHabitation == 0 && informationJeu->capaciteEau >= 10 &&
                    informationJeu->capaciteElectricite >= 10 && tabCase[i][j].etatAmelioration == 0) {
                    informationJeu->habitant += 10;
                    informationJeu->capaciteEau -= 10;
                    tabCase[i][j].etatAmelioration = 1;
                    informationJeu->capaciteElectricite -= 10;
                    tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale -=10;
                    tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau -=10;

                } else if (tabCase[i][j].niveauBatiment == 2 && tabCase[i][j].construisibilite == 1 &&
                           tabCase[i][j].niveauMaxHabitation == 0 && informationJeu->capaciteEau >= 40 &&
                           informationJeu->capaciteElectricite >= 40 && tabCase[i][j].etatAmelioration == 1) {
                    informationJeu->habitant += 40;
                    informationJeu->capaciteEau -= 40;
                    tabCase[i][j].etatAmelioration = 2;
                    informationJeu->capaciteElectricite -= 40;
                    tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale -=40;
                    tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau -=40;

                } else if (tabCase[i][j].niveauBatiment == 3 && tabCase[i][j].construisibilite == 1 &&
                           tabCase[i][j].niveauMaxHabitation == 0 && informationJeu->capaciteEau >= 50 &&
                           informationJeu->capaciteElectricite >= 50 && tabCase[i][j].etatAmelioration == 2) {
                    informationJeu->habitant += 50;
                    informationJeu->capaciteEau -= 50;
                    tabCase[i][j].etatAmelioration = 3;
                    informationJeu->capaciteElectricite -= 50;
                    tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale -=50;
                    tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau -=50;

                } else if (tabCase[i][j].niveauBatiment == 4 && tabCase[i][j].construisibilite == 1 &&
                           tabCase[i][j].niveauMaxHabitation == 0 && informationJeu->capaciteEau >= 900 &&
                           informationJeu->capaciteElectricite >= 900 && tabCase[i][j].etatAmelioration == 3) {
                    informationJeu->habitant += 900;
                    informationJeu->capaciteEau -= 900;
                    tabCase[i][j].etatAmelioration = 4;
                    informationJeu->capaciteElectricite -= 900;
                    tabCentrale[tabCase[iDeLaCentrale][jDeLaCentrale].numeroCentrale].capaciteDeLaCentrale -=900;
                    tabChateauDeau[tabCase[iDuChateau][jDuChateau].numeroChateauDeau].capaciteDuChateauDeau -=900;

                }
                if (tabCase[i][j].niveauBatiment == 4) {
                    tabCase[i][j].niveauMaxHabitation = 1;
                }

            }
        }
    }

}


void impotTaxe(InformationJeu *informationJeu, long long compteur) {
    if (compteur % 150 == 0) {
        informationJeu->argent += informationJeu->habitant * 10;
    }
}

void centraleConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu *informationJeu, Centrale tabCentrale[65]){
    for (int i = 0; i < NBHAUTEURCASE; ++i) {
        for (int j = 0; j < NBLARGEURCASE; ++j) {
            if (tabCase[i][j].centraleElectriquePresente && tabCase[i][j].construisibilite && tabCase[i][j].centraleConnexe == 0) {
                if (tabCase[i][j - 1].routePresente == 1 || tabCase[i + 1][j - 1].routePresente == 1 ||
                    tabCase[i + 2][j - 1].routePresente == 1 || tabCase[i + 3][j - 1].routePresente == 1 ||
                    tabCase[i + 4][j - 1].routePresente == 1 || tabCase[i + 5][j - 1].routePresente == 1 ||

                    tabCase[i][j + 4].routePresente == 1 || tabCase[i + 1][j + 4].routePresente == 1 ||
                    tabCase[i + 2][j + 4].routePresente == 1 || tabCase[i + 3][j + 4].routePresente == 1 ||
                    tabCase[i + 4][j + 4].routePresente == 1 || tabCase[i + 5][j + 4].routePresente == 1 ||

                    tabCase[i - 1][j].routePresente == 1 || tabCase[i - 1][j + 1].routePresente == 1 ||
                    tabCase[i - 1][j + 2].routePresente == 1 || tabCase[i - 1][j + 3].routePresente == 1 ||

                    tabCase[i + 6][j].routePresente == 1 || tabCase[i + 6][j + 1].routePresente == 1 ||
                    tabCase[i + 6][j + 2].routePresente == 1 || tabCase[i + 6][j + 3].routePresente == 1) {

                    informationJeu->capaciteElectricite += 5000;
                    tabCentrale[tabCase[i][j].numeroCentrale].capaciteDeLaCentrale += 5000;
                    tabCase[i][j].centraleConnexe = 1;

                }


            }
        }
    }

    for (int i = 0; i < NBHAUTEURCASE; ++i) {
        for (int j = 0; j < NBLARGEURCASE; ++j) {
            if (tabCase[i][j].centraleElectriquePresente && tabCase[i][j].construisibilite && tabCase[i][j].centraleConnexe == 1) {
                if (tabCase[i][j - 1].routePresente == 0 && tabCase[i + 1][j - 1].routePresente == 0 &&
                    tabCase[i + 2][j - 1].routePresente == 0 && tabCase[i + 3][j - 1].routePresente == 0 &&
                    tabCase[i + 4][j - 1].routePresente == 0 && tabCase[i + 5][j - 1].routePresente == 0 &&

                    tabCase[i][j + 4].routePresente == 0 && tabCase[i + 1][j + 4].routePresente == 0 &&
                    tabCase[i + 2][j + 4].routePresente == 0 && tabCase[i + 3][j + 4].routePresente == 0 &&
                    tabCase[i + 4][j + 4].routePresente == 0 && tabCase[i + 5][j + 4].routePresente == 0 &&

                    tabCase[i - 1][j].routePresente == 0 && tabCase[i - 1][j + 1].routePresente == 0 &&
                    tabCase[i - 1][j + 2].routePresente == 0 && tabCase[i - 1][j + 3].routePresente == 0 &&

                    tabCase[i + 6][j].routePresente == 0 && tabCase[i + 6][j + 1].routePresente == 0 &&
                    tabCase[i + 6][j + 2].routePresente == 0 && tabCase[i + 6][j + 3].routePresente == 0) {

                    tabCase[i][j].centraleConnexe = 0;
                    informationJeu->capaciteElectricite -= 5000;
                }


            }
        }
    }

}

void chateauDeauConnexe(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu *informationJeu, ChateauDeau tabChateauDeau[65]){
    for (int i = 0; i < NBHAUTEURCASE; ++i) {
        for (int j = 0; j < NBLARGEURCASE; ++j) {
            if (tabCase[i][j].chateauDeauPresent && tabCase[i][j].construisibilite && tabCase[i][j].chateauDeauConnexe == 0) {
                if (tabCase[i][j - 1].routePresente == 1 || tabCase[i + 1][j - 1].routePresente == 1 ||
                    tabCase[i + 2][j - 1].routePresente == 1 || tabCase[i + 3][j - 1].routePresente == 1 ||
                    tabCase[i + 4][j - 1].routePresente == 1 || tabCase[i + 5][j - 1].routePresente == 1 ||

                    tabCase[i][j + 4].routePresente == 1 || tabCase[i + 1][j + 4].routePresente == 1 ||
                    tabCase[i + 2][j + 4].routePresente == 1 || tabCase[i + 3][j + 4].routePresente == 1 ||
                    tabCase[i + 4][j + 4].routePresente == 1 || tabCase[i + 5][j + 4].routePresente == 1 ||

                    tabCase[i - 1][j].routePresente == 1 || tabCase[i - 1][j + 1].routePresente == 1 ||
                    tabCase[i - 1][j + 2].routePresente == 1 || tabCase[i - 1][j + 3].routePresente == 1 ||

                    tabCase[i + 6][j].routePresente == 1 || tabCase[i + 6][j + 1].routePresente == 1 ||
                    tabCase[i + 6][j + 2].routePresente == 1 || tabCase[i + 6][j + 3].routePresente == 1) {

                    informationJeu->capaciteEau += 5000;
                    tabChateauDeau[tabCase[i][j].numeroChateauDeau].capaciteDuChateauDeau += 5000;
                    tabCase[i][j].chateauDeauConnexe = 1;

                }


            }
        }
    }

    for (int i = 0; i < NBHAUTEURCASE; ++i) {
        for (int j = 0; j < NBLARGEURCASE; ++j) {
            if (tabCase[i][j].chateauDeauPresent && tabCase[i][j].construisibilite && tabCase[i][j].chateauDeauConnexe == 1) {
                if (tabCase[i][j - 1].routePresente == 0 && tabCase[i + 1][j - 1].routePresente == 0 &&
                    tabCase[i + 2][j - 1].routePresente == 0 && tabCase[i + 3][j - 1].routePresente == 0 &&
                    tabCase[i + 4][j - 1].routePresente == 0 && tabCase[i + 5][j - 1].routePresente == 0 &&

                    tabCase[i][j + 4].routePresente == 0 && tabCase[i + 1][j + 4].routePresente == 0 &&
                    tabCase[i + 2][j + 4].routePresente == 0 && tabCase[i + 3][j + 4].routePresente == 0 &&
                    tabCase[i + 4][j + 4].routePresente == 0 && tabCase[i + 5][j + 4].routePresente == 0 &&

                    tabCase[i - 1][j].routePresente == 0 && tabCase[i - 1][j + 1].routePresente == 0 &&
                    tabCase[i - 1][j + 2].routePresente == 0 && tabCase[i - 1][j + 3].routePresente == 0 &&

                    tabCase[i + 6][j].routePresente == 0 && tabCase[i + 6][j + 1].routePresente == 0 &&
                    tabCase[i + 6][j + 2].routePresente == 0 && tabCase[i + 6][j + 3].routePresente == 0) {

                    tabCase[i][j].chateauDeauConnexe = 0;
                    tabChateauDeau[tabCase[i][j].numeroChateauDeau].capaciteDuChateauDeau -= 5000;
                    informationJeu->capaciteEau -= 5000;

                }


            }
        }
    }

}

void jeu() {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;

    Images images;
    Etats etats;
    Fonts fonts;
    ALLEGRO_MOUSE_STATE mouse;
    InformationJeu informationJeu;
    CoutBatiment coutBatiment;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    long long compteur = 0;
    int chrono = 0;
    int nbMaison = 1;
    int nbChateauDeau = 1;
    int nbCentrale = 1;
    long long compteurMaison = 0;
    int xMouse;
    int yMouse;
    int nbCase = 0;
    Case tabCase[NBHAUTEURCASE][NBLARGEURCASE];
    ChateauDeau tabChateauDeau[65] = {0};
    Centrale tabCentrale[65] = {0};


    initialisationCase(tabCase);
    initialiserInfoJeu(&informationJeu);
    initialisationCoutBatiment(&coutBatiment);

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);

    queue = al_create_event_queue();
    timer = al_create_timer(0.1);

    //Images
    if (LARGEUR_FE == 1024) {
        images.menuPrincipal = al_load_bitmap("../Images/menuPrincipal1.png");
        images.staline = al_load_bitmap("../Images/Staline.png");
        images.trump = al_load_bitmap("../Images/Trump.png");
    } else {
        images.menuPrincipal = al_load_bitmap("../Images/menuPrincipal2.png");
        images.trump = al_load_bitmap("../Images/Trump1.png");
        images.staline = al_load_bitmap("../Images/Staline1.png");
    }
    images.map = al_load_bitmap("../Images/map.png");
    images.route1 = al_load_bitmap("../Images/route.png");
    images.route2 = al_load_bitmap("../Images/route2.png");
    images.maison = al_load_bitmap("../Images/maison.png");
    images.roue = al_load_bitmap("../Images/roueDentee.png");
    images.herbe = al_load_bitmap("../Images/herbe.png");
    images.eclair = al_load_bitmap("../Images/éclair.png");
    images.eau = al_load_bitmap("../Images/eau.png");
    images.couches = al_load_bitmap("../Images/couches.png");
    images.boutonCouches = al_load_bitmap("../Images/boutonCouches.png");
    images.usine = al_load_bitmap("../Images/usine.png");
    images.chateau = al_load_bitmap("../Images/chateau.png");
    images.bulldozer = al_load_bitmap("../Images/bulldozer.png");
    images.terrain0 = al_load_bitmap("../Images/terrain vague.png");
    images.terrain1 = al_load_bitmap("../Images/cabane.png");
    images.terrain2 = al_load_bitmap("../Images/maison1.png");
    images.terrain3 = al_load_bitmap("../Images/immeuble.png");
    images.terrain4 = al_load_bitmap("../Images/gratte-ciel.png");
    images.curseur = al_load_bitmap("../Images/curseur.png");
    images.watertower = al_load_bitmap("../Images/watertower.png");
    images.centrale = al_load_bitmap("../Images/centrale.png");

    //Booléens
    etats.fin = 0;
    etats.etatMenuPrincipal = 1;
    etats.etatMode = 1;
    etats.modeCapitaliste = 0;
    etats.modeCommuniste = 0;
    etats.etatEchap = 0;
    etats.couche1 = 1;
    etats.couche2 = 0;
    etats.couche3 = 0;
    etats.etatBoutonReglage = 0;
    etats.etatCouche = 0;
    etats.route = 0;
    etats.etatNoClick = 0;
    etats.curseur = 1;
    etats.habitation = 0;
    etats.eau = 0;
    etats.electricite = 0;
    etats.demolir = 0;

    //Fonts
    fonts.font1 = al_load_ttf_font("../Fonts/font1.ttf", 40, 0);
    fonts.font2 = al_load_ttf_font("../Fonts/font1.ttf", 20, 0);
    fonts.font3 = al_load_ttf_font("../Fonts/font1.ttf", 30, 0);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_position(display, 0, 0);

    al_start_timer(timer);

    while (etats.fin == 0) {
        al_get_mouse_state(&mouse);
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                etats.fin = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        if (!etats.etatMode) {
                            if (etats.etatEchap) {
                                etats.etatEchap = 0;
                            } else {
                                etats.etatEchap = 1;
                            }
                        }
                    }
                        break;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if ((event.mouse.button & 1) == 1) {
                }
                if (etats.etatMenuPrincipal) {
                    choixMenuPrincipal(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatMode) {
                    choixMode(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatEchap) {
                    choixMenuEchap(&etats, event.mouse.x, event.mouse.y);
                } else {
                    choixJeu(&etats, event.mouse.x, event.mouse.y);
                    if (etats.etatBoutonReglage) {
                        choixBoutonOutil(&etats, event.mouse.x, event.mouse.y);
                    }
                    if (etats.couche1 && !etats.etatNoClick) {
                        definirCaseChateauDeau(event, etats.eau, tabCase, &informationJeu, coutBatiment,
                                               &nbChateauDeau);
                        definirCaseCentraleElectrique(event, etats.electricite, tabCase, &informationJeu, coutBatiment,
                                                      &nbCentrale);
                        definirCaseHabitation(event, etats.habitation, tabCase, &nbMaison, &informationJeu, compteur,
                                              &compteurMaison, coutBatiment);
                        demolir(etats.etatBoutonReglage, tabCase, xMouse, yMouse, &informationJeu, etats.demolir);

                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES:
                caseSouris(event, &x1, &x2, &y1, &y2);
                xMouse = event.mouse.x;
                yMouse = event.mouse.y;
                break;
            case ALLEGRO_EVENT_TIMER: {
                if (etats.etatMenuPrincipal) {
                    affichageMenuPrincipal(images, fonts);
                } else if (etats.etatMode) {
                    affichageMode(images, fonts);
                } else if (etats.etatEchap) {
                    afficherMenuEchap(fonts);
                } else {
                    affichageMap(images, etats, fonts, xMouse, yMouse, informationJeu, &compteur, &chrono);
                    if (etats.couche1) {
                        if (etats.etatBoutonReglage) {
                            if ((etats.etatCouche && (xMouse < LARGEUR_FE - 145 && yMouse > HAUTEUR_FE - 105
                                                      && xMouse > LARGEUR_FE - 340 &&
                                                      yMouse < HAUTEUR_FE - 45)) || (xMouse < LARGEUR_FE - 65
                                                                                     &&
                                                                                     yMouse < HAUTEUR_FE - 45 &&
                                                                                     xMouse >
                                                                                     LARGEUR_FE - 275 &&
                                                                                     yMouse >
                                                                                     HAUTEUR_FE - 165)) {
                                etats.etatNoClick = 1;
                            } else {
                                etats.etatNoClick = 0;
                            }
                        } else {
                            etats.etatNoClick = 0;
                        }//Cette fonction sert à ne pas poser de route et d'autres sortes de structure lorsque l'on est dans un menu
                        if (!etats.etatNoClick) {
                            definirCaseRoute(etats.route, tabCase, xMouse, yMouse, mouse.buttons, &informationJeu,
                                             coutBatiment);
                        }
                        ameliorerHabitation(compteur, tabCase, &informationJeu,tabCentrale,tabChateauDeau);
                        afficherRoute(tabCase, images);
                        afficherChateauDeau(tabCase, images);
                        afficherCentraleElectrique(tabCase, images);
                        afficherHabitation(tabCase, images);
                        afficherCaseCurseur(x1, x2, y1, y2, tabCase, images, etats);
                        impotTaxe(&informationJeu, compteur);
                        centraleConnexe(tabCase,&informationJeu,tabCentrale);
                        chateauDeauConnexe(tabCase,&informationJeu,tabChateauDeau);

                    } else if (etats.couche2) {
                        afficherCentraleElectrique(tabCase, images);
                        afficherCapaciteCentrale(tabCase,fonts,tabCentrale);
                    } else if (etats.couche3) {
                        afficherChateauDeau(tabCase, images);
                        afficherCapaciteChateauDeau(tabCase,fonts,tabChateauDeau);
                        afficherHabitation(tabCase,images);
                        afficherHabitationAlimentee(tabCase,fonts);
                    }
                }
                al_flip_display();
                break;
            }

        }


    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}