#ifndef ECE_CITY_1_I_FIFO_H
#define ECE_CITY_1_I_FIFO_H

#include "cellule.h"


struct _file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct _file* File;

File fileVide();
int longueur(File F);
void enfiler(File F, typage element);
typage tete(File F);
void defiler(File F);
typage defilement(File F);
void ecrireFile(File F);

#endif //ECE_CITY_1_I_FIFO_H
