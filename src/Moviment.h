#ifndef MOVIMENT_H
 #define MOVIMENT_H

#include "definicions.h"
#include "mouse.h"

/*************\
| DEFINICIONS |
\*************/

#define INFINIT   -1   // Si el moviment no es infinit tindrem en compte el moviment actual...

#define NORMAL     0 
#define AUTO1     -1    // Va fins a nosaltres...
#define AUTO2     -2    // Es despla�a horitzontalment a la nostra posicio X.
#define MANUAL    -3
#define DETECTA_POSX1 -4
#define DETECTA_POSX2 -5


#define RXPYPM0    0  |  (+,+)
#define RXPYPM2    1  \
#define RXPYPM4    2  \
#define RXPYPM6    3  \
#define RXPYPM8    4  \
#define RXPYPM10   5  \
#define RXPYPM12   6  \
#define RXPYPM14   7  \
#define RXPYPM16   8  \
#define RXPYPM18   9  \

#define RXPYNM0    10 -- (+,-)
#define RXPYNM2    11 /
#define RXPYNM4    12 /
#define RXPYNM6    13 /
#define RXPYNM8    14 /
#define RXPYNM10   15 /
#define RXPYNM12   16 /
#define RXPYNM14   17 /
#define RXPYNM16   18 /
#define RXPYNM18   19 /

#define RXNYNM0    20 |  (-,-)
#define RXNYNM2    21 \
#define RXNYNM4    22 \
#define RXNYNM6    23 \
#define RXNYNM8    24 \
#define RXNYNM10   25 \
#define RXNYNM12   26 \
#define RXNYNM14   27 \
#define RXNYNM16   28 \
#define RXNYNM18   29 \

#define RXNYPM0    30 -- (-,+)
#define RXNYPM2    31 /
#define RXNYPM4    32 /
#define RXNYPM6    33 /
#define RXNYPM8    34 /
#define RXNYPM10   35 /
#define RXNYPM12   36 /
#define RXNYPM14   37 /
#define RXNYPM16   38 /
#define RXNYPM18   39 /


#define PENDENT                0.1f


#define MAX_POSICIONS          16
#define MAX_RECTES             21 //(word(float(1/PENDENT))*2) + 1

#define MAX_ELIPSES            0
#define MAX_CERCLES            3
#define MAX_MOVIMENTS          MAX_RECTES+MAX_ELIPSES+MAX_CERCLES



/**********************\
| DEFINICIONS DE TIPUS |
\**********************/


typedef struct _tM *PMoviment;

typedef struct _tM
{
  int Moviment;
  int xpos,ypos;
  int v;
  int condicio;
  int vegades;
  PMoviment  PSeguent;

}tM;



class tMoviment
{

 PMoviment PARTS,PActual;


 int x,y;
 int P_Actual;
 int M_Actual;
 int N_Moviments;


 void copia(const tMoviment &tMoviment);

public:

 tMoviment();
 tMoviment & operator = (const tMoviment  &S);
 void AfegirPart(int Moviment,int xpos,int ypos,int condicio,int v,int vegades);
 int Condicio();
 void EntrarCoordenades(int x,int y);
 int RetornarSigneY();
 int TransicioMoviment();
 int TransicioPosicio(int vel);

 void Reset();
 int EsNul();
 int MovimentsActuals();
 void SeguentPosicio(int *X,int *Y,int MYPOSX,int MYPOSY,int velx,int vely,int Sprite);
 ~tMoviment();

};


/*******************\
| VARAIBLES GLOBALS |
\*******************/

extern tPosicio *moviments[MAX_MOVIMENTS];

/************\
| PROTOTIPUS |
\************/

void Quit(byte *);
int InicialitzarMoviments();
int HiHaInterseccio(int x1,int y1,int x2,int y2,int dim1,int dim2);
int ElMeuMoviment(int x,int y,int myposx,int myposy,int dimensio);


#endif
