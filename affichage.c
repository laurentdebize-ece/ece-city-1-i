#include "affichage.h"
#include "Structure.h"

void affichageMap(){
    al_clear_to_color(al_map_rgb(255,255,255));
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++){
            al_draw_rectangle(XDepart + (j*LARGEURCASE), YDepart + (i*LARGEURCASE), XDepart+ LARGEURCASE + (j*LARGEURCASE), YDepart + LARGEURCASE + (i*LARGEURCASE),
                              al_map_rgb(0,0,0),2);

        }
    }
    al_draw_filled_rectangle(1150,50,1200,100, al_map_rgb(0,0,0));
    al_draw_filled_rectangle(1150,150,1200,200, al_map_rgb(255,0,0));
    al_draw_filled_rectangle(1150,250,1200,300, al_map_rgb(0,255,0));
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

void definirCaseRoute(ALLEGRO_EVENT event, int route, Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            if (event.mouse.x >= XDepart + (j * LARGEURCASE) &&
                event.mouse.x <= XDepart + LARGEURCASE + (j * LARGEURCASE) &&
                event.mouse.y >= YDepart + (i * LARGEURCASE) &&
                event.mouse.y <= YDepart + LARGEURCASE + (i * LARGEURCASE)) {
                if (route==1){
                    tabCase[i][j].routePresente = 1;
                }

            }

        }

    }
}

void afficherRoute(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            if (tabCase[i][j].routePresente == 1 && tabCase[i][j].batimentPresent==0){
                al_draw_filled_rectangle(XDepart + (j * LARGEURCASE),YDepart + (i * LARGEURCASE),XDepart + LARGEURCASE + (j * LARGEURCASE),YDepart + LARGEURCASE + (i * LARGEURCASE), al_map_rgb(0,0,0));
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
