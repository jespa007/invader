#ifndef ENEMICS_H
 #define ENEMICS_H

#include "const.h"


typedef struct INFO_ENEMY
{
 int enemic;
 int ruta;
 int ataca;
 int x,y;
 int temps;
};

#define MAX_ENEMICS_STAGE1 108



void CarregarEnemicsStage1();


#endif
