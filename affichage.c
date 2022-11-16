#include "affichage.h"

void affichageMap(Fonts fonts,InformationJeu informationJeu,Images images){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(images.map,XDepart,YDepart,0);
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);

        }
    }
    al_draw_filled_rectangle(1150,50,1200,100, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(1150,150,1200,200, al_map_rgb(0,0,255));
    al_draw_filled_rectangle(1150,250,1200,300, al_map_rgb(0,255,0));
    al_draw_filled_rectangle(1150,350,1200,400, al_map_rgb(0,0,200));
    al_draw_filled_rectangle(1250,350,1300,400, al_map_rgb(255,255,0));
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),1150,500,0,"Argent : %d",informationJeu.argent);

}



void afficherCompteur(Fonts fonts, long long * compteur, int* chrono){
    *compteur = *compteur + 1;
    if (*compteur%10 ==0){
        *chrono = *chrono + 1;
    }
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),1150,450,0,"Temps: %d",*chrono);
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
        (event.mouse.y <= YDepart  ||
         event.mouse.y >= YDepart + (NBHAUTEURCASE * 20) )){
        *x1 = 10000;
        *x2 = 10000;
        *y1 = 10000;
        *y2 = 10000;

    }




}

void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],InformationJeu* informationJeu){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((route==1 && tabCase[i][j].routePresente == 0 && tabCase[i][j].habitationPresente == 0 && tabCase[i][j].chateauDeauPresent == 0) && informationJeu->argent >= 10){
                    tabCase[i][j].routePresente = 1;
                    tabCase[i][j].construisibilite = 0;
                    informationJeu->argent -= 10;
                }

            }

        }

    }
}

void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1){
                al_draw_bitmap(images.route1,XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),0);
            }

        }

    }
}

void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison,InformationJeu* informationJeu, long long compteur, long long* compteurMaison){
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((habitation == 1 && (event.mouse.x +LARGEURCASE*2)<= XDepart + LARGEURCASE*NBLARGEURCASE && (event.mouse.y +LARGEURCASE*2)<= YDepart + LARGEURCASE*NBHAUTEURCASE) && informationJeu->argent >= 1000) {
                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].routePresente == 0){
                                implementation ++;
                            }
                        }
                    }

                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].chateauDeauPresent == 0){
                                implementation ++;
                            }
                        }
                    }

                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].habitationPresente == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].centraleElectriquePresente == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if(implementation == 9*4){
                                tabCase[i][j].construisibilite = 1;
                                tabCase[k][l].habitationPresente = 1;
                                tabCase[k][l].numeroMaison = *nbMaison;
                            }
                        }
                    }
                    if(implementation == 9*4){
                        *nbMaison = *nbMaison + 1;
                        informationJeu->argent -= 1000;
                        *compteurMaison = compteur;
                    }


                }

            }

        }

    }
}


void afficherHabitation(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 0){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,255,0));
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 1){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,255));
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 2){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,100));
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 3){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,0));
            }else if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].niveauBatiment== 4){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(128,128,128));
            }

        }

    }
}

void definirCaseChateauDeau(ALLEGRO_EVENT event, int eau, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu){
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
                                tabCase[k][l].chateauDeauPresent = 1;
                            }
                        }
                    }
                    if (implementation == 24*4){
                        informationJeu->argent -= 100000;
                    }


                }

            }

        }

    }
}


void afficherChateauDeau(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].chateauDeauPresent == 1 ){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,200));
            }
        }
    }
}

void definirCaseCentraleElectrique(ALLEGRO_EVENT event, int electricite, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], InformationJeu* informationJeu){
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if ((electricite == 1 && (event.mouse.x + LARGEURCASE * 3) <= XDepart + LARGEURCASE * NBLARGEURCASE && (event.mouse.y + LARGEURCASE * 5) <= YDepart + LARGEURCASE * NBHAUTEURCASE) && informationJeu->argent >= 100000){
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
                                tabCase[k][l].centraleElectriquePresente = 1;
                            }
                        }
                    }
                    if (implementation == 24*4){
                        informationJeu->argent -= 100000;
                    }


                }

            }

        }

    }
}


void afficherCentraleElectrique(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].centraleElectriquePresente == 1 ){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(255,255,0));
            }
        }
    }
}

void afficherCaseCurseur(int x1, int x2, int y1, int y2, int curseur, int route, int habitation, int eau,
                         Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], Images images, int electricite) {
    if (curseur == 1) {
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
    }
    if (route == 1) {
        al_draw_bitmap(images.route1, x1, y1, 0);
    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 1; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 1; l++) {
            if (route == 1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                               tabCase[k][l].chateauDeauPresent == 1 ||
                               tabCase[k][l].centraleElectriquePresente == 1)) {
                al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0));
            }
        }
    }

    if (habitation == 1 && (x1 + LARGEURCASE * 3) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
        (y1 + LARGEURCASE * 3) <= YDepart + LARGEURCASE * NBHAUTEURCASE) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 2, y2 + LARGEURCASE * 2, al_map_rgb(0, 255, 0));
    } else if (habitation == 1) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 2, y2 + LARGEURCASE * 2, al_map_rgb(255, 0, 0));
    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 3; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 3; l++) {
            if (habitation == 1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                                    tabCase[k][l].chateauDeauPresent == 1 ||
                                    tabCase[k][l].centraleElectriquePresente == 1)) {
                al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 2, y2 + LARGEURCASE * 2, al_map_rgb(255, 0, 0));
            }
        }
    }

    if (eau == 1 && (x1 + LARGEURCASE * 4) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
        (y1 + LARGEURCASE * 6) <= YDepart + LARGEURCASE * NBHAUTEURCASE) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(0, 0, 200));
    } else if (eau == 1) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));

    }

    if (electricite == 1 && (x1 + LARGEURCASE * 4) <= XDepart + LARGEURCASE * NBLARGEURCASE &&
        (y1 + LARGEURCASE * 6) <= YDepart + LARGEURCASE * NBHAUTEURCASE) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 255, 0));
    } else if (electricite == 1) {
        al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));

    }

    for (int k = (y1 - YDepart) / LARGEURCASE; k < (y1 - YDepart) / LARGEURCASE + 6; k++) {
        for (int l = (x1 - XDepart) / LARGEURCASE; l < (x1 - XDepart) / LARGEURCASE + 4; l++) {
            if ((eau == 1 || electricite == 1) &&
                (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente == 1 ||
                 tabCase[k][l].chateauDeauPresent == 1 || tabCase[k][l].centraleElectriquePresente == 1)) {
                al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 3, y2 + LARGEURCASE * 5, al_map_rgb(255, 0, 0));
            }
        }
    }


}



void affichageMenuPrincipal(Images images,Fonts fonts){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(images.menuPrincipal,0,0,0);
    al_draw_filled_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(123, 165, 248));
    al_draw_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(0,0,0),1);
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/2 -70,HAUTEUR_FE-165,0,"Continuer");
    al_draw_filled_rectangle(0,HAUTEUR_FE-50,150,HAUTEUR_FE, al_map_rgb(0,0,0));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),25,HAUTEUR_FE-45,0,"Quitter");
}


void choixMenuPrincipal(Etats *etats,int x,int y){
    if((x>LARGEUR_FE/2 -75 && x<LARGEUR_FE/2 +75) && (y>HAUTEUR_FE-175 && y<HAUTEUR_FE-100)){
        etats->etatMenuPrincipal=0;
    }
    if((x>0 && x<150) && (y>HAUTEUR_FE-50 && y<HAUTEUR_FE)){
        etats->fin=1;
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

void afficherDetailsConstruction(Fonts fonts,int x,int y){
    if ((x > LARGEUR_FE-65 && x < LARGEUR_FE-15) && (y > 50 && y < 100)) {
        al_draw_filled_rectangle(x-30,y-20,x+30,y, al_map_rgb(169,169,169));
        al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-25,y-20,0,"Routes");
    }
    if ((x >LARGEUR_FE-65 && x<LARGEUR_FE-15) && (y >250 && y <300)) {
        al_draw_filled_rectangle(x-30,y-20,x+30,y, al_map_rgb(169,169,169));
        al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-25,y-20,0,"Cabane");
    }
}