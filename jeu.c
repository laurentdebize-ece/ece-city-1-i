//
// Created by Kevin Le Heurt on 09/11/2022.
//

#include "jeu.h"

void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            tabCase[i][j].routePresente = 0;
            tabCase[i][j].habitationPresente = 0;
            tabCase[i][j].batimentPresent = 0;
            tabCase[i][j].construisibilite = 0;
            tabCase[i][j].niveauBatiment = 0;
            tabCase[i][j].numeroMaison = 0;
        }
    }
}

void calculCaseTabPixel(int* i,int* j,int x1,int y1){
    *i = (y1-YDepart)/LARGEURCASE;
    *j = (x1-XDepart)/LARGEURCASE;
}

void choixBoiteAoutil(ALLEGRO_EVENT event, int* curseur,int* route ,int* habitation ,int* batiment){
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 50 && event.mouse.y <= 100){
        *route = 1;
        *habitation = 0;
        *batiment = 0;
        *curseur = 0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 250 && event.mouse.y <= 300){
        *habitation = 1;
        *route = 0;
        *batiment = 0;
        *curseur = 0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 350 && event.mouse.y <= 400){
        *habitation = 0;
        *route = 0;
        *batiment = 1;
        *curseur = 0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 150 && event.mouse.y <= 200){
        *route = 0;
        *habitation = 0;
        *batiment = 0;
        *curseur = 1;

    }
}



void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    if (compteur%50 == 0){
        for (int i = 0; i < NBHAUTEURCASE; i++) {
            for (int j = 0; j < NBLARGEURCASE; j++){
                if (tabCase[i][j].habitationPresente == 1 && tabCase[i][j].construisibilite == 1){
                    if (tabCase[i][j-1].routePresente == 1 || tabCase[i+1][j-1].routePresente == 1 || tabCase[i+2][j-1].routePresente == 1 || tabCase[i+3][j].routePresente == 1 || tabCase[i+3][j+1].routePresente == 1 || tabCase[i+3][j+2].routePresente == 1 || tabCase[i][j+3].routePresente == 1 || tabCase[i+1][j+3].routePresente == 1 || tabCase[i+2][j+3].routePresente == 1 || tabCase[i-1][j].routePresente == 1 || tabCase[i-1][j+1].routePresente == 1 || tabCase[i-1][j+2].routePresente == 1 ){
                        for (int k =i; k < i+3; k++){
                            for (int l=j ; l < j+3; l++){
                                if (tabCase[k][l].niveauBatiment < 4){
                                    tabCase[k][l].niveauBatiment++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void jeu(){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;

    Fonts fonts;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int fin = 0;
    int x1 =0;
    int x2 = 0;
    int y1 = 0;
    int y2=0;
    int curseur = 1;
    int route = 0;
    int habitation = 0;
    int batiment = 0;
    long long compteur = 0;
    int chrono = 0;
    int nbMaison = 1;
    Case tabCase[NBHAUTEURCASE][NBLARGEURCASE];

    initialisationCase(tabCase);

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);
    fonts.font1= al_load_ttf_font("../Fonts/font1.ttf",40,0);


    queue = al_create_event_queue();
    timer = al_create_timer(0.1);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (fin == 0) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin = 1;
                    }
                        break;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if ((event.mouse.button & 1) == 1){
                    choixBoiteAoutil(event,&curseur,&route,&habitation,&batiment);
                    definirCaseHabitation(event, habitation, tabCase,&nbMaison);
                    definirCaseRoute(event, route, tabCase);
                    definirCaseBatiment(event,batiment,tabCase);
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                caseSouris(event,&x1,&x2,&y1,&y2);
                break;
            case ALLEGRO_EVENT_TIMER:
                affichageMap(fonts);
                afficherCompteur(fonts,&compteur,&chrono);
                ameliorerHabitation(compteur,tabCase);
                afficherHabitation(tabCase);
                afficherBatiment(tabCase);
                afficherRoute(tabCase);
                afficherCaseCurseur(x1,x2,y1,y2,curseur,route,habitation,batiment,tabCase);
                al_flip_display();
                break;
        }

    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}



