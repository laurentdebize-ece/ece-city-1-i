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
}