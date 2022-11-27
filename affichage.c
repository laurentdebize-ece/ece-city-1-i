#include "affichage.h"

void affichageMap(Images images,Etats etats,Fonts fonts,int x,int y,InformationJeu informationJeu,long long *compteur,int *chrono,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    al_clear_to_color(al_map_rgb(255,255,255));
    if(etats.couche1){
        afficherPremiereCouche(images,fonts);
    }else if(etats.couche2){
        afficherDeuxiemeCouche(images,fonts,tabCase,informationJeu);
    }else if(etats.couche3){
        afficherTroisiemeCouche(images,fonts,tabCase,informationJeu);
    }
    if(!etats.etatEchap) {
        afficherCompteur(fonts, compteur, chrono);
    }
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);

        }
    }
    al_draw_bitmap(images.roue,LARGEUR_FE-65,HAUTEUR_FE-100,0);
    if(etats.etatBoutonReglage){
        afficherMenuBoutonOutil(images, &etats,fonts,x,y);
    }
    al_draw_rectangle(LARGEUR_FE-310,YDepart,LARGEUR_FE-10,YDepart+250, al_map_rgb(0,0,0),6);
    al_draw_textf(fonts.font3, al_map_rgb(0,0,0),965,110,0,"ECE-FLOUZ : %d",informationJeu.argent);
    al_draw_textf(fonts.font3, al_map_rgb(0,0,0),965,155,0,"Habitant : %d",informationJeu.habitant);
    al_draw_textf(fonts.font3, al_map_rgb(0,0,0),965,200,0,"Capacite en eau : %d",informationJeu.capaciteEau);
    al_draw_textf(fonts.font3, al_map_rgb(0,0,0),965,245,0,"Capacite electrique: %d",informationJeu.capaciteElectricite);
    afficherModeDeJeu(etats,fonts);


}

void afficherModeDeJeu(Etats etats,Fonts fonts){
    if (etats.modeCapitaliste){
        al_draw_text(fonts.font1, al_map_rgb(0,0,0),XDepart+200,0,0,"Mode de jeu : Capitaliste");
    }
    if (etats.modeCommuniste){
        al_draw_text(fonts.font1, al_map_rgb(0,0,0),XDepart+200,0,0,"Mode de jeu : Communiste");
    }
}

void afficherCompteur(Fonts fonts, long long* compteur, int* chrono){
    *compteur = *compteur + 1;
    if (*compteur%10 ==0){
        *chrono = *chrono + 1;
    }
    al_draw_textf(fonts.font3, al_map_rgb(0,0,0),965,65,0,"TEMPS: %d",*chrono);
}

void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                *x1 = XDepart + (j * LARGEURCASE);
                *x2 = XDepart + LARGEURCASE + (j * LARGEURCASE);
                *y1 = YDepart + (i * LARGEURCASE);
                *y2 = YDepart + LARGEURCASE + (i * LARGEURCASE);

            }

        }

    }
    if ((event.mouse.x <= XDepart  ||
         event.mouse.x >= XDepart + (NBLARGEURCASE * 20)) ||
        (event.mouse.y <= YDepart ||
         event.mouse.y >= YDepart + (NBHAUTEURCASE * 20))) {
        *x1 = 2000;
        *x2 = 2000;
        *y1 = 2000;
        *y2 = 2000;

    }




}

void definirCaseRoute(int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,int bouton,InformationJeu* informationJeu,CoutBatiment coutBatiment) {
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (xMouse >= XDepart + (j * LARGEURCASE) &&
                xMouse <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                yMouse >= YDepart + (i * LARGEURCASE) &&
                yMouse <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (bouton == 1) {
                    if ((route == 1 && tabCase[i][j].routePresente == 0 && tabCase[i][j].habitationPresente == 0 &&
                         tabCase[i][j].chateauDeauPresent == 0 && tabCase[i][j].centraleElectriquePresente == 0) && informationJeu->argent >= 10) {

                        if (tabCase[i+1][j].routePresente == 0 || tabCase[i+1][j].habitationPresente == 0 || tabCase[i+1][j].chateauDeauPresent == 0 && tabCase[i+1][j].centraleElectriquePresente == 0){
                            tabCase[i+1][j].caseConnexeRoute = 1;

                        }

                        if (tabCase[i-1][j].routePresente == 0 || tabCase[i-1][j].habitationPresente == 0 || tabCase[i-1][j].chateauDeauPresent == 0 && tabCase[i-1][j].centraleElectriquePresente == 0){
                            tabCase[i-1][j].caseConnexeRoute = 1;

                        }

                        if (tabCase[i][j+1].routePresente == 0 || tabCase[i][j+1].habitationPresente == 0 || tabCase[i][j+1].chateauDeauPresent == 0 && tabCase[i][j+1].centraleElectriquePresente == 0){
                            tabCase[i][j+1].caseConnexeRoute = 1;

                        }
                        if (tabCase[i][j-1].routePresente == 0 || tabCase[i][j-1].habitationPresente == 0 || tabCase[i][j-1].chateauDeauPresent == 0 && tabCase[i][j-1].centraleElectriquePresente == 0){
                            tabCase[i][j-1].caseConnexeRoute = 1;

                        }

                        tabCase[i][j].routePresente = 1;
                        tabCase[i][j].caseConnexeRoute = 0;
                        informationJeu->argent -= coutBatiment.route;


                    }
                } else if (bouton == 2) {
                    if (route == 1) {
                        tabCase[i][j].routePresente = 0;
                    }

                }

            }

        }
    }
}

void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], Images images) {
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1) {
                al_draw_bitmap(images.route1, XDepart + (j * LARGEURCASE), YDepart + (i * LARGEURCASE), 0);
            }

        }

    }
}

void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], int *nbMaison,
                      InformationJeu *informationJeu, long long compteur, long long *compteurMaison,
                      CoutBatiment coutBatiment) {
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((habitation == 1 && (event.mouse.x + LARGEURCASE * 2) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
                     (event.mouse.y + LARGEURCASE * 2) <= YDepart + LARGEURCASE * NBHAUTEURCASE) &&
                    informationJeu->argent >= coutBatiment.maison)
                {
                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (tabCase[k][l].routePresente == 0) {
                                implementation++;
                            }
                        }
                    }

                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (tabCase[k][l].chateauDeauPresent == 0) {
                                implementation++;
                            }
                        }
                    }

                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (tabCase[k][l].habitationPresente == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (tabCase[k][l].centraleElectriquePresente == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            if (implementation == 9 * 4) {
                                tabCase[i][j].construisibilite = 1;
                                tabCase[k][l].habitationPresente = 1;
                                tabCase[k][l].numeroMaison = *nbMaison;
                            }
                        }
                    }
                    if (implementation == 9 * 4) {
                        *nbMaison = *nbMaison + 1;
                        informationJeu->argent -= coutBatiment.maison;
                        *compteurMaison = compteur;
                    }


                }

            }

        }

    }
}


void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 0 && (tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison)){
                al_draw_bitmap(images.terrain0,XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE),0);
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 1 && tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison){
                al_draw_bitmap(images.terrain1,XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE),0);
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 2 && tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison){
                al_draw_bitmap(images.terrain2,XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE),0);
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 3 && tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison){
                al_draw_bitmap(images.terrain3,XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE),0);
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 4 && tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison){
                al_draw_bitmap(images.terrain4,XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE)-109,0);
            }

        }

    }
}

void definirCaseChateauDeau(ALLEGRO_EVENT event, int eau, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu,CoutBatiment coutBatiment,int* nbChateauDeau){
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((eau == 1 && (event.mouse.x + LARGEURCASE * 3) <= XDepart + LARGEURCASE * NBLARGEURCASE && (event.mouse.y + LARGEURCASE * 5) <= YDepart + LARGEURCASE * NBHAUTEURCASE) && informationJeu->argent >= 100000){
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if (tabCase[k][l].routePresente == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if (tabCase[k][l].habitationPresente == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if (tabCase[k][l].chateauDeauPresent == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if (tabCase[k][l].centraleElectriquePresente == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if(implementation == 24*4){
                                tabCase[i][j].construisibilite = 1;
                                tabCase[k][l].chateauDeauPresent = 1;
                                tabCase[k][l].numeroChateauDeau = *nbChateauDeau;

                            }
                        }
                    }
                    if (implementation == 24*4){
                        *nbChateauDeau = *nbChateauDeau + 1;
                        informationJeu->argent -= coutBatiment.chateauDeau;
                    }


                }

            }

        }

    }
}


void afficherChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].chateauDeauPresent == 1 && tabCase[i][j].numeroChateauDeau==tabCase[i+5][j+3].numeroChateauDeau){
                al_draw_bitmap(images.watertower,XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),0);
            }
        }
    }
}

void afficherCapaciteChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Fonts fonts,ChateauDeau tabChateauDeau[65]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].chateauDeauPresent == 1 && tabCase[i][j].construisibilite){
                al_draw_textf(fonts.font2, al_map_rgb(255,255,255),XDepart + j*LARGEURCASE - 85,YDepart + i*LARGEURCASE + LARGEURCASE*6,0,"Capacite chateau %d : %d / 5000",tabCase[i][j].numeroChateauDeau,tabChateauDeau[tabCase[i][j].numeroChateauDeau].capaciteDuChateauDeau);

            }
        }
    }
}

void afficherHabitationAlimentee(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Fonts fonts){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].construisibilite == 1 && tabCase[i][j].niveauBatiment>=1) {
                al_draw_textf(fonts.font2, al_map_rgb(255,255,255),XDepart + j*LARGEURCASE -90,YDepart + i*LARGEURCASE + LARGEURCASE*3,0,"Habitation alimenté a par le chateau %d",tabCase[i][j].chateauDeauQuiAlimente);
            }

        }

    }
}


void definirCaseCentraleElectrique(ALLEGRO_EVENT event, int electricite, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu,CoutBatiment coutBatiment,int* nbCentrale) {
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((electricite == 1 && (event.mouse.x + LARGEURCASE * 3) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
                     (event.mouse.y + LARGEURCASE * 5) <= YDepart + LARGEURCASE * NBHAUTEURCASE) &&
                    informationJeu->argent >= 100000) {
                    for (int k = i; k < i + 6; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (tabCase[k][l].routePresente == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 6; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (tabCase[k][l].habitationPresente == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 6; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (tabCase[k][l].chateauDeauPresent == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 6; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (tabCase[k][l].centraleElectriquePresente == 0) {
                                implementation++;
                            }
                        }
                    }
                    for (int k = i; k < i + 6; k++) {
                        for (int l = j; l < j + 4; l++) {
                            if (implementation == 24 * 4) {
                                tabCase[i][j].construisibilite = 1;
                                tabCase[k][l].centraleElectriquePresente = 1;
                                tabCase[k][l].numeroCentrale = *nbCentrale;

                            }
                        }
                    }
                    if (implementation == 24 * 4) {
                        *nbCentrale = *nbCentrale +1;
                        informationJeu->argent -= coutBatiment.centraleElectrique;

                    }




                }

            }

        }

    }
}


void afficherCentraleElectrique(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].centraleElectriquePresente == 1 && tabCase[i][j].numeroCentrale==tabCase[i+5][j+3].numeroCentrale){
                al_draw_bitmap(images.centrale,XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),0);
            }
        }
    }
}

void afficherCapaciteCentrale(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Fonts fonts,Centrale tabCentrale[65]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].centraleElectriquePresente == 1 && tabCase[i][j].construisibilite){
                al_draw_textf(fonts.font2, al_map_rgb(255,255,0),XDepart + j*LARGEURCASE - 85,YDepart + i*LARGEURCASE + LARGEURCASE*6,0,"Capacite centrale %d : %d / 5000",tabCase[i][j].numeroCentrale,tabCentrale[tabCase[i][j].numeroCentrale].capaciteDeLaCentrale);

            }
        }
    }
}

void afficherCaseCurseur(int x1,int x2,int y1,int y2,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images,Etats etats){
    if  (etats.curseur==1){
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
    }
    if(etats.route==1 ){
        al_draw_bitmap(images.route1,x1,y1,0);
    }
    if (etats.demolir==1){
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0));

    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 1; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 1; l++) {
            if (etats.route == 1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                               tabCase[k][l].chateauDeauPresent == 1 ||
                               tabCase[k][l].centraleElectriquePresente == 1)) {
                al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgba(255, 0, 0,1));
            }
        }
    }

    if (etats.habitation == 1 && (x1 +LARGEURCASE*3)<= XDepart + LARGEURCASE*NBLARGEURCASE && (y1 +LARGEURCASE*3)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(0,255,0));
    } else if (etats.habitation == 1){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(255,0,0));
    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 3; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 3; l++) {
            if (etats.habitation == 1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                                    tabCase[k][l].chateauDeauPresent == 1 ||
                                    tabCase[k][l].centraleElectriquePresente == 1)) {
                al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 2, y2 + LARGEURCASE * 2, al_map_rgb(255, 0, 0));
            }
        }
    }

    if (etats.eau == 1 && (x1 + LARGEURCASE * 4) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
        (y1 + LARGEURCASE * 6) <= YDepart + LARGEURCASE * NBHAUTEURCASE) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(0, 0, 200));
    } else if (etats.eau == 1) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));

    }

    if (etats.electricite == 1 && (x1 + LARGEURCASE * 4) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
        (y1 + LARGEURCASE * 6) <= YDepart + LARGEURCASE * NBHAUTEURCASE) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 255, 0));
    } else if (etats.electricite == 1) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));

    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 6; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 4; l++) {
            if ((etats.eau == 1 || etats.electricite == 1) && ((tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                  tabCase[k][l].chateauDeauPresent == 1 || tabCase[k][l].centraleElectriquePresente == 1))) {
                al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));
            }
        }
    }


}




void affichageMenuPrincipal(Images images,Fonts fonts,int x,int y){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(images.menuPrincipal,0,0,0);
    al_draw_filled_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-180, al_map_rgb(123, 165, 248));
    al_draw_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-180, al_map_rgb(0,0,0),1);
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/2 -70,HAUTEUR_FE-165,0,"Continuer");
    al_draw_filled_rectangle(0,HAUTEUR_FE-50,150,HAUTEUR_FE, al_map_rgb(0,0,0));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),25,HAUTEUR_FE-45,0,"Quitter");
    al_draw_filled_rectangle(LARGEUR_FE/2 +75,HAUTEUR_FE-100,LARGEUR_FE/2 +145,HAUTEUR_FE-180, al_map_rgb(123, 165, 248));
    al_draw_rectangle(LARGEUR_FE/2 +75,HAUTEUR_FE-100,LARGEUR_FE/2 +145,HAUTEUR_FE-180, al_map_rgb(0,0,0),1);
    al_draw_bitmap(images.sauvegarde,LARGEUR_FE/2 +80,HAUTEUR_FE-175,0);
    if((x>LARGEUR_FE/2 +75 && x<LARGEUR_FE/2 +145) && (y>HAUTEUR_FE-180 && y<HAUTEUR_FE-100)){
        al_draw_filled_rectangle(x-85,y,x+85,y+40, al_map_rgb(169,169,169));
        al_draw_textf(fonts.font3, al_map_rgb(0,0,0),x-80,y+5,0,"Charger Partie");

    }
}


void choixMenuPrincipal(Etats *etats,int x,int y,InformationJeu* informationJeu,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    if((x>LARGEUR_FE/2 -75 && x<LARGEUR_FE/2 +75) && (y>HAUTEUR_FE-180 && y<HAUTEUR_FE-100)){
        etats->etatMenuPrincipal=0;
    }
    if((x>0 && x<150) && (y>HAUTEUR_FE-50 && y<HAUTEUR_FE)){
        etats->fin=1;
    }
    if((x>LARGEUR_FE/2 +75 && x<LARGEUR_FE/2 +145) && (y>HAUTEUR_FE-180 && y<HAUTEUR_FE-100)){
        *informationJeu = lire_information_Joueur(*informationJeu);
        liresauvegardeDuplateau(tabCase);
        etats->choixSauv=1;
        etats->etatMenuPrincipal=0;
        etats->etatMode=0;
    }
}

void affichageMode(Images images,Fonts fonts){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(images.staline,LARGEUR_FE/2,0,0);
    al_draw_bitmap(images.trump,0,0,0);
    al_draw_filled_rectangle(0,HAUTEUR_FE-50,150,HAUTEUR_FE, al_map_rgb(255,255,255));
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),25,HAUTEUR_FE-45,0,"Retour");
}

void choixMode(Etats *etats,int x,int y){
    if(((x>0 && x<LARGEUR_FE/2)&&(y>0 && y<HAUTEUR_FE-50)) || ((x>150 && x<LARGEUR_FE/2) && (y>0 && y<HAUTEUR_FE))){
        etats->modeCapitaliste=1;
        etats->etatMode=0;
    }
    if((x>LARGEUR_FE/2 && x<LARGEUR_FE)&&(y>0 && y<HAUTEUR_FE)){
        etats->modeCommuniste=1;
        etats->etatMode=0;
    }
    if((x>0 && x<150) && (y>HAUTEUR_FE-50 && y<HAUTEUR_FE)){
        etats->etatMenuPrincipal=1;
    }
}

void afficherMenuEchap(Fonts fonts){
    al_draw_filled_rectangle(LARGEUR_FE/2 -200,HAUTEUR_FE/2 -200,LARGEUR_FE/2 +200,HAUTEUR_FE/2 +200, al_map_rgb(169,169,169));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/2 -50,HAUTEUR_FE/2 -175,0,"Pause");
    al_draw_filled_rectangle(LARGEUR_FE/2 -100,HAUTEUR_FE/2 -100,LARGEUR_FE/2 +100,HAUTEUR_FE/2, al_map_rgb(0,0,0));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/2 -70,HAUTEUR_FE/2 -75,0,"Continuer");
    al_draw_filled_rectangle(LARGEUR_FE/2 -100,HAUTEUR_FE/2 +25,LARGEUR_FE/2 +100,HAUTEUR_FE/2 +125, al_map_rgb(0,0,0));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/2 -50,HAUTEUR_FE/2 +50,0,"Quitter");
}

void choixMenuEchap(Etats *etats,int x, int y){
    if((x>LARGEUR_FE/2 -100 && x<LARGEUR_FE/2 +100)&&(y>HAUTEUR_FE/2 -100 && y<HAUTEUR_FE/2)){
        etats->etatEchap=0;
    }
    if((x>LARGEUR_FE/2 -100 && x<LARGEUR_FE/2 +100)&&(y>HAUTEUR_FE/2 +25 && y<HAUTEUR_FE/2 +125)){
        etats->fin=1;
    }
}

void afficherPremiereCouche(Images images,Fonts fonts){
    al_draw_bitmap(images.map,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Surface");
}

void afficherDeuxiemeCouche(Images images,Fonts fonts,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu informationJeu){
    al_draw_bitmap(images.couches,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Electricité");
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1 && informationJeu.capaciteElectricite>0){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + (j * LARGEURCASE)+LARGEURCASE,YDepart + (i * LARGEURCASE)+LARGEURCASE,
                                         al_map_rgb(154,205,50));
            }
        }
    }
}

void afficherTroisiemeCouche(Images images,Fonts fonts,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu informationJeu){
    al_draw_bitmap(images.couches,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Eau");
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente && informationJeu.capaciteEau>0){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + (j * LARGEURCASE)+LARGEURCASE,YDepart + (i * LARGEURCASE)+LARGEURCASE,
                                         al_map_rgb(95,158,160));
            }
            if(tabCase[i][j].habitationPresente && tabCase[i][j].numeroMaison==tabCase[i+2][j+2].numeroMaison){
                al_draw_rectangle(XDepart+(j*LARGEURCASE),YDepart+(i*LARGEURCASE),XDepart+(j*LARGEURCASE)+3*LARGEURCASE,YDepart+(i*LARGEURCASE)+3*LARGEURCASE,
                                  al_map_rgb(0,0,0),5);
            }
        }
    }
}

void afficherMenuBoutonOutil(Images images,Etats *etats,Fonts fonts,int x,int y){
    al_draw_filled_rectangle(LARGEUR_FE-65,HAUTEUR_FE-105,LARGEUR_FE-145,HAUTEUR_FE-45, al_map_rgb(169,169,169));
    al_draw_bitmap(images.boutonCouches,LARGEUR_FE-130,HAUTEUR_FE-100,0);
    if(!etats->etatCouche) {
        if (etats->couche1) {
            al_draw_filled_rectangle(LARGEUR_FE - 65, HAUTEUR_FE - 105, LARGEUR_FE - 275, HAUTEUR_FE - 165,
                                     al_map_rgb(169, 169, 169));
            al_draw_filled_rectangle(LARGEUR_FE - 145, HAUTEUR_FE - 105, LARGEUR_FE - 275, HAUTEUR_FE - 45,
                                     al_map_rgb(169, 169, 169));
            al_draw_bitmap(images.route2, LARGEUR_FE - 195, HAUTEUR_FE - 100, 0);
            al_draw_filled_rectangle(LARGEUR_FE-275,HAUTEUR_FE-230,LARGEUR_FE-65,HAUTEUR_FE-115, al_map_rgb(169,169,169));
            if(etats->route){
                al_draw_filled_rectangle(LARGEUR_FE-195,HAUTEUR_FE-100,LARGEUR_FE-145,HAUTEUR_FE-50, al_map_rgba(169,169,169,200));
            }
            al_draw_bitmap(images.maison, LARGEUR_FE - 260, HAUTEUR_FE - 100, 0);
            if(etats->habitation){
                al_draw_filled_rectangle(LARGEUR_FE-260,HAUTEUR_FE-100,LARGEUR_FE-210,HAUTEUR_FE-50, al_map_rgba(169,169,169,200));
            }
            al_draw_bitmap(images.chateau, LARGEUR_FE - 130, HAUTEUR_FE - 160, 0);
            if(etats->eau){
                al_draw_filled_rectangle(LARGEUR_FE-130,HAUTEUR_FE-160,LARGEUR_FE-80,HAUTEUR_FE-110, al_map_rgba(169,169,169,200));
            }
            al_draw_bitmap(images.usine, LARGEUR_FE - 195, HAUTEUR_FE - 160, 0);
            if(etats->electricite){
                al_draw_filled_rectangle(LARGEUR_FE-195,HAUTEUR_FE-160,LARGEUR_FE-145,HAUTEUR_FE-110, al_map_rgba(169,169,169,200));
            }
            al_draw_bitmap(images.bulldozer, LARGEUR_FE - 260, HAUTEUR_FE - 160, 0);
            if(etats->demolir){
                al_draw_filled_rectangle(LARGEUR_FE-260,HAUTEUR_FE-160,LARGEUR_FE-210,HAUTEUR_FE-110, al_map_rgba(169,169,169,200));
            }
            al_draw_bitmap(images.curseur, LARGEUR_FE - 260, HAUTEUR_FE - 220, 0);

            if (etats->curseur){
                al_draw_filled_rectangle(LARGEUR_FE-260,HAUTEUR_FE-220,LARGEUR_FE-210,HAUTEUR_FE-170, al_map_rgba(169,169,169,200));
            }

            if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
                al_draw_filled_rectangle(x-30,y-20,x+30,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-25,y-20,0,"Route");
            }
            if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
                al_draw_filled_rectangle(x-40,y-20,x+40,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-35,y-20,0,"Habitation");
            }
            if((x>LARGEUR_FE-130 && x<LARGEUR_FE-80) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
                al_draw_filled_rectangle(x-60,y-20,x+60,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-55,y-20,0,"Chateau d'eau");
            }
            if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
                al_draw_filled_rectangle(x-27,y-20,x+27,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-22,y-20,0,"Usine");
            }
            if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
                al_draw_filled_rectangle(x-35,y-20,x+35,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-30,y-20,0,"Demolir");
            }
            if ((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-220 && y<HAUTEUR_FE-170)){
                al_draw_filled_rectangle(x-35,y-19,x+35,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-30,y-20,0,"Curseur");

            }
        }
    } else{
        al_draw_filled_rectangle(LARGEUR_FE - 145, HAUTEUR_FE - 105, LARGEUR_FE - 340, HAUTEUR_FE - 45,
                                 al_map_rgb(169, 169, 169));
        al_draw_bitmap(images.herbe,LARGEUR_FE-195,HAUTEUR_FE-100,0);
        al_draw_bitmap(images.eclair,LARGEUR_FE-260,HAUTEUR_FE-100,0);
        al_draw_bitmap(images.eau,LARGEUR_FE-325,HAUTEUR_FE-100,0);
        if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
            al_draw_filled_rectangle(x-35,y-20,x+35,y, al_map_rgb(169,169,169));
            al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-30,y-20,0,"Surface");
        }
        if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
            al_draw_filled_rectangle(x-45,y-20,x+45,y, al_map_rgb(169,169,169));
            al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-40,y-20,0,"Electricité");
        }
        if((x>LARGEUR_FE-325 && x<LARGEUR_FE-275) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
            al_draw_filled_rectangle(x-25,y-20,x+25,y, al_map_rgb(169,169,169));
            al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-20,y-20,0,"Eau");
        }
    }
    if((x>LARGEUR_FE-130 && x<LARGEUR_FE-80) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
        al_draw_filled_rectangle(x-35,y-20,x+35,y, al_map_rgb(169,169,169));
        al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-30,y-20,0,"Couches");
    }
}

void choixJeu(Etats *etats,int x,int y){
    if((x>LARGEUR_FE-65 && x<LARGEUR_FE-15)&&(y>HAUTEUR_FE-100 && y<HAUTEUR_FE-40)){
        if(etats->etatBoutonReglage){
            etats->etatBoutonReglage=0;
            etats->etatCouche=0;
        }else {
            etats->etatBoutonReglage=1;
        }
    }
}

void choixMenuBoutonCouches(Etats *etats,int x,int y){
    if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
        etats->couche3=0;
        etats->couche1=1;
        etats->couche2=0;
    }//Surface
    if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
        etats->couche3=0;
        etats->couche1=0;
        etats->couche2=1;
    }//Electricité
    if((x>LARGEUR_FE-325 && x<LARGEUR_FE-275) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
        etats->couche3=1;
        etats->couche1=0;
        etats->couche2=0;
    }//Eau
}

void choixBoutonOutil(Etats *etats,int x,int y){
    if((x>LARGEUR_FE-130 && x<LARGEUR_FE-80) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
        if(etats->etatCouche) {
            etats->etatCouche = 0;
        }else{
            etats->etatCouche=1;
        }//Bouton couche
        etats->habitation=0;
        etats->eau=0;
        etats->electricite=0;
        etats->demolir=0;
        etats->curseur = 0;
        etats->route=0;
    }
    if(!etats->etatCouche) {
        if ((x > LARGEUR_FE - 195 && x < LARGEUR_FE - 145) && (y > HAUTEUR_FE - 100 && y < HAUTEUR_FE - 50)) {
            if (etats->route) {
                etats->route = 0;
            } else {
                etats->route = 1;
            }
            etats->habitation=0;
            etats->eau=0;
            etats->electricite=0;
            etats->demolir=0;
            etats->curseur = 0;

        }//route
        if ((x > LARGEUR_FE - 260 && x < LARGEUR_FE - 210) && (y > HAUTEUR_FE - 100 && y < HAUTEUR_FE - 50)) {
            if (etats->habitation) {
                etats->habitation = 0;
            } else {
                etats->habitation = 1;
            }
            etats->route=0;
            etats->eau=0;
            etats->electricite=0;
            etats->demolir=0;
            etats->curseur = 0;

        }//Habitation
        if((x>LARGEUR_FE-130 && x<LARGEUR_FE-80) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
            if (etats->eau) {
                etats->eau = 0;
            } else {
                etats->eau = 1;
            }
            etats->habitation=0;
            etats->electricite=0;
            etats->demolir=0;
            etats->route=0;
            etats->curseur = 0;
        }//Chateau d'eau
        if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
            if (etats->electricite) {
                etats->electricite = 0;
            } else {
                etats->electricite = 1;
            }
            etats->habitation=0;
            etats->eau=0;
            etats->demolir=0;
            etats->route=0;
            etats->curseur = 0;

        }//Usine
        if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-160 && y<HAUTEUR_FE-110)){
            if(etats->demolir){
                etats->demolir=0;
            } else{
                etats->demolir=1;
            }
            etats->habitation=0;
            etats->eau=0;
            etats->electricite=0;
            etats->route=0;
            etats->curseur = 0;

        }//Demolir
        if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-220 && y<HAUTEUR_FE-170)){
            if(etats->curseur){
                etats->curseur=0;
            } else{
                etats->curseur=1;
            }
            etats->habitation=0;
            etats->eau=0;
            etats->electricite=0;
            etats->route=0;
            etats->demolir = 0;

        }//curseur
    }else{
        choixMenuBoutonCouches(etats,x,y);
    }
}

void demolir(int bouton,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,InformationJeu* informationJeu,int demolir){
    CoutBatiment cout;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (xMouse >= XDepart + (j * LARGEURCASE) &&
                xMouse <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                yMouse >= YDepart + (i * LARGEURCASE) &&
                yMouse <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (bouton == 1) {
                    if (demolir == 1){
                        if(tabCase[i][j].routePresente){
                            tabCase[i][j].routePresente = 0;
                            informationJeu->argent += 10;
                        }
                        if(tabCase[i][j].habitationPresente){
                            for (int k = 0; k < NBHAUTEURCASE; k++) {
                                for (int l = 0; l < NBLARGEURCASE; l++) {
                                    if (tabCase[k][l].numeroMaison == tabCase[i][j].numeroMaison){
                                        tabCase[k][l].habitationPresente = 0;
                                    }
                                    if (tabCase[k][l].niveauBatiment == 1 && tabCase[k][l].construisibilite){
                                        informationJeu->habitant -= 10;
                                    }
                                    if (tabCase[k][l].niveauBatiment == 2 && tabCase[k][l].construisibilite){
                                        informationJeu->habitant -= 40;
                                    }
                                    if (tabCase[k][l].niveauBatiment == 3 && tabCase[k][l].construisibilite){
                                        informationJeu->habitant -= 50;
                                    }if (tabCase[k][l].niveauBatiment == 4 && tabCase[k][l].construisibilite){
                                        informationJeu->habitant -= 900;
                                    }

                                }
                            }
                            informationJeu->argent += 1000;

                        }
                        if(tabCase[i][j].centraleElectriquePresente){

                            for (int k = 0; k < NBHAUTEURCASE; k++) {
                                for (int l = 0; l < NBLARGEURCASE; l++) {
                                    if (tabCase[k][l].numeroCentrale == tabCase[i][j].numeroCentrale){
                                        tabCase[k][l].centraleElectriquePresente = 0;
                                    }
                                }
                            }

                            informationJeu->argent += cout.centraleElectrique;
                        }
                        if(tabCase[i][j].chateauDeauPresent){
                            for (int k = 0; k < NBHAUTEURCASE; k++) {
                                for (int l = 0; l < NBLARGEURCASE; l++) {
                                    if (tabCase[k][l].numeroChateauDeau == tabCase[i][j].numeroChateauDeau){
                                        tabCase[k][l].chateauDeauPresent = 0;
                                    }
                                }
                            }

                            informationJeu->argent += cout.chateauDeau;
                        }
                    }
                }
            }
        }
    }
}