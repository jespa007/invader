//#include "menu.cc"
#include "Invader.h"

//#include "intro.h"





////////////////////////////////////////////////////////////////////////////
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
//                                                                        //
////////////////////////////////////////////////////////////////////////////


                   /*-___________-*\__  �   �            �
  �       �     )-/                 \_)   �      �
    �            | (  DEFINICIONS    |_) �      �     �
 .         �    )-\                  /_)   �    �
   �   �           \*_-------------_*/



#ifdef __cplusplus
	#define __CPPARGS ...
#else
	#define __CPPARGS
#endif


#define INTR 0x1C    /* The clock tick interrupt */

#define FACIL    0
#define MITJANA  1
#define DIFICIL  2

#define MAX_VIDES 4






                  /*-_________________-*\__  �   �            �
  �       �     )-/                       \_)   �      �
    �            | (  DEFINICIO DE TIPUS  |_) �      �     �
 .         �    )-\                       /_)   �    �
   �   �           \*_------------------_*/



// typedef byte far tBloc[AMPLADA_BLOC*ALTURA_BLOC];

                  /*-____________________-*\__  �   �            �
  �       �     )-/                          \_)   �      �
    �            | (  CAP�ALERA DE FUNCIONS  |_) �      �     �
 .         �    )-\                          /_)   �    �
   �   �           \*_---------------------_*/




void interrupt ( *oldhandler)(__CPPARGS);
void interrupt SONIDOS(__CPPARGS);


//  �������������������Ŀ
//  �Estructures del joc�
//  ���������������������

int game();
void credits();
void gameover();

//  ������Ŀ
//  �Altres�
//  ��������




//  �����������������Ŀ
//  �Gestio de Sortida�
//  �������������������






                   /*-_______________-*\__  �   �            �
  �       �     )-/                     \_)   �      �
    �            | (  VARIABLES GLOBALS |_) �      �     � 
 .         �    )-\                     /_)   �    �
   �   �           \*_----------------_*/

 tImatge Blocs[MAX_BLOCS];
 byte *Mapa=NULL;

 tImatge Imatges[MAX_SPRITES]; // En aqui trobarem totes les imatges.
 tSprite Sprites[MAX_SPRITES]; // En aqui trobarem tots els sprites del joc.

 word BLOCINVERS[AMPLADA_BLOC*ALTURA_BLOC];




 /********************\
| VSCREENS NECESSARIES |
 \********************/

int Cheat = FALS;
int vides;
dword puntuacio=0;
dword maxima_puntuacio=0;
int dificultat = MITJANA;
word temps = 0;

byte  * BUFFER1 = NULL; 
byte  * BUFFER2 = NULL;
byte  * BUFFER3 = NULL;
byte  * BUFFER4 = NULL;

word VSCREEN1;
word VSCREEN2;
word VSCREEN3;
word VSCREEN4;

 /********************\
| PALETES NECESSARIES |
 \********************/


tpaleta paleta1,paleta2,paleta3;


                   /*-__________-*\__  �   �            �
  �       �     )-/                \_)   �      �
    �            | (  FUNCIO MAIN  |_) �      �     � 
 .         �    )-\                /_)   �    �
   �   �           \*_-----------_*/


//  �������������Ŀ
//  �Propi del joc�
//  ���������������

#include "Effects.cc"
#include "Text.cc"

#include "Teclado.c"      // Per JASM & BMP

#include "Ruta.cc"
//#include "Moviment.cc"
#include "Init.cc"
#include "Scroll.cc"
#include "Menu.cc"
#include "Conjunt.cc"


//#include "Part.cc"
//#include "Objecte.cc"

//#include "Test.cc"


#include "Stage1.cc"

void main(int argc,char *argv[])
{
 byte Motiu0[]={"Sortint OK...\0"};
 byte Motiu1[]={"No s'ha pogut inicialitzar \"INVADER\"...\0"};

 int i,j;
 int true = FALS;

 if(argc>1) if(!strcmp(argv[1],"invencible")) Cheat = TRUE;

 InitFons();

 /* Inicializa SMIX */

 InicialitzarDrivers();



 if(!InicialitzarEstructura()) Quit(Motiu1); // Estructura dels sprites,sons,buffers,lletres i blocs del mapa.


 SetMode13();



 if(!CarregarImatgeVScreen((byte *)&"grafics//TITUL.RAW",BUFFER1)) Quit(Motiu1);
 if(!CarregarImatgeVScreen((byte *)&"grafics//OPTIONS.RAW",BUFFER2)) Quit(Motiu1);



 ClearScreen(NEGRE,VIDEO);


 CarregarPaleta((byte *)&"grafics//paleta1.pal",paleta1);

 CopiaPaleta(paleta3,paleta1,0,255);

 paleta3[227*3] = 0;
 paleta3[227*3+1] = 0;
 paleta3[227*3+2] = 0;

 paleta3[16*3] = 0;
 paleta3[16*3+1] = 0;
 paleta3[16*3+2] = 0;

 paleta3[136*3] = 0;
 paleta3[136*3+1] = 0;
 paleta3[136*3+2] = 0;

 paleta3[159*3] = 0;
 paleta3[159*3+1] = 0;
 paleta3[159*3+2] = 0;

 paleta3[67*3] = 0;
 paleta3[67*3+1] = 0;
 paleta3[67*3+2] = 0;


 paleta3[15*3] = 63;
 paleta3[15*3+1] = 63;
 paleta3[15*3+2] = 63;

 PaletaNegre(paleta2,0,255);

/* save the old interrupt vector */
   oldhandler = getvect(INTR);

/* install the new interrupt handler */
   setvect(INTR, SONIDOS);

 vides = 3;

 if(SB) start_sound(sonidos[5],5,ON);


 SetPalette(paleta2,0,255);
 ClearScreen(NEGRE,VIDEO);


 Flip_VScreen(VIDEO,VSCREEN1);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VSCREEN1);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VIDEO);

 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VSCREEN1);
 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VIDEO);

 Visualitzar_Numero(8*11,0,puntuacio,7,0,VSCREEN1);
 Visualitzar_Numero(8*11,0,puntuacio,7,0,VIDEO);

 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VSCREEN1);
 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VIDEO);


 WaitVRetrace();
 FadeIn(paleta3,0,255);
/*
 do{
  VisualitzarPaleta();
 }while(!letras[DISPAR]);
*/
 do{

  Flip_VScreen(VIDEO,VSCREEN1);
  MostrarPunter();


  switch(i=menu())
  {
    
   case 0:
          OcultarPunter();
          if(SB)start_sound(sonidos[6],6,OFF);

           FadeOut(0,255);
          if(SB) stop_sound(5);

          
           switch(game())
           {
            case 1:credits();break;
            case 2:gameover();
           }
            
           if(SB) start_sound(sonidos[5],5,ON);
           if(!CarregarImatgeVScreen((byte *)&"grafics//TITUL.RAW",BUFFER1)) Quit(Motiu1);
           if(!CarregarImatgeVScreen((byte *)&"grafics//OPTIONS.RAW",BUFFER2)) Quit(Motiu1);
           Flip_VScreen(VIDEO,VSCREEN1);

                 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VSCREEN1);
                 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VIDEO);

                 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VSCREEN1);
                 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VIDEO);
        
                 Visualitzar_Numero(8*11,0,puntuacio,7,0,VSCREEN1);
                 Visualitzar_Numero(8*11,0,puntuacio,7,0,VIDEO);

                 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VSCREEN1);
                 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VIDEO);



           FadeIn(paleta3,0,255);
           break;
 
   case 1: if(SB) start_sound(sonidos[6],6,OFF);
           OcultarPunter();options();
           SetPalette(paleta2,0,255);

           Flip_VScreen(VIDEO,VSCREEN1);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VSCREEN1);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT,VIDEO);

 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VSCREEN1);
 OutText(190,0,"Maxima:\0",0,0,0,FONTMT,VIDEO);

 Visualitzar_Numero(8*11,0,puntuacio,7,0,VSCREEN1);
 Visualitzar_Numero(8*11,0,puntuacio,7,0,VIDEO);

 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VSCREEN1);
 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0,VIDEO);

           FadeIn(paleta3,0,255);
           break;
  }
 
 }while(i!=2);
 if(SB) start_sound(sonidos[6],6,OFF);

// SetPalette(paleta3,0,255);
 FadeOut(0,255);

 if(SB) stop_sound(6);
 if(SB) stop_sound(5);
 /* reset the old interrupt handler */
  setvect(INTR, oldhandler);


 Quit(Motiu0);
}









                   /*-________________________-*\__  �   �            �
  �       �     )-/                              \_)   �      �
    �            | (  IMPLEMENTACIO DE FUNCIONS  |_) �      �     � 
 .         �    )-\                              /_)   �    �
   �   �           \*_-------------------------_*/










void credits()
{
 byte *Nau=NULL;
 byte *Terra=NULL;
 byte *NauNodriu=NULL;
 char color;
 int x,v=15;
 int xnau = 110,xnaudown = FALS;
 int xterra=-220;
 int xnaunodriu = -234;
 int POSX,POSY,SCROLLY;
 int ypos=0, yscroll=1,i;
 byte Motiu0[]={"No s'ha pogut obrir \"credits.dat\"...\0"};
 byte Motiu1[]={"No s'ha pogut obrir \"credits.raw\"...\0"};
 byte Motiu2[]={"Mem�ria insuficient...\0"};
 byte Motiu3[]={"No s'ha pogut obrir \"Nau00.raw\"...\0"};
 byte Motiu4[]={"No s'ha pogut obrir \"terra.raw\"...\0"};
 byte Motiu5[]={"No s'ha pogut obrir \"terra1.raw\"...\0"};
 byte Motiu6[]={"No s'ha pogut obrir \"NauMare0.raw\"...\0"};
 byte escape = FALS;
 byte pres = FALS;


 FILE *fitxer = NULL;
 int up=0,j,true;
 int temps1 =0;



 color = 0;
 ClearScreen(NEGRE,VSCREEN2);


 CopiaPaleta(paleta2,paleta1,0,255);

 for(i=17;i<32;i++)
 {
  paleta2[i*3]=i*2-10;
  paleta2[i*3+1]=i*2-10;
  paleta2[i*3+2]=i*2-10;

 }

 paleta2[224*3] = 63;
 paleta2[224*3+1] = 63;
 paleta2[224*3+2] = 63;
 paleta2[128*3] = 0;
 paleta2[128*3+1] = 0;
 paleta2[128*3+2] = 63;


 x=0;

 if(!CarregarImatgeVScreen((byte *)&"grafics//SPACE0.RAW",BUFFER1)) Quit(Motiu5);

 if((NauNodriu=(byte *)malloc(230*200))==NULL) Quit(Motiu2);
 if( (fitxer = fopen("grafics//NauMare0.raw","rb")) == NULL) Quit(Motiu6);

 fread(NauNodriu,230*200,1,fitxer);

 fclose(fitxer);

 if(SB)
 {
  start_sound(sonidos[1],1,ON);
  start_sound(sonidos[22],22,ON);
 }
 temps = 0;

 SetPalette(paleta2,0,255);

 while(!(escape)&&temps < 1000)
 {
  Flip_VScreen(VSCREEN2,VSCREEN1);
  PutSprite(xnaunodriu,0,NauNodriu,230,200,0,0,319,199,COLOR_MASCARA,VSCREEN2);

  Flip_VScreen(VIDEO,VSCREEN2);
  delay(10);

  if(temps%5==0) xnaunodriu++;
  temps++;
  escape=letras[ESCAPE];
 }

 if(SB)
 {
  stop_sound(22);
  start_sound(sonidos[8],8,OFF);
 }

 SetPalette(paleta2,0,255);


 free(NauNodriu);

if(!escape)
{
 ClearScreen(NEGRE,VSCREEN1);
 ClearScreen(NEGRE,VSCREEN2);

 CarregarImatgeVScreen("grafics//enemic.raw",BUFFER1);
 InitStars(); // Setup Stars

  SetPalette(paleta2,0,255);
}

 while(!(escape)&& temps < 2000)
 {

   DeleteStars(VSCREEN2);
   MoveStars();
   DrawStars(VSCREEN2);

   if((temps == 1500) || (temps == 2000)) ClearScreen(NEGRE,VSCREEN2);
   Flip_VScreen(VSCREEN3,VSCREEN2);
   PutSprite(0,0,BUFFER1,320,200,0,0,320,200,227,VSCREEN3);

   if((temps >= 1000) && (temps<1200))
   {
    OutText(0,165,(byte *)&"  HAS GUANYAT UNA BATALLA \0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+MAX_ALTURA_TEXT,(byte *)&"  PERO NO LA GUERRA.\0",0,0,0,FONTMT,VSCREEN3);
    if(color<63) {ModificarColorPaleta(color,0,0,15);color++;}

   }

   if((temps>=1200) && (temps<1300))
   {
    OutText(0,165,(byte *)&"  HAS GUANYAT UNA BATALLA \0",4,0,0,FONTMT,VSCREEN3);
    OutText(0,165+MAX_ALTURA_TEXT,(byte *)&"  PERO NO LA GUERRA.\0",0,0,0,FONTMT,VSCREEN3);
    if(color>0) {ModificarColorPaleta(color,0,0,15);color--;}
   }


   if((temps >= 1300) && (temps<1800))
   {
     
    OutText(0,165,(byte *)&"  AIXO NOMES ES EL INICI !!!            \0",0,0,0,FONTMT,VSCREEN3);
    if(color<63) {ModificarColorPaleta(color,0,0,15);color++;}
   }

   if((temps>=1800) && (temps<1900))
   {
    OutText(0,165,(byte *)&"  AIXO NOMES ES EL INICI !!!            \0",0,0,0,FONTMT,VSCREEN3);
    if(color>0) {ModificarColorPaleta(color,0,0,15);color--;}
   }



   escape=letras[ESCAPE];
   Flip_VScreen(VIDEO,VSCREEN3);
   WaitVRetrace();
   temps++;

  }


 if(SB)
 {
  stop_sound(1);
  stop_sound(8);

 }



 if((Mapa=(byte *)malloc(MAX_LLETRES_Y*MAX_LLETRES_X))==NULL) Quit(Motiu2);
 if((Nau=(byte *)malloc(19982))==NULL) Quit(Motiu2);
 if((Terra=(byte *)malloc(11000))==NULL) Quit(Motiu2);

 if( (fitxer = fopen("dat//credits.dat","rb")) == NULL) Quit(Motiu0);

 for(i=0;i<MAX_LLETRES_Y;i++) fread(Mapa+(i*MAX_LLETRES_X),MAX_LLETRES_X,1,fitxer);
 fclose(fitxer);

 if( (fitxer = fopen("grafics//Nau00.raw","rb")) == NULL) Quit(Motiu3);

 fread(Nau,19982L,1,fitxer);

 fclose(fitxer);

 if( (fitxer = fopen("grafics//terra.raw","rb")) == NULL) Quit(Motiu4);

 fread(Terra,11000L,1,fitxer);

 fclose(fitxer);


 XchangeColor(paleta2,4,63);

 SetPalette(paleta2,0,255);

 if(SB) start_sound(sonidos[0],0,OFF);


// if(!CarregarImatgeVScreen((byte *)&"grafics//credits.raw",BUFFER2)) Quit(Motiu1);

 ClearScreen(NEGRE,VSCREEN2);
 InitStars();
 temps = 1;

 true = CERT;
 up = CERT;


 while(true&&!escape)
 {

   DeleteStars(VSCREEN2);
   MoveStars();
   DrawStars(VSCREEN2);


  

  POSY = ypos;
  SCROLLY = yscroll;

  Flip_VScreen(VSCREEN1,VSCREEN2);
  PutSprite(xterra,60,Terra,110,100,0,0,319,199,COLOR_MASCARA,VSCREEN1);
  PutSprite(xnau,60,Nau,206,97,0,0,319,199,COLOR_MASCARA,VSCREEN1);


  for(i=-ALTURA_LLETRAM;i<(195);i+=ALTURA_LLETRAM) 
  {
   POSX=0;
 
   for(j=0;j<(260);j+=AMPLADA_LLETRAM)
   {
     PutChar(j,i-(SCROLLY-2-ALTURA_LLETRAM),traduccio_caracter(toupper(Mapa[((POSY<<4)+(POSY<<2))+POSX])),0,0,0,0,MEDFNT,VSCREEN1);
     POSX++;
   }

   POSY++;

  }

  if(!pres) {pres = letras[ESCAPE];}

  if(pres||(ypos>=(MAX_LLETRES_Y-NUMERO_LLETRES_Y)-1))
  {
   if((ypos>=(MAX_LLETRES_Y-NUMERO_LLETRES_Y)-1)) up = FALS;
   if(true)
   {

    if(temps1 == 63) true = FALS;
    else
    {
     for(i=0;i<768;i++) if(paleta2[i]!=0) paleta2[i]--;
     SetPalette(paleta2,0,255);
 
     if(SB)
     {
      if(((temps1%4)==0)&&(v>1)) v--;
      setmastervolume(v,v);
     }
     temps1++;

    }
   }
  };
    
  Flip_VScreen(VIDEO,VSCREEN1);
  WaitVRetrace();
  RotatePaletteLeft(paleta2,2,4);
  SetPalette(paleta2,0,6);



  if(up)
  {
    if((temps % 2) == 0)
    {
     if((yscroll % ALTURA_LLETRAM) == 0) {yscroll = 1;ypos++;}
     else yscroll++;
    }
  }

  temps++;
  if((temps%6)==0) xterra++;

  if(((ypos>=(MAX_LLETRES_Y-NUMERO_LLETRES_Y)-1)||pres)&&!xnaudown)
  {
   if(SB)start_sound(sonidos[9],9,OFF);
   xnaudown = CERT;
  }

  if(xnaudown)
  {
   xnau-=10;
  }

 }

 if(SB)
 {
  stop_sound(0);
  stop_sound(9);
  setmastervolume(15,15);
 }

 ClearScreen(NEGRE,VIDEO);
 ClearScreen(NEGRE,VSCREEN1);
 ClearScreen(NEGRE,VSCREEN2);
 ClearScreen(NEGRE,VSCREEN3);
 PaletaNegre(paleta2,0,255);
 SetPalette(paleta2,0,255);

 free(Mapa);
 free(Nau);
 free(Terra);


 

}




void gameover()
{
 byte Motiu1[]={"No s'ha pogut obrir els arxius necessaris...\0"};
 int i=0;

 if(!CarregarImatgeVScreen("grafics//terrad0.raw",BUFFER2))
 {
  Quit(Motiu1);
 }


 if(!CarregarImatgeVScreen("grafics//terra0.raw",BUFFER1))
 {
  Quit(Motiu1);
 }

 Flip_VScreen(VIDEO,VSCREEN1);

 CopiaPaleta(paleta2,paleta1,0,255);
 temps = 1;
 SetPalette(paleta2,0,255);

 do{

   if(temps>200&&temps<350)
   {
    if((temps%2)==0)
    {
     for(i=1;i<240;i++)
     {
      if(paleta2[i*3]<63)paleta2[i*3]++;
      if(paleta2[i*3+1]>0)paleta2[i*3+1]--;
      if(paleta2[i*3+2]>0)paleta2[i*3+2]--;
     }
     
   }
   SetPalette(paleta2,0,255);


   }
   else
   {
    if(temps>=350)
    {
     if((temps==350))
     {
      SetPalette(paleta1,0,255);
      ModificarColorPaleta(63,63,63,224);
      ModificarColorPaleta(0,0,0,128);
      if(SB)
      {
       start_sound(sonidos[2],2,ON);
       start_sound(sonidos[16],16,OFF);
      }
     }

     if(temps>600)
     {
      OutText(50,90,"GAME OVER\0",0,0,0,BIGFNT,VSCREEN2);
     }
     
     Flip_VScreen(VIDEO,VSCREEN2);

    }
   }
   WaitVRetrace();
   temps++;
 }while(!letras[ESCAPE]&&temps<900);

 FadeOut(0,255);
 stop_sound(16);
 stop_sound(2);

}






