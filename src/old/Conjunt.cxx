#include "Invader.h"


void Quit(byte *);

tConjunt::tConjunt()
{
 OBJECTES = NULL;
}


void tConjunt::copia(const tConjunt &Conjunt)
{
 int i;
 PObjectes actual,anterior,nou;


  if((actual = Conjunt.OBJECTES) != NULL)
  {

   anterior = NULL;

   do{
     nou= new conjunt_objectes;

     nou -> actual = actual ->actual;
     nou -> temps = actual -> temps;
     nou -> part_debil = actual -> part_debil;
     nou -> retard_dispar = 0;
     nou -> offsetx = actual -> offsetx;
     nou -> offsety = actual -> offsety;

     if(anterior == NULL) // 1st.
     {
       PActual = OBJECTES = nou;
     }
     else // 2nd,3rd,4rt,...,ect
     {
      anterior->PSeguent = nou;
     }

     anterior = nou;
     actual = actual -> PSeguent;

   }while((actual != NULL));

   anterior->PSeguent = NULL;


  }

   else
  {
   OBJECTES = NULL;
  }


}

tConjunt & tConjunt::operator = (tConjunt const &S)
{


 // Destrucci�...

 this->tConjunt::~tConjunt();

 // Copia de la nova part...

 this->copia(S);

 return (*this);

}



void tConjunt::AfegirObjecte(tObjecte const &Objecte,int OFFSETX,int OFFSETY,int part_debil,int TEMPS)
{
 byte Motiu0[]={"Tens poca mem�ria pels objectes!\0"};
 PObjectes PNou=NULL,PAux = OBJECTES;

 
 PNou = new conjunt_objectes;

 if(PNou == NULL) Quit(Motiu0);

 PNou -> actual = Objecte;
 PNou -> offsetx = OFFSETX;
 PNou -> offsety = OFFSETY;
 PNou -> retard_dispar = 0;
 PNou -> temps = TEMPS;
 PNou -> part_debil = part_debil;
 PNou -> PSeguent = NULL;

 if(OBJECTES == NULL)
 {
   PActual = OBJECTES = PNou;
 }
 else
 {

  PAux = OBJECTES;

  while(PAux->PSeguent!=NULL) PAux = PAux->PSeguent;

  PAux -> PSeguent = PNou;

 }





}


void tConjunt::ActualitzarCoordenades(int X,int Y)
{
 PObjectes PAux = OBJECTES;

 while(PAux != NULL)
 {
  PAux -> actual.ActualitzarCoordenades(X+PAux -> offsetx,Y+PAux -> offsety);
  PAux =  PAux -> PSeguent;
 }

}

 
void tConjunt::ActualitzarConjunt(int TransicioMoviment,int TransicioPosicio)
{
 PObjectes PAux = OBJECTES,PAnterior;
 

 while(PAux != NULL)
 {


  if(((PAux -> temps > 0) || (PAux -> temps == INFINIT))&&!(PAux->actual.ActualEsNul()))
  {
	  
   
   PAux->actual.SeguentFrame(TransicioMoviment,TransicioPosicio);

   if((Sprites[PAux->actual.SpriteActual()].agresiu)&&(PAux->retard_dispar<Sprites[PAux->actual.SpriteActual()].retard_dispar)) PAux->retard_dispar++;
   else PAux->retard_dispar = 0;

   if(PAux->temps!=INFINIT) PAux->temps--;
   PAux =  PAux->PSeguent;

   
  }

  else
  {

    if(PAux == OBJECTES)
    {
     PAnterior = OBJECTES;
     OBJECTES = PAux = PAux -> PSeguent;

    }
    else
    {
     PAnterior = OBJECTES;
     while(PAnterior->PSeguent != PAux) PAnterior = PAnterior -> PSeguent;
     PAnterior -> PSeguent = PAux -> PSeguent;
     PAnterior = PAux;
     PAux = PAux -> PSeguent;
    }

    delete PAnterior;
  }
 }

 PActual = OBJECTES;
}


int tConjunt::ActualVolDisparar(int *X,int *Y,int TM,int TP)
{
 if(PActual != NULL)
 {
  (*X) = (PActual -> offsetx) + (Sprites[PActual ->actual.SpriteActual()].dimx >> 1);
  (*Y) = (PActual -> offsety) + (Sprites[PActual ->actual.SpriteActual()].dimx >> 1);

  if((Sprites[PActual ->actual.SpriteActual()].retard_dispar==SEGUENT_POSICIO_AMB_TRANSICIO_Y)&&TP)
  {
   return(Sprites[PActual ->actual.SpriteActual()].agresiu);
  }
  else
  {

   if( (PActual->retard_dispar == (Sprites[PActual ->actual.SpriteActual()].retard_dispar)))
   {

   PActual->retard_dispar = 0;
   return(Sprites[PActual ->actual.SpriteActual()].agresiu);

   }
  }
 }
 return 0;
}


void tConjunt::Seguent()
{
 if(PActual != NULL)
 {
  PActual = PActual -> PSeguent;
 }
}



int tConjunt::PartDebil()
{
 if(PActual!=NULL)
 {
  return (PActual->part_debil);
 }

 return 0;

}



void tConjunt::EscriureObjectes()
{
 PObjectes PAux = OBJECTES;

 while(PAux != NULL)
 {
  PAux -> actual.EscriureActual();
  PAux =  PAux->PSeguent;
 }
}

int tConjunt::DecrementarVitalitatActual(int N)
{
 if(PActual != NULL)
 {
  return(PActual->actual.DecrementarVitalitat(N));
 }
}

int tConjunt::RegaletActual()
{
 if(PActual != NULL)
 {
  return(PActual->actual.Regal());
 }
}

word tConjunt::ScoreActual()
{
 if(PActual != NULL)
 {
  return(PActual->actual.Puntuacio());
 }
 else return 0;
}

int tConjunt::SpriteActual()
{
 if(PActual != NULL)
 {
  return(PActual->actual.SpriteActual());
 }
}


void tConjunt::RetornarOffsetActual(int *X,int *Y)
{
 if(PActual != NULL)
 {
  (*X)=PActual -> offsetx;
  (*Y)=PActual -> offsety;
 }
}

int tConjunt::DimensioMax()
{
 int Max=8;
 int SpriteAmbDimensioMax;

 Reset();

 while(PActual != NULL)
 {
  if(Sprites[PActual->actual.SpriteActual()].dimx>Max)
  {
   SpriteAmbDimensioMax = PActual->actual.SpriteActual();
   Max = Sprites[PActual->actual.SpriteActual()].dimx;
  }
  PActual = PActual -> PSeguent;
 }

 Reset();

 return(SpriteAmbDimensioMax);

}

int tConjunt::ActualEsNul()
{
 return (PActual == NULL);
}

int tConjunt::ConjuntEsNul()
{
 return ((OBJECTES == NULL));
}

void tConjunt::Reset()
{
 PActual = OBJECTES;
}


void tConjunt::EliminarActual()
{
 PObjectes PAnterior;

 if((PActual != NULL)&&(OBJECTES != NULL))
 {
    if(PActual == OBJECTES)
    {
     OBJECTES = PActual -> PSeguent; // Enlla�em
     PAnterior = PActual;

     PActual = PActual -> PSeguent;
     delete PAnterior;  // Falla ?

    }
    else
    {
     PAnterior = OBJECTES;

     while(PAnterior->PSeguent != PActual) PAnterior = PAnterior -> PSeguent;
     PAnterior -> PSeguent = PActual -> PSeguent;
     PAnterior = PActual;

     PActual = PActual -> PSeguent;
     delete PAnterior;

    }

 }


}

int tConjunt::EsActiu()
{
 return(Actiu != 0);
}

int tConjunt::EsInvencible()
{
 if(PActual != NULL) return(PActual->actual.EsInvencible());
 return 0;
}



tConjunt::~tConjunt()
{
 PObjectes actual,anterior;

 if((actual = OBJECTES)!=NULL)
 {
  do{

   anterior = actual;
   actual = actual -> PSeguent;
   delete anterior;

  }while(actual != NULL);
 }

 OBJECTES = PActual = NULL;
}

