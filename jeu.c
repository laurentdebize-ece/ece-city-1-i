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

void choixBoiteAoutil(ALLEGRO_EVENT event, Etats *etats){
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 50 && event.mouse.y <= 100){
        etats->route = 1;
        etats->habitation = 0;
        etats->curseur = 0;
        etats->eau=0;
        etats->electricite=0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 250 && event.mouse.y <= 300){
        etats->habitation = 1;
        etats->route = 0;
        etats->curseur = 0;
        etats->eau=0;
        etats->electricite=0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 350 && event.mouse.y <= 400){
        etats->habitation = 0;
        etats->route = 0;
        etats->curseur = 0;
        etats->eau=1;
        etats->electricite=0;

    }
    if (event.mouse.x >= 1150 && event.mouse.x <= 1200
        && event.mouse.y >= 150 && event.mouse.y <= 200){
        etats->habitation = 0;
        etats->route = 0;
        etats->curseur = 1;
        etats->eau=0;
        etats->electricite=0;

    }
    if (event.mouse.x >= 1250 && event.mouse.x <= 1300
        && event.mouse.y >= 350 && event.mouse.y <= 400){
        etats->habitation = 0;
        etats->route = 0;
        etats->curseur = 0;
        etats->eau=0;
        etats->electricite=1;
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

    Images images;
    Etats etats;
    Fonts fonts;
    ALLEGRO_MOUSE_STATE mouse;
    InformationJeu informationJeu;

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    long long compteur = 0;
    int chrono=0;
    int nbMaison = 1;
    long long compteurMaison= 0;
    Case tabCase[NBHAUTEURCASE][NBLARGEURCASE];

    initialisationCase(tabCase);
    initialiserInfoJeu(&informationJeu);

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);

    queue = al_create_event_queue();
    timer = al_create_timer(0.1);

    //Images
    images.menuPrincipal = al_load_bitmap("../Images/menuPrincipal1.png");
    images.staline = al_load_bitmap("../Images/Staline.png");
    images.trump = al_load_bitmap("../Images/Trump.png");
    images.map = al_load_bitmap("../Images/map.png");
    images.route1 = al_load_bitmap("../Images/route.png");
    images.route2 = al_load_bitmap("../Images/route2.png");
    images.maison = al_load_bitmap("../Images/maison.png");
    images.roue = al_load_bitmap("../Images/roueDentee.png");
    images.herbe = al_load_bitmap("../Images/herbe.png");
    images.eclair = al_load_bitmap("../Images/éclair.png");
    images.eau = al_load_bitmap("../Images/eau.png");
    images.couches = al_load_bitmap("../Images/couches.png");
    images.boutonCouches = al_load_bitmap("../Images/boutonCouches.png");
    images.usine = al_load_bitmap("../Images/usine.png");
    images.chateau = al_load_bitmap("../Images/chateau.png");
    images.bulldozer = al_load_bitmap("../Images/bulldozer.png");

    //Booléens
    etats.fin = 0;
    etats.etatMenuPrincipal = 1;
    etats.etatMode = 1;
    etats.modeCapitaliste = 0;
    etats.modeCommuniste = 0;
    etats.etatEchap = 0;
    etats.couche1 = 1;
    etats.couche2 = 0;
    etats.couche3 = 0;
    etats.etatBoutonReglage = 0;
    etats.etatCouche = 0;
    etats.route = 0;
    etats.etatNoClick = 0;
    etats.curseur=1;
    etats.habitation=0;
    etats.eau=0;
    etats.electricite=0;
    etats.demolir=0;

    //Fonts
    fonts.font1 = al_load_ttf_font("../Fonts/font1.ttf", 40, 0);
    fonts.font2 = al_load_ttf_font("../Fonts/font1.ttf", 20, 0);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_position(display, 0, 0);

    al_start_timer(timer);

    while (etats.fin == 0) {
        al_get_mouse_state(&mouse);
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                etats.fin = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        if (!etats.etatMode) {
                            if (etats.etatEchap) {
                                etats.etatEchap = 0;
                            } else {
                                etats.etatEchap = 1;
                            }
                        }
                    }
                        break;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                if ((event.mouse.button & 1) == 1) {
                    choixBoiteAoutil(event, &etats);
                }
                if (etats.etatMenuPrincipal) {
                    choixMenuPrincipal(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatMode) {
                    choixMode(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatEchap) {
                    choixMenuEchap(&etats, event.mouse.x, event.mouse.y);
                } else {
                    choixJeu(&etats, event.mouse.x, event.mouse.y);
                    if (etats.etatBoutonReglage) {
                        choixBoutonOutil(&etats, event.mouse.x, event.mouse.y);
                    }
                    if (etats.couche1 && !etats.etatNoClick) {
                        definirCaseChateauDeau(event, etats.eau, tabCase, &informationJeu);
                        definirCaseCentraleElectrique(event, etats.electricite, tabCase, &informationJeu);
                        definirCaseHabitation(event, etats.habitation, tabCase, &nbMaison,&informationJeu,compteur,&compteurMaison);
                    }
                }
                break;
            }
            case ALLEGRO_EVENT_MOUSE_AXES:
                        caseSouris(event, &x1, &x2, &y1, &y2);
                        int xMouse = event.mouse.x;
                        int yMouse = event.mouse.y;
                        break;
                    case ALLEGRO_EVENT_TIMER: {
                        if (etats.etatMenuPrincipal) {
                            affichageMenuPrincipal(images, fonts);
                        } else if (etats.etatMode) {
                            affichageMode(images, fonts);
                        } else if (etats.etatEchap) {
                            afficherMenuEchap(fonts);
                        } else {
                            al_clear_to_color(al_map_rgb(255,255,255));
                            if (etats.couche1) {
                                if (etats.etatBoutonReglage) {
                                    if ((etats.etatCouche && (xMouse < LARGEUR_FE - 145 && yMouse > HAUTEUR_FE - 105
                                                              && xMouse > LARGEUR_FE - 340 &&
                                                              yMouse < HAUTEUR_FE - 45)) || (xMouse < LARGEUR_FE - 65
                                                                                             &&
                                                                                             yMouse < HAUTEUR_FE - 45 &&
                                                                                             xMouse >
                                                                                             LARGEUR_FE - 275 &&
                                                                                             yMouse >
                                                                                             HAUTEUR_FE - 165)) {
                                        etats.etatNoClick = 1;
                                    } else {
                                        etats.etatNoClick = 0;
                                    }
                                } else {
                                    etats.etatNoClick = 0;
                                }//Cette fonction sert à ne pas poser de route et d'autres sortes de structure lorsque l'on est dans un menu
                                afficherPremiereCouche(images, fonts);
                                if (!etats.etatNoClick) {
                                    definirCaseRoute(etats.route, tabCase, xMouse, yMouse, mouse.buttons,&informationJeu);
                                }
                                afficherCompteur(fonts, &compteur, &chrono);
                                ameliorerHabitation(compteur, tabCase,compteurMaison);
                                afficherHabitation(tabCase);
                                afficherRoute(tabCase, images);
                                afficherChateauDeau(tabCase);
                                afficherCentraleElectrique(tabCase);
                                afficherCaseCurseur(x1, x2, y1, y2,tabCase, images,etats);
                            } else if (etats.couche2) {
                                afficherDeuxiemeCouche(images, fonts);
                            } else if (etats.couche3) {
                                afficherTroisiemeCouche(images, fonts);
                            }
                            affichageMap(images,etats,fonts,xMouse,yMouse,informationJeu);
                        }
                        al_flip_display();
                        break;
                    }

                }
        }
                al_destroy_display(display);
                al_destroy_event_queue(queue);
                al_destroy_timer(timer);
    }