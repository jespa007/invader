#ifndef MOVIMENT_H
 #define MOVIMENT_H



#define INFINIT   -1   // Si el moviment no es infinit tindrem en compte el moviment actual...

#define NORMAL     0 
#define AUTO1     -1    // Va fins a nosaltres...
#define AUTO2     -2    // Es despla‡a horitzontalment a la nostra posicio X.
#define MANUAL    -3
#define DETECTA_POSX1 -4
#define DETECTA_POSX2 -5


typedef struct M
{
  int Moviment;
  int xpos,ypos;
  int v;
  int condicio;
  int vegades;
  M *PSeguent;
};

typedef M *PMoviment;


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
 void tMoviment::SeguentPosicio(int *X,int *Y,int MYPOSX,int MYPOSY,int velx,int vely,int Sprite);
 ~tMoviment();

};


#endif
