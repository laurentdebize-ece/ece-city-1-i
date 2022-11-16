#include "affichage.h"

void affichageMap(Images images,Etats etats,Fonts fonts,int x,int y){
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
    al_draw_filled_rectangle(1150,50,1200,100, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(1150,150,1200,200, al_map_rgb(0,0,255));
    al_draw_filled_rectangle(1150,250,1200,300, al_map_rgb(0,255,0));
    al_draw_filled_rectangle(1150,350,1200,400, al_map_rgb(128,0,128));
}

void afficherCompteur(Fonts fonts, long long* compteur, int* chrono){
    *compteur = *compteur + 1;
    if (*compteur%10 ==0){
        *chrono = *chrono + 1;
    }
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),1150,450,0,"Temps: %d",*chrono);
}

void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2) {
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
    if ((event.mouse.x <= XDepart ||
         event.mouse.x >= XDepart + (NBLARGEURCASE * 20)) ||
        (event.mouse.y <= YDepart ||
         event.mouse.y >= YDepart + (NBHAUTEURCASE * 20))) {
        *x1 = 10000;
        *x2 = 10000;
        *y1 = 10000;
        *y2 = 10000;

    }
}

void definirCaseRoute(int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int xMouse,int yMouse,int bouton){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (xMouse >= XDepart + (j * LARGEURCASE) &&
                xMouse <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                yMouse >= YDepart + (i * LARGEURCASE) &&
                yMouse <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if(bouton ==1) {
                    if (route == 1) {
                        tabCase[i][j].routePresente = 1;
                    }
                }else if(bouton==2){
                    if (route == 1) {
                        tabCase[i][j].routePresente = 0;
                    }
                }

            }

        }

    }
}

void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Images images){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1 && tabCase[i][j].batimentPresent==0){
                al_draw_bitmap(images.route1,XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),0);
            }

        }

    }
}
void definirCaseHabitation(ALLEGRO_EVENT event, int habitation, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],int* nbMaison){
    int implementation = 0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (habitation == 1 && (event.mouse.x +LARGEURCASE*2)<= XDepart + LARGEURCASE*NBLARGEURCASE && (event.mouse.y +LARGEURCASE*2)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].routePresente == 0){
                                implementation ++;
                            }
                        }
                    }

                    for (int k =i; k < i+3; k++){
                        for (int l=j ; l < j+3; l++){
                            if (tabCase[k][l].batimentPresent == 0){
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
                            if(implementation == 9*3){
                                tabCase[i][j].construisibilite = 1;
                                tabCase[k][l].habitationPresente = 1;
                                tabCase[k][l].numeroMaison = *nbMaison;
                            }
                        }
                    }
                    if(implementation == 9*3){
                        *nbMaison = *nbMaison + 1;

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

void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    int implementation=0;
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (batiment==1 && (event.mouse.x +LARGEURCASE*3)<= XDepart + LARGEURCASE*NBLARGEURCASE && (event.mouse.y +LARGEURCASE*5)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
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
                            if (tabCase[k][l].batimentPresent == 0){
                                implementation ++;
                            }
                        }
                    }
                    for (int k =i; k < i+6; k++){
                        for (int l=j ; l < j+4; l++){
                            if(implementation == 24*3){
                                tabCase[k][l].batimentPresent = 1;
                            }
                        }
                    }


                }

            }

        }

    }
}


void afficherBatiment(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].batimentPresent == 1 ){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(128,0,128));
            }

        }

    }
}

void afficherCaseCurseur(int x1,int x2,int y1,int y2,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE],Etats etats){
    if  (etats.curseur==1){
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
    }
    if(etats.route==1 ){
        al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(0,0,0));
    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +1; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE +1; l++){
            if (etats.route==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
                al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(255,0,0));
            }
        }
    }

    if (etats.habitation == 1 && (x1 +LARGEURCASE*3)<= XDepart + LARGEURCASE*NBLARGEURCASE && (y1 +LARGEURCASE*3)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(0,255,0));
    } else if (etats.habitation == 1){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(255,0,0));
    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +3; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE+3; l++){
            if (etats.habitation==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
                al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(255,0,0));
            }
        }
    }

    if (etats.batiment == 1 && (x1 +LARGEURCASE*4)<= XDepart + LARGEURCASE*NBLARGEURCASE && (y1 +LARGEURCASE*6)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*3,y2+LARGEURCASE*5, al_map_rgb(128,0,128));
    } else if (etats.batiment == 1){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*3,y2+LARGEURCASE*5, al_map_rgb(255,0,0));
    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +6; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE+4; l++){
            if (etats.batiment==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
                al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*3,y2+LARGEURCASE*5, al_map_rgb(255,0,0));
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

void afficherPremiereCouche(Images images,Fonts fonts){
    al_draw_bitmap(images.map,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Surface");
}

void afficherDeuxiemeCouche(Images images,Fonts fonts){
    al_draw_bitmap(images.couches,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Electricité");
}

void afficherTroisiemeCouche(Images images,Fonts fonts){
    al_draw_bitmap(images.couches,XDepart,YDepart,0);
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),XDepart,0,0,"Eau");
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
            al_draw_bitmap(images.maison, LARGEUR_FE - 260, HAUTEUR_FE - 100, 0);
            al_draw_bitmap(images.chateau, LARGEUR_FE - 130, HAUTEUR_FE - 160, 0);
            al_draw_bitmap(images.usine, LARGEUR_FE - 195, HAUTEUR_FE - 160, 0);
            al_draw_bitmap(images.bulldozer, LARGEUR_FE - 260, HAUTEUR_FE - 160, 0);
            if((x>LARGEUR_FE-195 && x<LARGEUR_FE-145) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
                al_draw_filled_rectangle(x-30,y-20,x+30,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-25,y-20,0,"Route");
            }
            if((x>LARGEUR_FE-260 && x<LARGEUR_FE-210) && (y>HAUTEUR_FE-100 && y<HAUTEUR_FE-50)){
                al_draw_filled_rectangle(x-40,y-20,x+40,y, al_map_rgb(169,169,169));
                al_draw_textf(fonts.font2, al_map_rgb(0,0,0),x-35,y-20,0,"Batiment");
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
        }
    }
    if(!etats->etatCouche) {
        if ((x > LARGEUR_FE - 195 && x < LARGEUR_FE - 145) && (y > HAUTEUR_FE - 100 && y < HAUTEUR_FE - 50)) {
            if (etats->route) {
                etats->route = 0;
            } else {
                etats->route = 1;
            }
            etats->batiment=0;
        }//route
        if ((x > LARGEUR_FE - 260 && x < LARGEUR_FE - 210) && (y > HAUTEUR_FE - 100 && y < HAUTEUR_FE - 50)) {
            if (etats->batiment) {
                etats->batiment = 0;
            } else {
                etats->batiment = 1;
            }
            etats->route=0;
        }//Batiment
    }else{
        choixMenuBoutonCouches(etats,x,y);
    }
}