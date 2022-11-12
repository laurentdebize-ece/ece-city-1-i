#include "jeu.h"

void initialisationCase(Case tabCase[NBLARGEURCASE][NBLONGUEURCASE]){
    for (int i = 0; i < NBLARGEURCASE; i++) {
        for (int j = 0; j < NBLONGUEURCASE; j++) {
            tabCase[i][j].routePresente = 0;
            tabCase[i][j].batimentPresent = 0;
            tabCase[i][j].construisibilite = 0;
        }
    }
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

    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int x1 =0;
    int x2 = 0;
    int y1 = 0;
    int y2=0;
    int route = 0;
    int batiment = 0;
    Case tabCase[NBLARGEURCASE][NBLONGUEURCASE];

    initialisationCase(tabCase);

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);

    queue = al_create_event_queue();
    timer = al_create_timer(0.1);

    //Images
    images.menuPrincipal= al_load_bitmap("../Images/menuPrincipal1.png");
    images.staline= al_load_bitmap("../Images/Staline.png");
    images.trump= al_load_bitmap("../Images/Trump.png");
    images.map= al_load_bitmap("../Images/map.png");
    images.route1= al_load_bitmap("../Images/route.png");
    images.route2= al_load_bitmap("../Images/route2.png");
    images.maison= al_load_bitmap("../Images/maison.png");
    images.roue= al_load_bitmap("../Images/roueDentee.png");
    images.herbe= al_load_bitmap("../Images/herbe.png");
    images.eclair= al_load_bitmap("../Images/éclair.png");
    images.eau= al_load_bitmap("../Images/eau.png");
    images.couches= al_load_bitmap("../Images/couches.png");
    images.boutonCouches= al_load_bitmap("../Images/boutonCouches.png");

    //Booléens
    etats.fin=0;
    etats.etatMenuPrincipal=1;
    etats.etatMode=1;
    etats.modeCapitaliste=0;
    etats.modeCommuniste=0;
    etats.etatEchap=0;
    etats.couche1=1;
    etats.couche2=0;
    etats.couche3=0;
    etats.etatBoutonReglage=0;

    //Fonts
    fonts.font1= al_load_ttf_font("../Fonts/font1.ttf",40,0);
    fonts.font2= al_load_ttf_font("../Fonts/font1.ttf",20,0);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_set_window_position(display,0,0);

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
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (etats.etatMenuPrincipal) {
                    choixMenuPrincipal(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatMode) {
                    choixMode(&etats, event.mouse.x, event.mouse.y);
                } else if (etats.etatEchap) {
                    choixMenuEchap(&etats, event.mouse.x, event.mouse.y);
                } else {
                    choixJeu(&etats,event.mouse.x,event.mouse.y);
                    if(etats.etatBoutonReglage){
                        choixMenuBoutonCouches(&etats,event.mouse.x,event.mouse.y);
                    }
                    if (etats.couche1) {
                        if ((event.mouse.button & 1) == 1) {
                            if (event.mouse.x >= LARGEUR_FE - 65 && event.mouse.x <= LARGEUR_FE - 15
                                && event.mouse.y >= 50 && event.mouse.y <= 100) {
                                if(route){
                                    route=0;
                                }else {
                                    route = 1;
                                }
                                batiment = 0;
                            }
                            if (event.mouse.x >= LARGEUR_FE - 65 && event.mouse.x <= LARGEUR_FE - 15
                                && event.mouse.y >= 250 && event.mouse.y <= 300) {
                                if(batiment){
                                    batiment=0;
                                } else {
                                    batiment = 1;
                                }
                                route = 0;
                            }
                            if (event.mouse.x >= LARGEUR_FE - 65 && event.mouse.x <= LARGEUR_FE - 15
                                && event.mouse.y >= 150 && event.mouse.y <= 200) {
                                route = 0;
                                batiment = 0;
                            }
                            definirCaseBatiment(event, batiment, tabCase);
                        }
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                break;
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
                    al_clear_to_color(al_map_rgb(255, 255, 255));
                    if (etats.couche1) {
                        afficherPremiereCouche(images, fonts);
                        if (route) {
                            al_draw_bitmap(images.route1, x1, y1, 0);
                        }
                        if (batiment) {
                            al_draw_filled_rectangle(x1, y1, x2 + LARGEURCASE * 2, y2 + LARGEURCASE * 2,
                                                     al_map_rgb(0, 255, 0));

                        }
                        if(!route && !batiment) {
                            al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 0, 0));
                        }
                        afficherDetailsConstruction(fonts, xMouse, yMouse);
                        definirCaseRoute(route, tabCase, xMouse, yMouse, mouse.buttons);
                        afficherRoute(tabCase, images);
                        afficherBatiment(tabCase);
                    } else if (etats.couche2) {
                        afficherDeuxiemeCouche(images);
                    } else if (etats.couche3) {
                        afficherTroisiemeCouche(images);
                    }
                    affichageMap(images,etats,fonts,xMouse,yMouse);
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