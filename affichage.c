#include "affichage.h"

void affichageMap(){
    al_clear_to_color(al_map_rgb(255,255,255));
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);
        }
    }
}

void affichageMenuPrincipal(Images images,Fonts fonts){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(images.menuPrincipal,0,0,0);
    al_draw_filled_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(123, 165, 248));
    al_draw_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(0,0,0),5);
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
    al_draw_filled_rectangle(LARGEUR_FE/4 -125,HAUTEUR_FE/2 -50,LARGEUR_FE/4 +75,HAUTEUR_FE/2 +50, al_map_rgb(123, 165, 248));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),LARGEUR_FE/4 -100,HAUTEUR_FE/2 -25,0,"Capitaliste");
    al_draw_filled_rectangle(3*LARGEUR_FE/4 -100,HAUTEUR_FE/2 -50,3*LARGEUR_FE/4 +100,HAUTEUR_FE/2 +50, al_map_rgb(255,165,0));
    al_draw_textf(fonts.font1, al_map_rgb(255,255,255),3*LARGEUR_FE/4 -90,HAUTEUR_FE/2 -25,0,"Communiste");
    al_draw_filled_rectangle(0,HAUTEUR_FE-50,150,HAUTEUR_FE, al_map_rgb(255,255,255));
    al_draw_textf(fonts.font1, al_map_rgb(0,0,0),25,HAUTEUR_FE-45,0,"Retour");
}

void choixMode(Etats *etats,int x,int y){
    if((x>LARGEUR_FE/4 -125 && x<LARGEUR_FE/4 +75)&&(y>HAUTEUR_FE/2 -50 && y<HAUTEUR_FE/2 +50)){
        etats->modeCapitaliste=1;
        etats->etatMode=0;
    }
    if((x>3*LARGEUR_FE/4 -100 && x<3*LARGEUR_FE/4 +100)&&(y>HAUTEUR_FE/2 -50 && y<HAUTEUR_FE/2 +50)){
        etats->modeCommuniste=1;
        etats->etatMode=0;
    }
    if((x>0 && x<150) && (y>HAUTEUR_FE-50 && y<HAUTEUR_FE)){
        etats->etatMenuPrincipal=1;
    }
}