#include "Structure.h"


int main(){
    bool etatMenuPrincipal=1;

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_EVENT event = {0};
    ALLEGRO_TIMER* timer = NULL;

    Images images;

    al_init();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    int fin = 0;

    display = al_create_display(LARGEUR_FE, HAUTEUR_FE);

    queue = al_create_event_queue();
    timer = al_create_timer(0.1);

    images.menuPrincipal= al_load_bitmap("../Images/menuPrincipal.png");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    while (fin == 0){
        al_wait_for_event(queue,&event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN : {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE: {
                        fin=1;
                    }
                        break;
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:

                break;
            case ALLEGRO_EVENT_TIMER:
                if(etatMenuPrincipal){
                    affichageMenuPrincipal(images);
                } else {
                    affichageMap();
                }
                al_flip_display();
                break;

        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

}

