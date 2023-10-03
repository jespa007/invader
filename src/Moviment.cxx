#include "moviment.h"
#include "Teclat.h"

#include <math.h>   // sin,cos,tangent,etc...


//#include "Ruta.cc"



tPosicio *moviments[MAX_MOVIMENTS];  // POS =>  X(Y) o Y(X)



int InicialitzarMoviments()
{
 float m=0;
 int i,j,k;

 // Inicialitzar Rectes;

 // Entrada de dades... uffff!

 for(i=0;i<(MAX_MOVIMENTS);i++)
 {
  if((moviments[i] = (tPosicio *)malloc(MAX_POSICIONS*sizeof(tPosicio))) == NULL) return 0;
 }

 for(i=0;i<word(MAX_RECTES/2)+1;i++)
 {
  k=0;
  j=0;

  while(j<(MAX_POSICIONS))
  {

     moviments[i][j].y=word((k+1)*m);
     moviments[i][j].x=(k+1);
     moviments[MAX_RECTES-i-1][j].y=(k+1);
     moviments[MAX_RECTES-i-1][j].x=word((k+1)*m);
     k++;
     j++;

  }
 
  m+=PENDENT;

 }
 
 moviments[MAX_RECTES][0].x=0;
 moviments[MAX_RECTES][0].y=0;
 moviments[MAX_RECTES][1].x=1;
 moviments[MAX_RECTES][1].y=1;
 moviments[MAX_RECTES][2].x=2;
 moviments[MAX_RECTES][2].y=2;
 moviments[MAX_RECTES][3].x=3;
 moviments[MAX_RECTES][3].y=3;
 moviments[MAX_RECTES][4].x=4;
 moviments[MAX_RECTES][4].y=3;
 moviments[MAX_RECTES][5].x=5;
 moviments[MAX_RECTES][5].y=4;
 moviments[MAX_RECTES][6].x=6;
 moviments[MAX_RECTES][6].y=4;
 moviments[MAX_RECTES][7].x=7;
 moviments[MAX_RECTES][7].y=4;
 moviments[MAX_RECTES][8].x=8;
 moviments[MAX_RECTES][8].y=4;

 moviments[MAX_RECTES][9].x=9;
 moviments[MAX_RECTES][9].y=5;
 moviments[MAX_RECTES][10].x=10;
 moviments[MAX_RECTES][10].y=5;
 moviments[MAX_RECTES][11].x=11;
 moviments[MAX_RECTES][11].y=5;
 moviments[MAX_RECTES][12].x=12;
 moviments[MAX_RECTES][12].y=5;
 moviments[MAX_RECTES][13].x=13;
 moviments[MAX_RECTES][13].y=5;
 moviments[MAX_RECTES][14].x=14;
 moviments[MAX_RECTES][14].y=6;
 moviments[MAX_RECTES][15].x=15;
 moviments[MAX_RECTES][15].y=6;

 for(j=0;j<MAX_POSICIONS;j++)
 {
  moviments[MAX_RECTES+1][j].x = j;
  moviments[MAX_RECTES+1][j].y = (6-moviments[MAX_RECTES][MAX_POSICIONS-j-1].y);
 }


 moviments[MAX_RECTES+2][0].x=0;
 moviments[MAX_RECTES+2][0].y=0;
 moviments[MAX_RECTES+2][1].x=1;
 moviments[MAX_RECTES+2][1].y=2;
 moviments[MAX_RECTES+2][2].x=2;
 moviments[MAX_RECTES+2][2].y=4;
 moviments[MAX_RECTES+2][3].x=3;
 moviments[MAX_RECTES+2][3].y=6;
 moviments[MAX_RECTES+2][4].x=4;
 moviments[MAX_RECTES+2][4].y=7;
 moviments[MAX_RECTES+2][5].x=5;
 moviments[MAX_RECTES+2][5].y=8;
 moviments[MAX_RECTES+2][6].x=6;
 moviments[MAX_RECTES+2][6].y=9;
 moviments[MAX_RECTES+2][7].x=7;
 moviments[MAX_RECTES+2][7].y=9;
 moviments[MAX_RECTES+2][8].x=8;
 moviments[MAX_RECTES+2][8].y=9;
                     
 moviments[MAX_RECTES+2][9].x=9;
 moviments[MAX_RECTES+2][9].y=9;
 moviments[MAX_RECTES+2][10].x=10;
 moviments[MAX_RECTES+2][10].y=8;
 moviments[MAX_RECTES+2][11].x=11;
 moviments[MAX_RECTES+2][11].y=7;
 moviments[MAX_RECTES+2][12].x=12;
 moviments[MAX_RECTES+2][12].y=6;
 moviments[MAX_RECTES+2][13].x=13;
 moviments[MAX_RECTES+2][13].y=4;
 moviments[MAX_RECTES+2][14].x=14;
 moviments[MAX_RECTES+2][14].y=2;
 moviments[MAX_RECTES+2][15].x=15;
 moviments[MAX_RECTES+2][15].y=0;
                     
// Cercles amb presisio

 return 1; //Ok !


}


int HiHaInterseccio(int x1,int y1,int x2,int y2,int dim1,int dim2)
{

 int ALT,AMPLADA,dimx1,dimx2,dimy1,dimy2;



 switch(dim1)
 {
  case 8:x1+=2;y1+=1;dimx1=6;dimy1=6;break;
  case 16:x1+=3;y1+=1;dimx1=10;dimy1=14;break;
  case 32:dimx1=28;dimy1=30;break;
  case 64:dimx1=56;dimy1=59;
 }

 switch(dim2)
 {
  case 8:x2+=2;y2+=1;dimx2=6;dimy2=6;break;
  case 16:x2+=3;y2+=1;dimx2=10;dimy2=14;break;
  case 32:dimx2=28;dimy2=30;break;
  case 64:dimx2=56;dimy2=59;
 }



 if(y2>y1) ALT = dimy1; else ALT = dimy2;
 if(x2>x1) AMPLADA = dimx1;else AMPLADA = dimx2;

 return((abs(x1-x2)<AMPLADA)&&(abs(y1-y2)<ALT));

}


int DireccioMeva(int x,int y,int myposx,int myposy,int *xpos,int *ypos,int dimensio)
{
 int destx = (myposx+8) - (x + (dimensio >> 1));
 int desty = (myposy+8) - (y + (dimensio >> 1));
 float div;


 if((destx>=0)&&(desty>=0)) {(*xpos)=1;(*ypos)=1;}
    else if((destx>=0)&&(desty<0)) {(*xpos)=1;(*ypos)=-1;}
         else if((destx<0)&&(desty<0)) {(*xpos)=-1;(*ypos)=-1;}
              else if((destx<0)&&(desty>=0)) {(*xpos)=-1;(*ypos)=1;}


 destx = abs(destx);
 desty = abs(desty);



 if(destx >= desty) // y/x
 {

  if(destx != 0) div=(float)desty/destx;
  else return 0;
 
  if((div>=0.0)&&(div<0.2)) return(0);
  else if((div>=0.2)&&(div<0.4)) return(2);
       else if((div>=0.4)&&(div<0.6)) return(4);
            else if((div>=0.6)&&(div<0.8)) return(6);
                 else if((div>=0.8)&&(div<1.0)) return(8);
                      else if((div>=1.0)) return(10);
  
 }
 else // x/y
 {

  if(desty != 0) div=(float)destx/desty;
  else return 0;

  if((div>=0.0)&&(div<0.2)) return(20);
    else if((div>=0.2)&&(div<0.4)) return(18);
         else if((div>=0.4)&&(div<0.6)) return(16);
              else if((div>=0.6)&&(div<0.8)) return(14);
                   else if((div>=0.8)&&(div<1.0)) return(12);
  }

 return 0;
}


int ElMeuMoviment(int x,int y,int myposx,int myposy,int dimensio)
{
 int xpos,ypos,D;

  D=DireccioMeva(x,y,myposx,myposy,&xpos,&ypos,dimensio);
 
  if((xpos>=0)&&(ypos>=0))
  {
   switch(D)
   {
    case 0: return 10;
    case 2: return 9;
    case 4: return 8;
    case 6: return 7;
    case 8: return 6;
    case 10: return 5;
    case 12: return 4;
    case 14: return 3;
    case 16: return 2;
    case 18: return 1;
    case 20: return 0;
   }
  }
  if((xpos>=0)&&(ypos<0))
  {
   switch(D)
   {
    case 0: return 10;
    case 2: return 11;
    case 4: return 12;
    case 6: return 13;
    case 8: return 14;
    case 10: return 15;
    case 12: return 16;
    case 14: return 17;
    case 16: return 18;
    case 18: return 19;
    case 20: return 20;
   }

  }
  if((xpos<0)&&(ypos<0))
  {
   switch(D)
   {
    case 0: return 30;
    case 2: return 29;
    case 4: return 28;
    case 6: return 27;
    case 8: return 26;
    case 10: return 25;
    case 12: return 24;
    case 14: return 23;
    case 16: return 22;
    case 18: return 21;
    case 20: return 20;
   }

  }
  if((xpos<0)&&(ypos>=0))
  {
   switch(D)
   {
    case 0: return 30;
    case 2: return 31;
    case 4: return 32;
    case 6: return 33;
    case 8: return 34;
    case 10: return 35;
    case 12: return 36;
    case 14: return 37;
    case 16: return 38;
    case 18: return 39;
    case 20: return 0;
   }

  }


 return 0;
}

tMoviment::tMoviment()
{
 PARTS = NULL;
 PActual = NULL;
 N_Moviments = M_Actual = P_Actual = x = y = 0;
}


void tMoviment::copia(const tMoviment &MOV)
{
 PMoviment actual,anterior,nou;

 if((actual = MOV.PARTS) != NULL)
 {

   anterior = NULL;

   do{

     nou = new tM;
     nou -> Moviment = actual -> Moviment;
     nou -> xpos = actual -> xpos;
     nou -> ypos = actual -> ypos;
     nou -> v = actual -> v;
     nou -> condicio = actual -> condicio;
     nou -> vegades = actual -> vegades;

//     if(MOV.PActual == actual) PActual = nou; // Volem que seguiexi la mateixa ruta no ?

     if(anterior == NULL) // 1st.
     {
       PActual = PARTS = nou;
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
   PARTS = NULL;
 }


}


tMoviment & tMoviment::operator = (tMoviment const &S)
{

 
 // Destrucci¢...

 this->tMoviment::~tMoviment();

 // Copia de la nova part...

 this->copia(S);

 N_Moviments = S.N_Moviments;
 M_Actual = S.M_Actual;
 P_Actual = S.P_Actual;
 x = S.x;
 y = S.y;



 return (*this);

}


int tMoviment::RetornarSigneY()
{
 if(!EsNul())
 {
  return(PActual -> ypos);
 }
}





void tMoviment::AfegirPart(int MOVIMENT,int XPOS,int YPOS,int condicio,int VELOCITAT,int N_VEGADES)
{
 byte Motiu0[]={"No tens prou mem•ria...\0"};
 PMoviment PNou = NULL;

 PNou = (PMoviment) new tM;

 if(PNou == NULL) Quit(Motiu0);

 PNou -> Moviment = MOVIMENT;
 PNou -> xpos = XPOS;
 PNou -> ypos = YPOS;
 PNou -> v = VELOCITAT;
 PNou -> vegades = N_VEGADES;
 PNou -> condicio = condicio;
 PNou -> PSeguent = NULL;

 if(PARTS == NULL) // 1st
 {
  PARTS = PActual = PNou;
 }
 else
 {
  PActual = PARTS;
  while(!(PActual->PSeguent == NULL)) PActual = PActual -> PSeguent;
  PActual -> PSeguent = PNou;

  PActual = PARTS;
 }



}



int tMoviment::TransicioMoviment()
{
	if(PActual != NULL)
	{
		 if((M_Actual == PActual->vegades-1)&&(PActual->PSeguent != NULL))
		 {
		  return(PActual->ypos != PActual->PSeguent->ypos);
		 }
	}

 return 0;
}

int tMoviment::TransicioPosicio(int velocitat)
{
	if(PActual != NULL)
	{
		 if((M_Actual == PActual->vegades-1)&&(PActual->PSeguent != NULL)&&((P_Actual+velocitat)>16))
		 {
		  return(PActual->ypos != PActual->PSeguent->ypos);
		 }
	}


 return 0;
}



void tMoviment::EntrarCoordenades(int X,int Y)
{
 x = X;
 y = Y;
}



void tMoviment::SeguentPosicio(int *X,int *Y,int MYPOSX,int MYPOSY,int velx,int vely,int Sprite)
{
 int dimensio = Sprites[Sprite].dimx;
 int offsetx,offsety;

 if(!EsNul())
 {


  if((P_Actual < MAX_POSICIONS)&&(PActual -> condicio != AUTO2)&&(PActual -> condicio != MANUAL))
  {

    offsetx = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
    offsety = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));

    if(velx!=0) (*X) = offsetx;
    if(vely!=0) (*Y) = offsety; 
    P_Actual += ((velx)*(PActual -> v));
  }
  else
  {

    if(vely!=0) y+=(moviments[PActual->Moviment][MAX_POSICIONS-1].y*(PActual->ypos)+(moviments[PActual->Moviment][0].y*(PActual->ypos)));
    if(velx!=0) x+=(moviments[PActual->Moviment][MAX_POSICIONS-1].x*(PActual->xpos)+(moviments[PActual->Moviment][0].x*(PActual->xpos)));

    M_Actual++;
    P_Actual = 0;
   


   switch(PActual -> condicio)
   {
    case DETECTA_POSX1: if(((*X)+(dimensio>>1) > MYPOSX))
                       {
                        PActual = PActual -> PSeguent;
                       }
                  if(M_Actual < PActual -> vegades)
                {
                 N_Moviments++;


                 if(velx!=0)(*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
                 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
                 P_Actual += ((velx)*(PActual -> v));

                }
                else
                {
                 PActual = PActual -> PSeguent;
                 M_Actual=0;
                 N_Moviments++;

                 if(velx!=0) (*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
                 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
                 P_Actual += ((velx)*(PActual -> v));

                }
                break;

    case DETECTA_POSX2: if(((*X)+(dimensio>>1) < MYPOSX))
                       {
                        PActual = PActual -> PSeguent;
                       }

    case NORMAL:if(M_Actual < PActual -> vegades)
                {
                 N_Moviments++;


                 if(velx!=0)(*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
                 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
                 P_Actual += ((velx)*(PActual -> v));

                }
                else
                {
					 if((PActual = PActual -> PSeguent) != NULL)
					 {
						 M_Actual=0;
						 N_Moviments++;

						 if(velx!=0) (*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
						 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
						 P_Actual += ((velx)*(PActual -> v));
					 }

                }
                break;



    case AUTO1:if(!(PActual -> vegades==INFINIT))
               {
                if(M_Actual < PActual -> vegades)
                {
                 PActual -> Moviment = DireccioMeva((*X)+(dimensio>>2),(*Y)+(dimensio>>2),MYPOSX,MYPOSY,&(PActual->xpos),&(PActual->ypos),Sprites[Sprite].dimx >> 1);
                 N_Moviments++;

                 if(velx!=0) (*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
                 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
                 P_Actual += ((velx)*(PActual -> v));

                }
                else
                {
					
                 if((PActual = PActual -> PSeguent) != NULL)
				 {
					 M_Actual=0;P_Actual=0;
					 N_Moviments++;

					 if(velx!=0) (*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
					 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
					 P_Actual += ((velx)*(PActual -> v));

				 }

                }
               }
               else
               {
                 PActual -> Moviment = DireccioMeva((*X)+(dimensio>>2),(*Y)+(dimensio>>2),MYPOSX,MYPOSY,&(PActual->xpos),&(PActual->ypos),Sprites[Sprite].dimx);

                 N_Moviments++;

                 if(velx!=0) (*X) = x + (moviments[PActual->Moviment][P_Actual].x*(PActual->xpos));
                 if(vely!=0)(*Y) = y + (moviments[PActual->Moviment][P_Actual].y*(PActual->ypos));
                 P_Actual += ((velx)*(PActual -> v));


               }
               break;

    case AUTO2: if((((*X)+(dimensio>>1))<(MYPOSX+8))&&( ((*X)+(dimensio)) < ((AMPLADA_PANTALLA_JOC)) ) ) (*X) += velx;
                else if((((*X)+(dimensio>>1))>(MYPOSX+8))&&((*X)>=0)) (*X) -= velx;
                break;
    case MANUAL: if(TECLA_AMUNT&&((*Y)>0)) (*Y) -= 2;
                 if(TECLA_AVALL&&(((*Y)+dimensio)<ALTURA_PANTALLA_JOC-8)) (*Y) += 2;
                 if(TECLA_ESQUERRA&&((*X)>0)) (*X) -= 2;
                 if(TECLA_DRETA&&(((*X)+16)<AMPLADA_PANTALLA_JOC)) (*X) += 2;

    
   }
  }
 }
}

void tMoviment::Reset()
{
 PActual = PARTS;
}

int tMoviment::MovimentsActuals()
{
 return(N_Moviments);
}


int tMoviment::EsNul()
{
 return(PActual == NULL);
}

tMoviment::~tMoviment()
{
 PMoviment  PAnterior;

 if((PActual = PARTS) != NULL)
 {

  do{

   PAnterior = PActual;
   PActual = PActual -> PSeguent;
   delete PAnterior;

  }while(PActual!=NULL);

  PARTS = NULL;

 }

}


