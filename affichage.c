#include "affichage.h"

void affichageMap(Images images){
    al_clear_to_color(al_map_rgb(255,255,255));
    al_draw_bitmap(images.map,XDepart,YDepart,0);
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);

        }
    }
    al_draw_bitmap(images.route2,LARGEUR_FE-65,50,0);
    al_draw_filled_rectangle(LARGEUR_FE-65,150,LARGEUR_FE-15,200, al_map_rgb(255,0,0));
    al_draw_bitmap(images.maison,LARGEUR_FE-65,250,0);
}

void caseSouris(ALLEGRO_EVENT event, int* x1,int* x2, int* y1, int* y2){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
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

}

void definirCaseRoute(int route, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE],int xMouse,int yMouse,int bouton){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
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

void afficherRoute(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE],Images images){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1 && tabCase[i][j].batimentPresent==0){
                al_draw_bitmap(images.route1,XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),0);
            }

        }

    }
}

void definirCaseBatiment(ALLEGRO_EVENT event, int batiment, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (batiment==1){
                    tabCase[i][j].batimentPresent = 1;
                    tabCase[i+1][j].batimentPresent = 1;
                    tabCase[i+2][j].batimentPresent = 1;
                    tabCase[i][j+1].batimentPresent = 1;
                    tabCase[i+1][j+1].batimentPresent = 1;
                    tabCase[i+2][j+1].batimentPresent = 1;
                    tabCase[i][j+2].batimentPresent = 1;
                    tabCase[i+1][j+2].batimentPresent = 1;
                    tabCase[i+2][j+2].batimentPresent = 1;

                }

            }

        }

    }
}

void afficherBatiment(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            if (tabCase[i][j].batimentPresent == 1 ){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE) ,YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,255,0));
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