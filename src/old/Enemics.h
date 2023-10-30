#ifndef ENEMICS_H
 #define ENEMICS_H



typedef struct _INFO_ENEMY
{
 int enemic;
 int ruta;
 int ataca;
 int x,y;
 int temps;
}INFO_ENEMY;

#define MAX_ENEMICS_STAGE1 108



void CarregarEnemicsStage1();


#endif
