//
// Created by Kevin Le Heurt on 09/11/2022.
//

#include "jeu.h"

void initialisationCase(Case tabCase[NBHAUTEURCASE][NBLARGEURCASE]){
    for (int i = 0; i < NBHAUTEURCASE; i++) {
        for (int j = 0; j < NBLARGEURCASE; j++) {
            tabCase[i][j].routePresente = 0;
            tabCase[i][j].habitationPresente = 0;
            tabCase[i][j].chateauDeauPresent = 0;
            tabCase[i][j].centraleElectriquePresente = 0;
            tabCase[i][j].construisibilite = 0;
            tabCase[i][j].niveauBatiment = 0;
            tabCase[i][j].numeroMaison = 0;
        }
    }
}

void initialiserInfoJeu(InformationJeu* informationJeu){
    informationJeu->argent = 500000;
    informationJeu->capaciteEau = 0;
    informationJeu->capaciteElectricite = 0;
    informationJeu->habitant = 0;
}

void calculCaseTabPixel(int* i,int* j,int x1,int y1){
    *i = (y1-YDepart)/LARGEURCASE;
    *j = (x1-XDepart)/LARGEURCASE;
}

void choixBoiteAoutil(ALLEGRO_EVENT event, int* curseur,int* route ,int* habitation ,int* eau, int* electricite){
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 50 && event.mouse.y <= 100){
        *route = 1;
        *habitation = 0;
        *eau = 0;
        *curseur = 0;
        *electricite = 0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 250 && event.mouse.y <= 300){
        *habitation = 1;
        *route = 0;
        *eau = 0;
        *curseur = 0;
        *electricite = 0;


    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 350 && event.mouse.y <= 400){
        *habitation = 0;
        *route = 0;
        *eau = 1;
        *curseur = 0;
        *electricite = 0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 150 && event.mouse.y <= 200){
        *route = 0;
        *habitation = 0;
        *eau = 0;
        *curseur = 1;
        *electricite = 0;

    }
    if (event.mouse.x >= 1250 && event.mouse.x <= 1300
        && event.mouse.y >= 350 && event.mouse.y <= 400){
        *route = 0;
        *habitation = 0;
        *eau = 0;
        *curseur = 0;
        *electricite = 1;

    }
}



void ameliorerHabitation(long long compteur,Case tabCase[NBHAUTEURCASE][NBLARGEURCASE], long long compteurMaison){
    if ((compteur%50 == 0)){
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

void impotTaxe(InformationJeu informationJeu, int compteur){

}


void jeu(){
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER *timer = NULL;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int fin = 0;
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    int curseur = 1;
    int route = 0;
    int habitation = 0;
    int electricite = 0;
    int eau = 0;
    long long compteur = 0;
    int chrono = 0;
    int nbMaison = 1;
    long long compteurMaison= 0;
    Case tabCase[NBHAUTEURCASE][NBLARGEURCASE];
    InformationJeu informationJeu;
    Images images;
    Etats etats;
    Fonts fonts;


    //Images
    images.menuPrincipal= al_load_bitmap("../Images/menuPrincipal1.png");
    images.staline= al_load_bitmap("../Images/Staline.png");
    images.trump= al_load_bitmap("../Images/Trump.png");
    images.map= al_load_bitmap("../Images/map.png");
    images.route1= al_load_bitmap("../Images/route.png");
    images.route2= al_load_bitmap("../Images/route2.png");
    images.maison= al_load_bitmap("../Images/maison.png");

    //Fonts
    fonts.font1= al_load_ttf_font("../Fonts/font1.ttf",40,0);
    fonts.font2= al_load_ttf_font("../Fonts/font1.ttf",20,0);

    //Booléens
    etats.fin=0;
    etats.etatMenuPrincipal=1;
    etats.etatMode=1;
    etats.modeCapitaliste=0;
    etats.modeCommuniste=0;
    etats.etatEchap=0;

    initialisationCase(tabCase);
    initialiserInfoJeu(&informationJeu);

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);

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
                    choixBoiteAoutil(event,&curseur,&route,&habitation,&eau,&electricite);
                    definirCaseHabitation(event, habitation, tabCase,&nbMaison,&informationJeu,compteur,&compteurMaison);
                    definirCaseRoute(event, route, tabCase,&informationJeu);
                    definirCaseChateauDeau(event, eau, tabCase, &informationJeu);
                    definirCaseCentraleElectrique(event,electricite,tabCase,&informationJeu);
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                caseSouris(event,&x1,&x2,&y1,&y2);
                break;
            case ALLEGRO_EVENT_TIMER:
                affichageMap(fonts,informationJeu,images);
                afficherCompteur(fonts,&compteur,&chrono);
                ameliorerHabitation(compteur,tabCase,compteurMaison);
                afficherHabitation(tabCase);
                afficherChateauDeau(tabCase);
                afficherRoute(tabCase,images);
                afficherCentraleElectrique(tabCase);
                afficherCaseCurseur(x1, x2, y1, y2, curseur, route, habitation, eau, tabCase, images,electricite);
                al_flip_display();
                break;
        }

    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
}






