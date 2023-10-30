#include "Invader.h"

int myposy,myposx;

#define MAX_OBJECTES  25

#define MAX_ENEMY_SHOTS       10
#define MAX_MY_SHOTS          15
#define MAX_COLISIONABLES     25


#define CENTREX myposx+(DIM_SPR_16X16 >> 1)
#define CENTREY myposx+(DIM_SPR_16X16 >> 1)




/*
typedef struct tEnemyShot
{
 tPart *PARTS;
};

typedef struct tMyShot
{
 tPart *PARTS;
};



typedef struct tObjectList  // Pot ser meteorit ?
{

 tObject actual;
 tObjectList *PSeguent; // Quant es destruit

};


typedef struct tEnemyShotList
{

 tEnemyShot     actual;
 tEnemyShotList *PSeguent;

};


typedef struct tMyShotList
{
 tMyShot     actual;
 tMyShotList *PSeguent;
};
*/



// void CrearObjecte(IniciX,IniciY,TipusPartActual,TipusPartDestruida,Moviment[AUTO][0]);
// Si Moviment = AUTO . Calcula la teva posici� i realitza el moviment RECTA o
//                      amb cercles.

// TipusObjecte = ENEMICS , DISPARS_ENEMICS, ELS_MEUS_DISPARS , ITEMS...
