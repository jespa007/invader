//#include "menu.cc"
	#include "System.cpp"
	#include "Graphics.cpp"
	#include "Input.cpp"
	#include "Collider.cpp"
	#include "Image.cpp"
	#include "Sprite.cpp"
	#include "Entity.cpp"
	#include "EntityAnimation.cpp"
	#include "EntityManager.cpp"
	#include "Tilemap.cpp"
	#include "Font.cpp"
	#include "Sound.cpp"
	#include "SoundPlayer.cpp"
	/*
	#include "Conjunt.cxx"
	#include "Effects.cxx"
	#include "Enemics.cxx"
	#include "Resources.cxx"
	
	#include "Invader.cxx"
	#include "Mouse.cxx"
	#include "Moviment.cxx"
	#include "Objecte.cxx"
	#include "Paleta.cxx"
	#include "Stage1.cxx"
	#include "Vscreen.cxx"*/


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



int menu();
void options();

//void interrupt ( *oldhandler)(__CPPARGS);
//void interrupt SONIDOS(__CPPARGS);


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

 int BLOCINVERS[AMPLADA_BLOC*ALTURA_BLOC];




 /********************\
| VSCREENS NECESSARIES |
 \********************/

int Cheat = FALS;
int vides;
dword puntuacio=0;
dword maxima_puntuacio=0;
int dificultat = MITJANA;
word temps = 0;

char  * BUFFER1 = NULL; 
char  * BUFFER2 = NULL;
char  * BUFFER3 = NULL;
char  * BUFFER4 = NULL;

word VSCREEN1;
word VSCREEN2;
word VSCREEN3;
word VSCREEN4;

 /********************\
| PALETES NECESSARIES |
 \********************/


tPaleta paleta1,paleta2,paleta3,paleta4;


                   /*-__________-*\__  �   �            �
  �       �     )-/                \_)   �      �
    �            | (  FUNCIO MAIN  |_) �      �     � 
 .         �    )-\                /_)   �    �
   �   �           \*_-----------_*/


//  �������������Ŀ
//  �Propi del joc�
//  ���������������

//#include "Effects.cc"
//#include "Text.cc"

//#include "Teclado.c"      // Per JASM & BMP

//#include "Ruta.cc"
//#include "Moviment.cc"
#include "Init.cc"
//#include "Scroll.cc"
#include "Menu.cc"
//#include "Conjunt.cc"


//#include "Part.cc"
//#include "Objecte.cc"

//#include "Test.cc"


//#include "Stage1.cc"

int main(int argc,char *argv[])
{
 byte Motiu0[]={"Sortint OK...\0"};
 byte Motiu1[]={"No s'ha pogut inicialitzar \"INVADER\"...\0"};

 int i,StartTicks;
 //int true = FALS;

 if(argc>1) if(!strcmp(argv[1],"invencible")) Cheat = CERT;

// InitFons();

 /* Inicializa SMIX */

 InicialitzarDrivers();



 if(!InicialitzarEstructura()) Quit(Motiu1); // Estructura dels sprites,sons,buffers,lletres i blocs del mapa.


// SetMode13();



 if(!CarregarImatgeVScreen("grafics//TITUL.RAW",BUFFER1)) Quit(Motiu1);
 if(!CarregarImatgeVScreen("grafics//OPTIONS.RAW",BUFFER2)) Quit(Motiu1);

if(SDL_MUSTLOCK(Video))
{
 SDL_LockSurface(Video);
}


 ClearScreen(NEGRE);


 CarregarPaleta("grafics//paleta1.pal",paleta1);

 CopiaPaleta(paleta3,paleta1,0,256);

 paleta3[227].r = 0;
 paleta3[227].g = 0;
 paleta3[227].b = 0;

 paleta3[16].r = 0;
 paleta3[16].g = 0;
 paleta3[16].b = 0;

 paleta3[136].r = 0;
 paleta3[136].g = 0;
 paleta3[136].b = 0;

 paleta3[159].r = 0;
 paleta3[159].g = 0;
 paleta3[159].b = 0;

 paleta3[67].r = 0;
 paleta3[67].g = 0;
 paleta3[67].b = 0;


 paleta3[15].r = 255;
 paleta3[15].g = 255;
 paleta3[15].b = 255;

 CopiaPaleta(paleta1,paleta3,0,256);

 PaletaNegre(paleta2,0,256);

/* save the old interrupt vector */
//   oldhandler = getvect(INTR);

/* install the new interrupt handler */
//   setvect(INTR, SONIDOS);

 vides = 3;

// if(SB) start_sound(sonidos[5],5,ON);


 SetPalette(paleta2,0,256);
 ClearScreen(NEGRE);


 Flip_VScreen(ptr_video,BUFFER1);
// OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);

// OutText(190,0,"Maxima:\0",0,0,0,FONTMT);
 OutText(190,0,"Maxima:\0",0,0,0,FONTMT);

/// Visualitzar_Numero(8*11,0,puntuacio,7,0);
 Visualitzar_Numero(8*11,0,puntuacio,7,0);

// Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);
 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);




 
// Flip_VScreen();
 FadeIn(paleta3,0,256);

 


 do{

  //Flip_VScreen(ptr_video,BUFFER1);Flip_Video();
  //MostrarPunter();
     StartTicks = SDL_GetTicks();


  switch(i=menu())
  {
    
   case 0:
    //      OcultarPunter();
//          if(SB)start_sound(sonidos[6],6,OFF);

           FadeOut(paleta3,0,256);
  //        if(SB) stop_sound(5);

          
           switch(game())
           {
			   
            case 1:credits();break;
            case 2:gameover();
           }
		   
            //gameover();
          // if(SB) start_sound(sonidos[5],5,ON);
           if(!CarregarImatgeVScreen("grafics//TITUL.RAW",BUFFER1)) Quit(Motiu1);
           if(!CarregarImatgeVScreen("grafics//OPTIONS.RAW",BUFFER2)) Quit(Motiu1);
           
		   SetPalette(paleta2,0,256);
		   Flip_VScreen(ptr_video,BUFFER1);
           while((SDL_GetTicks() - StartTicks) < 16);
           Flip_Video();

		  

                 //OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);
                 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);

                 //OutText(190,0,"Maxima:\0",0,0,0,FONTMT);
                 OutText(190,0,"Maxima:\0",0,0,0,FONTMT);
        
                 //Visualitzar_Numero(8*11,0,puntuacio,7,0);
                 Visualitzar_Numero(8*11,0,puntuacio,7,0);

                 //Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);
                 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);



           FadeIn(paleta3,0,256);
           break;
 
   case 1: //if(SB) start_sound(sonidos[6],6,OFF);
           //OcultarPunter();
		   FadeOut(paleta3,0,256);
		   //
	       options();
		 // SDL_Delay(1000);
		   Flip_VScreen(ptr_video,BUFFER1); 
           SetPalette(paleta2,0,256);
           while((SDL_GetTicks() - StartTicks) < 16);
		   Flip_Video();

           
 //OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);
 OutText(0,0,"Puntuacio:\0",0,0,0,FONTMT);

 //OutText(190,0,"Maxima:\0",0,0,0,FONTMT);
 OutText(190,0,"Maxima:\0",0,0,0,FONTMT);

 //Visualitzar_Numero(8*11,0,puntuacio,7,0);
 Visualitzar_Numero(8*11,0,puntuacio,7,0);

 //Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);
 Visualitzar_Numero(190+(8*8),0,maxima_puntuacio,7,0);

           FadeIn(paleta3,0,256);
           break;
  }
 
 }while(i!=2);
 //if(SB) start_sound(sonidos[6],6,OFF);

// SetPalette(paleta3,0,255);

 
 FadeOut(paleta3,0,256);

 //if(SB) stop_sound(6);
 //if(SB) stop_sound(5);
 // reset the old interrupt handler
 // setvect(INTR, oldhandler);


 //Quit(Motiu0);
 SDL_UnlockSurface(Video);

 exit(0);
}









                   /*-________________________-*\__  �   �            �
  �       �     )-/                              \_)   �      �
    �            | (  IMPLEMENTACIO DE FUNCIONS  |_) �      �     � 
 .         �    )-\                              /_)   �    �
   �   �           \*_-------------------------_*/














void credits()
{
 int temps;
 char *Nau=NULL;
 char *Terra=NULL;
 char *NauNodriu=NULL;
 unsigned char color;
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
 tPaleta paleta;


 FILE *fitxer = NULL;
 int up=0,j,variable_certa;
 int temps1 =0,StartTicks;



 color = 0;
 ClearScreen(NEGRE);

 CarregarPaleta("grafics//paleta1.pal",paleta);

// CopiaPaleta(paleta2,paleta,0,255);
 //CopiaPaleta(paleta2,paleta,0,255);

 for(i=17;i<32;i++)
 {
  paleta[i].r=i*8-10;
  paleta[i].g=i*8-10;
  paleta[i].b=i*8-10;

 }

 paleta[224].r = 255;
 paleta[224].g = 255;
 paleta[224].b = 255;

 paleta[128].r = 0;
 paleta[128].g = 0;
 paleta[128].b = 255;



 x=0;

 if(!CarregarImatgeVScreen("grafics//SPACE0.RAW",BUFFER1)) Quit(Motiu5);

 if((NauNodriu=(char *)malloc(230*200))==NULL) Quit(Motiu2);
 if( (fitxer = fopen("grafics//NauMare0.raw","rb")) == NULL) Quit(Motiu6);

 fread(NauNodriu,230*200,1,fitxer);

 fclose(fitxer);

/* if(SB)
 {
  start_sound(sonidos[1],1,ON);
  start_sound(sonidos[22],22,ON);
 }*/
 temps = 0;

 SetPalette(paleta,0,256);

 while(!(escape)&&temps < 1000)
 {

 StartTicks = SDL_GetTicks();
  Flip_VScreen(ptr_video,BUFFER1);
  PutSprite(xnaunodriu,0,NauNodriu,230,200,0,0,319,199,COLOR_MASCARA);

  while((SDL_GetTicks() - StartTicks) < 16);
  Flip_Video();
  //SDL_Delay(10);

  if(temps%5==0) xnaunodriu++;
  temps++;
  escape=TECLA_ESCAPE;
 }

 /*if(SB)
 {
  stop_sound(22);
  start_sound(sonidos[8],8,OFF);
 }*/

//SetPalette(paleta2,0,256);


 free(NauNodriu);

if(!escape)
{
    StartTicks = SDL_GetTicks();

 //ClearScreen(NEGRE);

 CarregarImatgeVScreen("grafics//enemic.raw",BUFFER1);
 Flip_VScreen(ptr_video,BUFFER1);
 while((SDL_GetTicks() - StartTicks) < 16);
 Flip_Video();
// InitStars(); // Setup Stars

  SetPalette(paleta,0,256);
}

 while(!(escape)&& temps < 2100)
 {
     StartTicks = SDL_GetTicks();

//   DeleteStars(VSCREEN2);
//   MoveStars();
//   DrawStars(VSCREEN2);

   if(temps == 1400) ClearRect(0,165,320,34,0);
   //Flip_VScreen(VSCREEN3,VSCREEN2);
   //PutSprite(0,0,BUFFER1,320,200,0,0,320,200,227,VSCREEN3);

   

   if((temps >= 1000) && (temps<1200))
   {
    OutText(0,165,"  HAS GUANYAT UNA BATALLA \0",0,0,0,FONTMT);
    OutText(0,165+MAX_ALTURA_TEXT,"  PERO NO LA GUERRA.\0",0,0,0,FONTMT);
    if(color<250) {ModificarColorPaleta(paleta,color,0,0,15);color+=4;}

   }

   if((temps>=1300) && (temps<1400))
   {
    OutText(0,165,"  HAS GUANYAT UNA BATALLA \0",4,0,0,FONTMT);
    OutText(0,165+MAX_ALTURA_TEXT,"  PERO NO LA GUERRA.\0",0,0,0,FONTMT);
    if(color>4) {ModificarColorPaleta(paleta,color,0,0,15);color-=4;}
   }


   if((temps >= 1400) && (temps<1900))
   {
     
    OutText(0,165,"  AIXO NOMES ES EL INICI !!!            \0",0,0,0,FONTMT);
    if(color<250) {ModificarColorPaleta(paleta,color,0,0,15);color+=4;}
   }

   if((temps>=2000) && (temps<2100))
   {
    OutText(0,165,"  AIXO NOMES ES EL INICI !!!            \0",0,0,0,FONTMT);
    if(color>4) {ModificarColorPaleta(paleta,color,0,0,15);color-=4;}
   }



   escape |= TECLA_ESCAPE;
 //  Flip_VScreen(ptr_video,BUFFER3);

   //WaitVRetrace();
   while((SDL_GetTicks() - StartTicks) < 16);
   Flip_Video();
   temps++;

  }
/*

 if(SB)
 {
  stop_sound(1);
  stop_sound(8);

 }*/



 if((Mapa=(byte *)malloc(MAX_LLETRES_Y*MAX_LLETRES_X))==NULL) Quit(Motiu2);
 if((Nau=(char *)malloc(19982))==NULL) Quit(Motiu2);
 if((Terra=(char *)malloc(11000))==NULL) Quit(Motiu2);

 if( (fitxer = fopen("dat//credits.dat","rb")) == NULL) Quit(Motiu0);

 for(i=0;i<MAX_LLETRES_Y;i++) fread(Mapa+(i*MAX_LLETRES_X),MAX_LLETRES_X,1,fitxer);
 fclose(fitxer);

 if( (fitxer = fopen("grafics//Nau00.raw","rb")) == NULL) Quit(Motiu3);

 fread(Nau,19982L,1,fitxer);

 fclose(fitxer);

 if( (fitxer = fopen("grafics//terra.raw","rb")) == NULL) Quit(Motiu4);

 fread(Terra,11000L,1,fitxer);

 fclose(fitxer);


 
// CopiaPaleta(paleta,paleta2,0,256);
// SetPalette(paleta,0,256);
 XchangeColor(paleta,4,63);

// if(SB) start_sound(sonidos[0],0,OFF);


// if(!CarregarImatgeVScreen((byte *)&"grafics//credits.raw",BUFFER2)) Quit(Motiu1);

 ClearScreen(NEGRE);
 InitStars();
 temps = 1;

 variable_certa = CERT;
 up = CERT;


 while(variable_certa&&!escape)
 {
     StartTicks = SDL_GetTicks();

   ClearScreen(NEGRE);
//   DeleteStars(VSCREEN2);
   MoveStars();
   DrawStars();


  

  POSY = ypos;
  SCROLLY = yscroll;

//  Flip_VScreen(BUFFER1,BUFFER2);
  PutSprite(xterra,60,Terra,110,100,0,0,319,199,COLOR_MASCARA);
  PutSprite(xnau,60,Nau,206,97,0,0,319,199,COLOR_MASCARA);


  for(i=-ALTURA_LLETRAM;i<(195);i+=ALTURA_LLETRAM) 
  {
   POSX=0;
 
   for(j=0;j<(260);j+=AMPLADA_LLETRAM)
   {
     PutChar(j,i-(SCROLLY-2-ALTURA_LLETRAM),traduccio_caracter(toupper(Mapa[((POSY<<4)+(POSY<<2))+POSX])),0,0,0,0,MEDFNT);
     POSX++;
   }

   POSY++;

  }

  if(!pres) {pres = TECLA_ESCAPE;}

  if(pres||(ypos>=(MAX_LLETRES_Y-NUMERO_LLETRES_Y)-1))
  {
   if((ypos>=(MAX_LLETRES_Y-NUMERO_LLETRES_Y)-1)) up = FALS;
   if(variable_certa)
   {

    if(temps1 >= 63) variable_certa = FALS;
    else
    {
     for(i=0;i<256;i++)
	 {
		if(paleta[i].r > 4) paleta[i].r-=4;
		if(paleta[i].g > 4) paleta[i].g-=4;
		if(paleta[i].b > 4) paleta[i].b-=4;
	 }
     SetPalette(paleta,0,256);
 
     /*if(SB)
     {
      if(((temps1%4)==0)&&(v>1)) v--;
      setmastervolume(v,v);
     }*/
     temps1++;

    }
   }
  };
    
  //Flip_VScreen(ptr_video,BUFFER1);
  
  //WaitVRetrace();
  RotatePaletteLeft(paleta,2,4);
  SetPalette(paleta,0,256);
    while((SDL_GetTicks() - StartTicks) < 16);
  Flip_Video();


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
//   if(SB)start_sound(sonidos[9],9,OFF);
   xnaudown = CERT;
  }

  if(xnaudown)
  {
   xnau-=10;
  }

 }
/*
 if(SB)
 {
  stop_sound(0);
  stop_sound(9);
  setmastervolume(15,15);
 }*/

 ClearScreen(NEGRE);
 FadeOut(paleta,0,256);
// ClearScreen(NEGRE,VSCREEN1);
// ClearScreen(NEGRE,VSCREEN2);
// ClearScreen(NEGRE,VSCREEN3);
// PaletaNegre(paleta2,0,255);
// SetPalette(paleta2,0,255);

 free(Mapa);
 free(Nau);
 free(Terra);


 

}




void gameover()
{
int StartTicks;
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

 Flip_VScreen(ptr_video,BUFFER1);

 CopiaPaleta(paleta2,paleta1,0,256);
 CopiaPaleta(paleta3,paleta1,0,256);
 temps = 1;
 SetPalette(paleta2,0,256);

 do{

 StartTicks = SDL_GetTicks();

   if(temps>200&&temps<350)
   {
    if((temps%2)==0)
    {
     for(i=1;i<240;i++)
     {
      if(paleta2[i].r<250)paleta2[i].r+=4;
      if(paleta2[i].g>4)paleta2[i].g-=4;
      if(paleta2[i].b>4)paleta2[i].b-=4;
     }
     
   }
   SetPalette(paleta2,0,256);


   }
   else
   {
    if(temps>=350)
    {
     if((temps==350))
     {
      SetPalette(paleta3,0,256);
      ModificarColorPaleta(paleta3,255,255,255,224);
      ModificarColorPaleta(paleta3,0,0,0,128);
//      if(SB)
//      {
       //start_sound(sonidos[2],2,ON);
       //start_sound(sonidos[16],16,OFF);
//      }
     }
     
     Flip_VScreen(ptr_video,BUFFER2);

	 if(temps>600)
     {
      OutText(50,90,"GAME OVER\0",0,0,0,BIGFNT);
     }
     

    }
   }
   Flip_Video();
   while((SDL_GetTicks() - StartTicks) < 16);
   //WaitVRetrace();
   temps++;
 }while(!TECLA_ESCAPE&&temps<900);

 FadeOut(paleta3,0,256);
 CopiaPaleta(paleta3,paleta1,0,256);
 PaletaNegre(paleta2,0,256);
 
// stop_sound(16);
// stop_sound(2);

}






