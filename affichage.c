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

void affichageMenuPrincipal(Images images){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(images.menuPrincipal,0,0,0);
    al_draw_filled_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(123, 165, 248));
    al_draw_rectangle(LARGEUR_FE/2 -75,HAUTEUR_FE-100,LARGEUR_FE/2 +75,HAUTEUR_FE-175, al_map_rgb(0,0,0),5);
}

void choixMenuPrincipal(Etats *etats,int x,int y){
    if((x>LARGEUR_FE/2 -75 && x<LARGEUR_FE/2 +75) && (y>HAUTEUR_FE-175 && y<HAUTEUR_FE-100)){
        etats->etatMenuPrincipal=0;
    }
}

void affichageMode(Images images){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(LARGEUR_FE/2 -175,HAUTEUR_FE/2 -50,LARGEUR_FE/2 -25,HAUTEUR_FE/2 +50, al_map_rgb(123, 165, 248));
    al_draw_filled_rectangle(LARGEUR_FE/2 +25,HAUTEUR_FE/2 -50,LARGEUR_FE/2 +175,HAUTEUR_FE/2 +50, al_map_rgb(255,165,0));
}

void choixMode(Etats *etats,int x,int y){
    if((x>LARGEUR_FE/2 -175 && x<LARGEUR_FE/2 -25)&&(y>HAUTEUR_FE/2 -50 && y<HAUTEUR_FE/2 +50)){
        etats->modeCapitaliste=1;
        etats->etatMode=0;
    }
    if((x>LARGEUR_FE/2 +25 && x<LARGEUR_FE/2 +175)&&(y>HAUTEUR_FE/2 -50 && y<HAUTEUR_FE/2 +50)){
        etats->modeCommuniste=1;
        etats->etatMode=0;
    }
}