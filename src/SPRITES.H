#ifndef SPRITES_H
 #define SPRITES_H

#include "all_lib.h"

#define PASSIU           0
#define BALA_ENEMIC      1
#define ENEMIC_AERI      2
#define ENEMIC_TERRESTRE 3
#define EXPLOSIU         4

#define LA_MEVA_BALA     5


typedef byte far *tImatge;

typedef struct
{

 int dimx,dimy;
 tImatge imatge;
 int retard_dispar; // 0...MAX_DISPAR*DIFICULTAT
 int agresiu;  // 0 (No ho es), != 0 (ens diu el tipus de dispar a dispar…)...
 int invencible;  // es te en compte si decreix la seva vitalitat al ser impactat (CERT o FALS).
 int impactable;  // CERT/FALS
 int vx,vy;

}tSprite;





void PutSprite(int X,int Y,byte far * SPRITE,word AMPLADA,word ALTURA,word MIN_AMPLADA,word MIN_ALTURA,word MAX_AMPLADA,word MAX_ALTURA,char ColorMascara,word SEGMENT);
int Colisio(int X1,int Y1,int X2,int Y2);



#endif
