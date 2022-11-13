#include "affichage.h"

void affichageMap(Fonts fonts){
    al_clear_to_color(al_map_rgb(255,255,255));
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);

        }
    }
    al_draw_filled_rectangle(1150,50,1200,100, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(1150,150,1200,200, al_map_rgb(0,0,255));
    al_draw_filled_rectangle(1150,250,1200,300, al_map_rgb(0,255,0));
    al_draw_filled_rectangle(1150,350,1200,400, al_map_rgb(128,0,128));
}

void afficherCompteur(Fonts fonts, int* compteur, int* chrono){
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

void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (route==1 && tabCase[i][j].routePresente == 0 && tabCase[i][j].habitationPresente == 0 && tabCase[i][j].batimentPresent == 0){
                    tabCase[i][j].routePresente = 1;
                    tabCase[i][j].construisibilite = 0;
                }
            }

        }

    }
}

void afficherRoute(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE),YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,0));
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
    int implementation = 0;
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

void afficherCaseCurseur(int x1,int x2,int y1,int y2, int curseur, int route, int habitation, int batiment,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    if  (curseur==1){
        al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
    }
    if(route==1 ){
        al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(0,0,0));
    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +1; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE +1; l++){
            if (route==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
                al_draw_filled_rectangle(x1,y1,x2,y2, al_map_rgb(255,0,0));
            }
        }
    }

    if (habitation == 1 && (x1 +LARGEURCASE*3)<= XDepart + LARGEURCASE*NBLARGEURCASE && (y1 +LARGEURCASE*3)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(0,255,0));
    } else if (habitation == 1){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(255,0,0));
    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +3; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE+3; l++){
            if (habitation==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
                al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*2,y2+LARGEURCASE*2, al_map_rgb(255,0,0));
            }
        }
    }

    if (batiment == 1 && (x1 +LARGEURCASE*4)<= XDepart + LARGEURCASE*NBLARGEURCASE && (y1 +LARGEURCASE*6)<= YDepart + LARGEURCASE*NBHAUTEURCASE){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*3,y2+LARGEURCASE*5, al_map_rgb(128,0,128));
    } else if (batiment == 1){
        al_draw_filled_rectangle(x1,y1,x2+LARGEURCASE*3,y2+LARGEURCASE*5, al_map_rgb(255,0,0));

    }

    for (int k =(y1-YDepart)/LARGEURCASE; k < (y1-YDepart)/LARGEURCASE +6; k++){
        for (int l=(x1-XDepart)/LARGEURCASE ; l < (x1-XDepart)/LARGEURCASE+4; l++){
            if (batiment==1 && (tabCase[k][l].habitationPresente == 1 || tabCase[k][l].routePresente==1 || tabCase[k][l].batimentPresent == 1)){
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