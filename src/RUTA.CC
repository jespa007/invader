#include "invader.h"

void Quit(byte *);


tRuta::tRuta()
{


 PARTS = NULL;
 N_Moviments = 0;
 M_Actual = 0;
 PActual = NULL;

}

void tRuta::copia(const tRuta &Ruta)
{
 PMoviments actual,anterior,nou;

 if((actual = Ruta.PARTS) != NULL)
 {

   anterior = NULL;
   do{

     nou= new MOV;
     nou -> actual = actual -> actual;
     nou -> n_vegades = actual -> n_vegades;
     nou -> condicio = actual -> condicio;
     nou -> vel = actual -> vel;


     if(anterior == NULL) // 1st.
     {
       PARTS = nou;
     }
     else // 2nd,3rd,4rt,...,ect
     {
      anterior->PSeguent = nou;
     }
     anterior = nou;
     actual = actual -> PSeguent;
     PActual = PARTS; // Al principi...

 }while((actual != NULL));
 anterior->PSeguent = NULL;
 }
 else
 {
   PARTS = NULL;
 }

}

tRuta & tRuta::operator = (tRuta const &S)
{

 
 // Destrucci�...

 this->tRuta::~tRuta();

 // Copia de la nova part...

 this->copia(S);

 N_Moviments = 0;
 M_Actual = 0;
 x=y=0;

 return (*this);

}


void tRuta::AfegirMoviment(const tMoviment &M,int vel,int condicio,int n_vegades)
{
 byte Motiu0[] = {"Insuficient mem�ria...\0"};
 PMoviments PNou;

 PNou = new MOV;

 if(PNou == NULL) Quit(Motiu0);

 // C�rrega de dades...

 PNou -> actual = M;
 PNou -> vel = vel;
 PNou -> condicio = condicio;
 PNou -> n_vegades = n_vegades;
 PNou -> PSeguent = NULL;

 // Enlla�ament...

 if(PARTS == NULL)
 {
  PActual = PARTS = PNou;
 }
 else
 {
  PActual = PARTS;
  while(PActual -> PSeguent != NULL) PActual = PActual -> PSeguent;

  PActual -> PSeguent = PNou;
  
  PActual = PARTS;
 }

}

void tRuta::EntrarCoordenades(int X,int Y)
{
 x=X;
 y=Y;

 PActual->actual.EntrarCoordenades(x,y);

}


void tRuta::SeguentPosicio(int *X,int *Y,int myposx,int myposy,int velx,int vely,int dimensio)
{
 
 if(!EsNul())
 {


       switch(PActual -> condicio)
       {

        case NORMAL: PActual->actual.SeguentPosicio(X,Y,myposx,myposy,velx,vely,dimensio);break;

       }

      if(PActual->actual.EsNul())
      {

       M_Actual++;
       N_Moviments += PActual->actual.MovimentsActuals();

       if((M_Actual < PActual->n_vegades)||(PActual->n_vegades == INFINIT))
       {
  
        M_Actual = 0;
        PActual->actual.Reset();
       }

       else
       {
        M_Actual = 0;
        PActual = PActual -> PSeguent;
       }
      }



  }
}


int tRuta::TransicioYMovimentSeguent()
{
 if((PActual != NULL)&&(PActual -> PSeguent != NULL))
 {
  return(PActual->actual.RetornarSigneY() != PActual->PSeguent->actual.RetornarSigneY());
 }
}




int tRuta::EsNul()
{
 return (PActual == NULL);
}


int tRuta::N() // Per llen�ar contratac...
{
 return (N_Moviments+PActual->actual.MovimentsActuals());
}


tRuta::~tRuta()
{
 PMoviments actual,anterior;

 if((actual = PARTS) != NULL)
 {

  do{

   anterior = actual;
   actual = actual -> PSeguent;
   delete anterior;

  }while(actual != NULL);

 PARTS = NULL;

 }

}




