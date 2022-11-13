//
// Created by Kevin Le Heurt on 08/11/2022.
//

#ifndef ECE_CITY_1_I_CELLULE_H
#define ECE_CITY_1_I_CELLULE_H

typedef int typage;

struct _cellule {
    typage element;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;

#endif //ECE_CITY_1_I_CELLULE_H
