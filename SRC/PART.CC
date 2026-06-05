//#include "Part.h"

#define RETARD_CANVI_DIRECCIO 4


void Quit(byte *);


void tObjecte::tObjecte()  // er constructor...
{
 int i;

 PActual = NULL;

 for(i=0;i<MAX_DIRECCIONS;i++) direccio[i] = NULL;

}


void tObjecte::copia(const tObjecte &Part)
{
 int i;
 PAnimacio actual,anterior,nou;

 for(i=0;i<MAX_DIRECCIONS;i++)
 {
  if((actual = Part.direccio[i]) != NULL)
  {

   anterior = NULL;
   do{
     nou= new tAnimacio;
     nou -> actual = actual ->actual;
     nou -> temps = actual -> temps;
     if(anterior == NULL) // 1st.
     {
       direccio[i] = nou;
     }
     else // 2nd,3rd,4rt,...,ect
     {
      anterior->PSeguent = nou;
     }
     anterior = nou;
     actual = actual -> PSeguent;

   }while((actual != NULL)&&(actual != Part.direccio[i]));

   if(actual == Part.direccio[i]) anterior->PSeguent = direccio[i];
   else anterior->PSeguent = NULL;

  }
  else
  {
   direccio[i] = NULL;
  }
 }

}



tObjecte & tObjecte::operator = (tObjecte const &S)
{


 // Destrucci¢...

 this->tObjecte::~tObjecte();

 // Copia de la nova part...

 this->copia(S);

 PActual = direccio[1];

 return (*this);

}



void tObjecte::AfegirFrame(int Dir,int Sprite,int temps,int NUL)
{


 // Sprite = Numero de sprite.
 // Dir = Direccio del sprite.
 // NUL = Si '1' llavors la animacio es finita, si no, no ho ‚s.

 PAnimacio PInici,PAux;
 PAnimacio PNou = NULL;

 PNou = new tAnimacio;

 if((PInici = PAux = direccio[Dir]) != NULL) // Ja el tenim ocupat !!!
 {
  while((PAux->PSeguent != NULL) && (PAux->PSeguent != PInici)) // Anem buscant l' ultim...
  {
   PAux = PAux->PSeguent;
  } // Ja l'hem trobat...


 }
 else // Es Nou !!!
 {

  direccio[Dir] = PActual = PAux = PInici = PNou;

 }


 if(NUL) // Llavors ser  una animaci¢ finita...
 {
  // Carrega de dades...

  PAux->PSeguent = PNou;
  PNou->PSeguent = NULL;
  PNou->actual = Sprite;
  PNou->temps = temps;

 }
 else // Ser  infinita...
 {

  PNou -> PSeguent = PInici;
  PNou->actual = Sprite;
  PNou->temps = temps;
  PAux -> PSeguent = PNou;

 }


 // Afegit OK!

}
 

int tObjecte::EsNul()
{
 return(PActual == NULL);
}

int tObjecte::SpriteActual()
{
 return(PActual -> actual);
}

void tObjecte::SeguentFrame()
{
 if(!EsNul())
 {
  PActual = PActual -> PSeguent;
 }
}



void tObjecte::EntrarCoordenades(int x,int y)
{
 posx = x;
 posy = y;
}





void tObjecte::ActualitzarCoordenades(int x,int y) // Li podem passar els moviments que volguem !!! (Serïla estrategia !!!)
{
 if(!EsNul())
 {

  direccio_actual = 1;

  if(posx<x){posx = posx + (x-posx);direccio_actual = 0;}// Anirem cap a la dreta...
  if(posx>x){posx = posx - (posx-x);direccio_actual = 2;} // Anirem cap a la esquerra...
  if(posy<y) posy = posy + (y-posy);
  if(posy>y) posy = posy - (posy-y);
 
  if((direccio_actual == 0)) {if(insisteixd<RETARD_CANVI_DIRECCIO) {insisteixd++;direccio_actual=1;}else direccio_actual = 0;}
  else insisteixd = 0;
  if((direccio_actual == 2)) {if(insisteixe<RETARD_CANVI_DIRECCIO) {insisteixe++;direccio_actual=1;}else direccio_actual = 2;}
  else insisteixe = 0;

 

  if((direccio_actual!=direccio_anterior))
  {
   switch(direccio_actual)
   {
    case 0:{Esquerra();direccio_anterior = 0;}break;
    case 1:Centre();direccio_anterior = 1;break;
    case 2:{Dreta();direccio_anterior = 2;}

   }
  }

 }
}






void tObjecte::Dreta()
{
 if(direccio[0]!=NULL)
 {
  PActual = direccio[0];
 }
}

void tObjecte::Centre()
{
 if(direccio[1]!=NULL)
 {
  PActual = direccio[1];
 }
}


void tObjecte::Esquerra()
{
 if(direccio[2]!=NULL)
 {
  PActual = direccio[2];
 }
}



void tObjecte::EscriureActual(word SEGMENT)
{
 if(!EsNul())
 {
  PutSprite(posx,posy,Sprites[PActual->actual].imatge,Sprites[PActual->actual].dimx,Sprites[PActual->actual].dimy,0,0,AMPLADA_PANTALLA-1,ALTURA_PANTALLA-1,COLOR_MASCARA,SEGMENT);
 }
}



void tObjecte::~tObjecte()  // er destructor...
{
 int i;
 PAnimacio PAux = NULL;


 for(i=0;i<MAX_DIRECCIONS;i++)
 {

  if((direccio[i]) != NULL)
  {

    PActual = direccio[i];
    PActual = PActual->PSeguent;

  
     while( (PActual != NULL) && (PActual != direccio[i]) )
     {
    
      PAux = PActual->PSeguent;
      delete PActual;
      PActual = PAux;
  
     }
     //  Estem a l' ultim.
    
      delete direccio[i];
      direccio[i] = NULL;

  }


 }
 
}

