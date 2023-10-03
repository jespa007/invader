#include "effects.h"
#include "grafics.h"
#include "stdlib.h"



// EFFECTES DE ESTRELLES 2D


// DirX = 1 (De Esquerre a Dreta) DirX=-1 (De Dreta a Esquerre)

int DirX = 1, DirY = 0;

struct {

 int x, y;
 char Plane;

} Star2D[ NBR_STARS ];



void DeleteStars()

{

 int x, y ,i;

 for( i = 0; i < NBR_STARS; i++ )
  if((Star2D[i].x<320)&(Star2D[i].x>=0)&(Star2D[i].y<200)&(Star2D[i].y>=0))
  PutPixel( Star2D[ i ].x, Star2D[ i ].y, 0 );

}

/*
void DeleteStarsX( byte page )

{

 int i;

 for( i = 0; i < NBR_STARS; i++ )

  PutPixelX( Star2D[ i ].x, Star2D[ i ].y, 0 ,page);

}

*/

void MoveStars(void)

{

 int i;
 for( i = 0; i < NBR_STARS; i++ )

 {
  Star2D[ i ].x += ( Star2D[ i ].Plane >> 1 ) * DirX + DirX;
  Star2D[ i ].y += ( Star2D[ i ].Plane >> 1 ) * DirY + DirY;
  if( Star2D[ i ].x > MaxX || Star2D[ i ].x < MinX ||
      Star2D[ i ].y > MaxY || Star2D[ i ].y < MinY )
  {

   switch( DirX )
   {
    case -1: Star2D[ i ].x = MaxX; break;
    case 1: Star2D[ i ].x = MinX; break;
    case 0: Star2D[ i ].x = ( rand() % (MaxX-MinX) ) + MinX;
   }

   switch( DirY )
   {
    case -1: Star2D[ i ].y = MaxY;break;
    case 1: Star2D[ i ].y = MinY;break;
    case 0: Star2D[ i ].y = ( rand() % (MaxY-MinY) ) + MinY;
   }

   Star2D[ i ].Plane = rand() % 16;
  }
 }
}


void DrawStars( )
{
 int i;

 for( i = 0; i < NBR_STARS; i++ )
 {

  if((Star2D[i].x<320)&(Star2D[i].x>=0)&(Star2D[i].y<200)&(Star2D[i].y>=0))
  PutPixel( Star2D[ i ].x, Star2D[ i ].y, Star2D[ i ].Plane + 16);

 }
}


/*
void DrawStarsX(byte page )

{
 int i;
 for( i = 0; i < NBR_STARS; i++ )

 {

  PutPixelX( Star2D[ i ].x, Star2D[ i ].y, Star2D[ i ].Plane + 16 ,page);

 }

}




void Estrelles_2DX(byte page )

{

 InitStars();
 do {


  DeleteStarsX(page);

  MoveStars();

  DrawStarsX(page);

  delay(25);

 } while( !kbhit() );
 getch();
}
*/


void InitStars( void )
{

 int i;
 for( i = 0; i < NBR_STARS; i++ )
 {

  Star2D[ i ].x = ( rand() % (MaxX-MinX) ) + MinX;
  Star2D[ i ].y = ( rand() % (MaxY-MinY) ) + MinY;
  Star2D[ i ].Plane = rand() % 16;

 }
}


void Estrelles2D()
{

 ClearScreen(NEGRE);

 InitStars();

 do
 {

  DeleteStars();
  MoveStars();
  DrawStars();
 // Flip_VScreen(VIDEO);
 // WaitVRetrace();

 } while( !kbhit() );
 getch();

}







/*- EFECTES ESTRELLES 3D-*/


 typedef struct
 {
  int X,Y,Z;
 }Star3D;


 Star3D Stars[maxstars+1];
 Star3D Pos3d[maxstars+1];



void Setup(void)
{
 // Inicialitza les estrelles aleatoriement.

 unsigned int Loop;
 for(Loop=1;Loop<=maxstars;Loop++)
 {
  Stars[Loop].X=rand()%320-160;// Valors de -160 a +160.
  Stars[Loop].Y=rand()%200-100;// Valors de -100 a +100.
  Stars[Loop].Z=Loop;
 }
}


void Calc(void)
{
 // Converteix 3D => 2D

 unsigned int Loop;
 for(Loop=1;Loop<=maxstars;Loop++)
 {
  Pos3d[Loop].X=Stars[Loop].X*100/Stars[Loop].Z+160;
  Pos3d[Loop].Y=Stars[Loop].Y*100/Stars[Loop].Z+100;
 }
}

void Moure_Estrelles(void)
{
 unsigned int Loop;
 for(Loop=1;Loop<=maxstars;Loop++)
 {
  Stars[Loop].Z=Stars[Loop].Z-4;
  if(Stars[Loop].Z<1) Stars[Loop].Z=Stars[Loop].Z+Loop+4;
 }

}

void Dibuixar_Estrelles(word VSCREEN)
{
 unsigned int Loop,X,Y;
 for(Loop=1;Loop<=maxstars;Loop++)
 {
  X=Pos3d[Loop].X;
  Y=Pos3d[Loop].Y;
  if((X>1)&(X<320)&(Y>1)&(Y<200))
  {
   if (Pos3d[Loop].X<1) Pos3d[Loop].X=Pos3d[Loop].X+160;
   if (Pos3d[Loop].X>320) Pos3d[Loop].X=Pos3d[Loop].X-160;
   if (Pos3d[Loop].Y<1) Pos3d[Loop].Y=Pos3d[Loop].Y+100;
   if (Pos3d[Loop].Y>200) Pos3d[Loop].Y=Pos3d[Loop].Y-100;

   if(Stars[Loop].Z>400) PutPixel(X,Y,5); else
   if(Stars[Loop].Z>300) PutPixel(X,Y,6); else
   if(Stars[Loop].Z>200) PutPixel(X,Y,7); else
   if(Stars[Loop].Z>100) PutPixel(X,Y,8); else
   PutPixel(X,Y,9);
  }
 }
}

/*
void Estrelles3D(word VSCREEN)
{

 ClearScreen(NEGRE,VSCREEN);

 ModificarColorPaleta(0,0,0,5);
 ModificarColorPaleta(10,10,20,6);
 ModificarColorPaleta(20,20,30,7);
 ModificarColorPaleta(30,30,50,8);
 ModificarColorPaleta(50,50,60,9);

 Setup();
 Dibuixar_Estrelles(VSCREEN);
 Calc();
 do{
    Calc();
    Dibuixar_Estrelles(VSCREEN);
    Flip_VScreen(VIDEO,VSCREEN);
    WaitVRetrace();

    Moure_Estrelles();
    ClearScreen(NEGRE,VSCREEN);

   }while(!kbhit());

 getch();


}
*/

/*- EFECTE DE FOC -*/

/*
static int ytab[319]; // Ve a ser unes 320 posicions.//


void mk_ytab(void)
{
 int y;
 for(y=0;y<319;y++) ytab[y]= y*320;

}

void CrearPaletaFoc(char index_i,char vermell_i,char verd_i,char blau_i,char index_f,char vermell_f,char verd_f,char blau_f)
{
// Crea un degradat de paleta per la funci¢ FOC. "i" = inicial, "f" = final i "inc" = increment //

 unsigned char index;
 unsigned char max = (index_f - index_i);
 float inc_vermell,inc_verd,inc_blau;

 ModificarColorPaleta(vermell_i,verd_i,blau_i,index_i);
 ModificarColorPaleta(vermell_f,verd_f,blau_f,index_f);
 inc_vermell=(vermell_f-vermell_i)/((float)max);
 inc_verd=(verd_f-verd_i)/((float)max);
 inc_blau=(blau_f-blau_i)/((float)max);

 for(index = 1;index < max;index++) ModificarColorPaleta((vermell_i+inc_vermell*index),(verd_i+inc_verd*index),(blau_i+inc_blau*index),(index_i+index));
 

}



void cll(unsigned char *vbuffer)
{
 // Posa 320 linies linees a negre.(0)//
 memset(vbuffer+63680,0,320);
}


void set_hot(unsigned char *vbuffer)
{
 int x;
 cll(vbuffer);// Neteja la linia per a la pr¢xima volta. //
 for(x=0;x<319;x++)
 {
  if(random(100)<50)vbuffer[ytab[199]+x]=63;
 }
}

unsigned char average(int x,int y,unsigned char *vbuffer)
{
// foo = (int)(0+24+63+24+0+0+0)/7//
 unsigned char ave_color;
 unsigned char ave1,ave2,ave3,ave4,ave5,ave6,ave7;

 ave1=vbuffer[ytab[y+1]+x];
 ave2=vbuffer[ytab[y-1]+x];
 ave3=vbuffer[ytab[y]+x+1];
 ave4=vbuffer[ytab[y]+x-1];
 ave5=vbuffer[ytab[y]+x+2];
 ave6=vbuffer[ytab[y]+x-2];
 ave7=vbuffer[ytab[y]+x];

 ave_color=(ave1+ave2+ave3+ave4+ave5+ave6+ave7)/7;
 return(ave_color);
}

void mk_lines(unsigned char *vbuffer)
{
 int x,y;
 for(x=0;x<319;x++)
 {
  for(y=199;y>123;y--) vbuffer[ytab[y-1]+x]=average(x,y,vbuffer);
 }
}


void Foc(byte far *buffer1)
{

 tpaleta paleta1;

 // Inicialitzam el vector ytab[].


 mk_ytab();

 // Assignem memoria.

// ClearScreen(NEGRE,FP_SEG(buffer1));

 ClearScreen(NEGRE,VIDEO);

 GetPalette(paleta1,0,255);

 CrearPaletaFoc(0,0,0,0,63,63,63,100);

 randomize();
 do
 {
  set_hot(buffer1);
  mk_lines(buffer1);
  Flip_VScreen(VIDEO,FP_SEG(buffer1),63360);
 }while(!kbhit());

 getch();
 Lliurar_VSBuffer(buffer1);

}

*/
/*- EFECTE PLASMA -*/

/*

void Plasma(word VSCREEN)
{
 // Efecte de plasma //


 byte *buffer1=(byte *)MK_FP((word)VSCREEN,0);

 int XAnswer,YAnswer,ToAdd,X,Y,H;

 int SinArray[513],XValues[320];



 // Netegem memoria de video i buffer //

 ClearScreen(NEGRE,VIDEO);


 ClearScreen(NEGRE,VSCREEN);

 // Creacio de la taula de sinus. //

 for(X=0;X<=512;X++)
 {
  SinArray[X]=(int)(sin(rad(X)/512*360)*1024);
 }

 ToAdd=0;

 // Aqui comen‡a l' acci¢ //

 do
 {
  ToAdd=ToAdd+1;

  for(X=0;X<=319;X++)
  {
  // Obtenim els valors de les X //

   XValues[X]=(SinArray[((X<<2)+(ToAdd   ))&511]<<4)+(SinArray[((X<<2)+(ToAdd   ))&511]<<2)+
	      (SinArray[((X   )+(ToAdd<<2))&511]<<4)+(SinArray[((X   )+(ToAdd<<2))&511]<<3)+(SinArray[((X   )+(ToAdd<<2))&511]<<2)+(SinArray[((X   )+(ToAdd<<2))&511]<<1)+
	      (SinArray[((X>>2)+(ToAdd>>2))&511]<<1)+(SinArray[((X>>2)+(ToAdd>>2))&511]<<4)+(SinArray[((X>>2)+(ToAdd>>2))&511]<<5);

  }
  for(Y=0;Y<=199;Y++)
  {
  // Resposta de la Y, segons els vlors de X //

    YAnswer=(SinArray[((Y<<3)+(ToAdd   ))&511]<<5)+(SinArray[((Y<<3)+(ToAdd   ))&511]<<3)+
	    (SinArray[((Y   )+(ToAdd<<3))&511]<<5)+(SinArray[((Y   )+(ToAdd<<3))&511]<<3)+
	    (SinArray[((Y   )+(ToAdd>>3))&511]<<4)+(SinArray[((Y   )+(ToAdd>>3))&511]<<2);

   for(X=0;X<=319;X++)
   {
   //  Resposta de les X segons el valor de les Y //

     XAnswer=XValues[X];

     buffer1[(Y<<8)+(Y<<6)+X]=(XAnswer+YAnswer)>>10;

   }
  }
 Flip_VScreen(VIDEO,VSCREEN);

 }while(!kbhit());
 Lliurar_VSBuffer(buffer1);
 getch();
}

*/
/*- TRANSFORMACIONS -*/

/*

void TransformarBLOCK(byte far*DEST,byte far*ORG,word far *TFM,word L,byte tipus)
{


 // Sabent la dimensio (L) i el tipus Transformem...

 word x,y,d=5,Rc,Px,Py,Pz,Iz,Ix,Iy,D,Qz,Qy,Qx,Rs;
 byte m=2;

 switch(tipus)
 {



  case CapgirarY:

  // Efecte aigua. (Capgirar eix de les Y).

   for(y=0;y < L;y++)
   {
    for(x=0;x< L;x++)
    {
     TFM[y*L+x] = (L-1)*(L-1) - (y*(L-1)+x);
    }
   }

   for(y=0;y<=(L)*(L)-1;y++) DEST[y]=ORG[TFM[y]];// La mateixa DESTI mateix que ORG per¢ transformat.

  
   break;
 

  case CapgirarX:

  // Effecte Mirall (Capgirar eix de les X).

   for(y=0; y < L ;y++)
   {
    for(x=0;x < L;x++)
    TFM[y*L+x]=y*L+L-1-x; // La mateixa DESTI mateix que ORG per¢ transformat.
   }
   for(y=0;y<=(L)*(L)-1;y++) DEST[y]=ORG[TFM[y]];
   break;


  case CapgirarXY:

  // Effecte (Capgirar eix de les X i la Y).

   for(y=0;y<=L*L-1;y++)
     TFM[y]=L*L-y-1; // La mateixa DESTI mateix que ORG per¢ transformat.

   for(y=0;y<=(L)*(L)-1;y++) DEST[y]=ORG[TFM[y]];
   break;

  case Augmentar:

  // Effecte de Augment. (varia la constant m per augmentar.(  m  =  augment)

   for(y=0;y < L;y++)
   {
    for(x=0;x < L;x++)
     TFM[y*L+x]=(y/m)*L+(x/m); // La mateixa DESTI mateix que ORG per¢ transformat.
   }
   for(y=0;y<=(L)*(L)-1;y++) DEST[y]=ORG[TFM[y]];// La mateixa DESTI mateix que ORG per¢ transformat.
   break;

  case Lents:

  // Effecte de Lents.

  Rc=L/2;
  Rs=sqrt(Rc*Rc+d*d);

  for(y=0;y<=L-1;y++)
  {
   for(x=0;x<=L-1;x++)
   {
    Px=(x-Rc);
    Py=(y-Rc);
    if((Rc*Rc)>(Px*Px)+(Py*Py)) // Est… dins el cercle?
    {

     // Si!!! Llabors, transforma...

     Qx=Px;
     Qy=Py;
     D=d*d-((Px*Px)+(Py*Py)-(Rc*Rc));
     Qz=1+sqrt(D);
     Ix=((d)/(Qz+d))*Qx;
     Iy=((d)/(Qz+d))*Qy;
     Iz=0;

     TFM[(L/2+Px)+(L/2+Py)*L]=(L/2+Iy)*L+(L/2+Ix);
     TFM[(L/2-Px)+(L/2+Py)*L]=(L/2+Iy)*L+(L/2+Ix);
     TFM[(L/2-Px)+(L/2-Py)*L]=(L/2+Iy)*L+(L/2+Ix);
     TFM[(L/2+Px)+(L/2-Py)*L]=(L/2+Iy)*L+(L/2+Ix);
    }
    else
    {

    // No!!! Llabors no transforma.

     TFM[(x)+L*(y)]=(x)+L*(y);
    }
   }
  }
  for(y=0;y<=(L)*(L)-1;y++) DEST[y]=ORG[TFM[y]];// La mateixa DESTI mateix que ORG per¢ transformat.
 }
}



//  ÚÄÄÄÄÄÄúúÄÄúÄ¿
//  ³ CROSSFADE   ³      
//  ÀÄÄÄÄÄúúúúÄÄúúÄÙ     
  


int ExisteixCombinacio(byte *p1,byte *p2,byte color1,byte color2,byte *origen,byte *desti,int max_tamany,byte *posicio)
{

 int i=0;

 while((i<max_tamany) && ! ( ColorIgual(origen,p1,i,color1) && ColorIgual(p2,desti,color2,i) ))    i++;

 if(ColorIgual(origen,p1,i,color1) && ColorIgual(p2,desti,color2,i))
 {

  (*posicio) = i;
  return 1;

 }

 return 0;

}



void IntroduirCombinacio(int posicio,byte *origen,byte *desti,byte R1,byte R2,byte G1,byte G2,byte B1,byte B2)
{

  origen[posicio*3] = R1;
  origen[posicio*3+1] = G1;
  origen[posicio*3+2] = B1;

  desti[posicio*3] = R2;
  desti[posicio*3+1] = G2;
  desti[posicio*3+2] = B2;

}




int InitFade(byte *S2, byte *S1,byte *S3, byte *p2, byte *p1, byte *desti,byte *origen)
{
 // Inicialitza un CrossFade... (Retorna 0 si no s'ha pogut acabar amb exit)!

 int y,x,t = 1; // N§ de pixel (representa)
 byte posicio;

 byte color1;
 byte color2;
 
 PaletaNegre(origen,0,255);
 PaletaNegre(desti,0,255);



  for(y=0;y<200;y++)
  { 
   for(x=0;x<320;x++)
   {

   // Agafem el color per cada imatge...

    color1 = S1[(y << 8) + (y << 6) + x];
    color2 = S2[(y << 8) + (y << 6) + x];

    if(ExisteixCombinacio(p1,p2,color1,color2,origen,desti,t,&posicio))
    {

      S3[(y << 8) + (y << 6)+x] = posicio; // Combinaci¢ trobada (posicio).

    }
    else
    {

     if(t > MAX_COMB)
     {
      return 0; // error!, hem superat el limit m…xim de combinacions.
     }

     IntroduirCombinacio(t,origen,desti,p1[color1*3],p2[color2*3],p1[color1*3+1],p2[color2*3+1],p1[color1*3+2],p2[color2*3+2]);

     S3[(y << 8) + (y << 6) + x] = t; // Nova combinaci¢ introduida.

     t++; // Pr•xima combinacio.

    }
    
   } 

  }
 

  // Ja tenim inicialitzada les paletes, SCREENS, etc..

 return 1; //OK!

}


void  CrossFade(byte *desti,byte *origen)
{
 tpaleta temp;
 int y=0,x=0;

 CopiaPaleta(temp,origen,0,255);


 for(y=0;y<63;y++)
 {
  for(x=0;x<768;x++)
  {
   if(temp[x]<desti[x]) temp[x]++;
   if(temp[x]>desti[x]) temp[x]--;
  }
  SetPalette(temp,0,255);
  WaitVRetrace();

 }

}

*/