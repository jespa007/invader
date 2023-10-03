//#include "Part.h"
#include "Invader.h"

#define RETARD_CANVI_DIRECCIO 4


void Quit(byte *);


tObjecte::tObjecte()  // er constructor...
{
 int i;

 PActual = NULL;

 for(i=0;i<MAX_DIRECCIONS;i++) direccio[i] = NULL;

 Regalet = Score = Invencible = Vitalitat = 0;

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
     nou -> temps_frame = actual -> temps_frame;
     nou -> temps_actual = actual -> temps_actual;

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

   PActual = direccio[1];

  }
  else
  {
   direccio[i] = NULL;
  }

 }

}



tObjecte & tObjecte::operator = (tObjecte const &S)
{


 // Destrucci�...

 this->tObjecte::~tObjecte();

 // Copia de la nova part...

 this->copia(S);

 PActual = direccio[1];
 Regalet = S.Regalet;
 Vitalitat = S.Vitalitat;
 Score = S.Score;
 Invencible = S.Invencible;

 return (*this);

}



void tObjecte::AfegirFrame(int Dir,int Sprite,int temps,int NUL)
{
 byte Motiu0[]={"Caca de vaca !"};

 // Sprite = Numero de sprite.
 // Dir = Direccio del sprite.
 // NUL = Si '1' llavors la animacio es finita, si no, no ho �s.

 PAnimacio PInici,PAux;
 PAnimacio PNou = NULL;

 PNou = new tAnimacio;

 if(PNou == NULL)
 {
  tObjecte::~tObjecte();
  Quit(Motiu0);
 }

 PNou->actual = Sprite;
 PNou->temps_frame = temps;
 PNou->temps_actual = 0;


 if((PInici = PAux = direccio[Dir]) != NULL) // Ja el tenim ocupat !!!
 {

  while((PAux->PSeguent != NULL) && (PAux->PSeguent != PInici)) // Anem buscant l' ultim...
  {
   PAux = PAux->PSeguent;
  } // Ja l'hem trobat...


  if(NUL) // Llavors ser� una animaci� finita...
  {
   // Carrega de dades...

   PNou->PSeguent = NULL;
  }
  else // Ser� infinita...
  {

   PNou -> PSeguent = PInici;

  }

   PAux -> PSeguent = PNou;



 }
 else // Es Nou !!!
 {

  direccio[Dir] = PNou;
  PActual = PNou;

  if(NUL) // Llavors ser� una animaci� finita...
  {
  // Carrega de dades...

   PNou->PSeguent = NULL;

  }
  else // Ser� infinita...
  {

   PNou -> PSeguent = direccio[Dir];

  }



 }


 // Afegit OK!

}
 

void tObjecte::EntrarDades(long int ENERGY,word SCORE,int REGALET,int I)
{
 Invencible = I;
 Vitalitat = ENERGY;
 Score = SCORE;
 Regalet = REGALET;
}

int tObjecte::ActualEsNul()
{
 return(PActual == NULL);
}




int tObjecte::SpriteActual()
{
 if(PActual != NULL)return(PActual -> actual);
 else return 0;
}




void tObjecte::SeguentFrame(int TransicioMoviment,int TransicioPosicio)
{
 if(!ActualEsNul())
 {

  
   if((PActual->temps_frame>=0))
   {
    if(PActual->temps_actual < PActual->temps_frame) PActual->temps_actual ++;
    else {PActual->temps_actual = 0;PActual = PActual -> PSeguent;}
   }
   else
   {
    switch(PActual->temps_frame)
    {
     
     case SEGUENT_POSICIO_AMB_TRANSICIO_Y: if(TransicioPosicio) PActual = PActual->PSeguent;
                                           break;
     case SEGUENT_MOVIMENT_AMB_TRANSICIO_Y: if(TransicioMoviment) PActual = PActual->PSeguent;
     
    }
   }



 }
}



void tObjecte::EntrarCoordenades(int x,int y)
{
 posx = x;
 posy = y;
}





void tObjecte::ActualitzarCoordenades(int x,int y) // Li podem passar els moviments que volguem !!! (Ser�la estrategia !!!)
{
 if(!ActualEsNul())
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

 

  if((direccio_actual!=direccio_anterior)&&(PotCanviarDireccio()))
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

int tObjecte::EsInvencible()
{
	return(Invencible);
}

int tObjecte::PotCanviarDireccio()
{
 return((direccio[0]!=NULL)&&(direccio[2]!=NULL));
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



void tObjecte::EscriureActual()
{
 if(!ActualEsNul())
 {


  if(!Invencible)
  {
   PutSprite(posx,posy,Sprites[PActual->actual].imatge,Sprites[PActual->actual].dimx,Sprites[PActual->actual].dimy,0,0,AMPLADA_PANTALLA_JOC-1,ALTURA_PANTALLA_JOC-1,COLOR_MASCARA);
  }
  else
  {


   if((Invencible & 2) == 0)
   {
    PutSprite(posx,posy,Sprites[PActual->actual].imatge,Sprites[PActual->actual].dimx,Sprites[PActual->actual].dimy,0,0,AMPLADA_PANTALLA_JOC-1,ALTURA_PANTALLA_JOC-1,COLOR_MASCARA);
   }

   if(Invencible>0) Invencible--;

   if(Cheat&&(Invencible == 0)) Invencible = 4;

  }
 }
}

int  tObjecte::Power() // Retorna la vitalitat...
{
 return(Vitalitat);
}

int  tObjecte::DecrementarVitalitat(int N) // Retorna la vitalitat...
{
 if(PActual!=NULL)
 {
  if(!Sprites[PActual->actual].invencible) return ((Vitalitat -= N)>0); // retorna CERT si la vitalitat encara es positiva...
 }
 return 1;
}


int   tObjecte::Puntuacio()
{
 return (Score);
}
int   tObjecte::Regal()
{
 return (Regalet);
}




tObjecte::~tObjecte()  // er destructor...
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
      PActual = direccio[i] = NULL;

  }


 }
 
}

