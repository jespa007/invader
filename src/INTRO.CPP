#include "all_lib.h"


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

                   /*-______________-*\__  ú   ú            ú
  ú       ú     )-/                    \_)   ú      ú
    ú            | (  SOUND BLASTER 16  |_) ú      ú     ú 
 .         ú    )-\                    /_)   ú    ú
   ú   ú           \*_---------------_*/


#define NUMSOUNDS 6     /* Cambie este parametro si a¤adi¢ mas sonidos */
#define XMSREQUIRED 700 /* memoria en kbytes, que requiere sus sonidos */

char *sonidos_key[NUMSOUNDS] = { /* aqui debe definir las claves de su */
	 "JET",								/* archivo de sonido, lea el archivo  */
	 "GUN",								/* leame.txt para detalles sobre esto */
	 "CRASH",
	 "CANNON",
	 "LASER",
	 "GLASS",
};



#include "sb\mixer.h"	/*solo debe incluir este archivo para usar Sound Blaster*/



                   /*-___________-*\__  ú   ú            ú
  ú       ú     )-/                 \_)   ú      ú
    ú            | (  DEFINICIONS    |_) ú      ú     ú 
 .         ú    )-\                  /_)   ú    ú
   ú   ú           \*_-------------_*/





                   /*-_________________-*\__  ú   ú            ú
  ú       ú     )-/                       \_)   ú      ú
    ú            | (  DEFINICIO DE TIPUS  |_) ú      ú     ú 
 .         ú    )-\                       /_)   ú    ú
   ú   ú           \*_------------------_*/


//typedef tSpriteDinamic Sprites[MAX_SPRITES];
typedef byte far tBloc[AMPLADA_BLOC*ALTURA_BLOC];


                   /*-____________________-*\__  ú   ú            ú
  ú       ú     )-/                          \_)   ú      ú
    ú            | (  CAP€ALERA DE FUNCIONS  |_) ú      ú     ú 
 .         ú    )-\                          /_)   ú    ú
   ú   ú           \*_---------------------_*/




//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Estructures del joc³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

void InicialitzarEstructura(void);

//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Funcions propies del joc³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ


void Scrollejar(int POSICIO_Y,int SCROLL_Y,word SEGMENT);


//  ÚÄÄÄÄÄÄ¿
//  ³Altres³
//  ÀÄÄÄÄÄÄÙ




//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Gestio de Sortida³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

void Quit(byte *Motiu);


                   /*-_______________-*\__  ú   ú            ú
  ú       ú     )-/                     \_)   ú      ú
    ú            | (  VARIABLES GLOBALS |_) ú      ú     ú 
 .         ú    )-\                     /_)   ú    ú
   ú   ú           \*_----------------_*/


 /******************************\
| GRAFICS DEL ESCENARI I SPRITES |
 \******************************/


//tSpriteDinamic SpritesDinamics[MAX_SPRITES];
//tSpriteEstatic SpritesEstatics[MAX_SPRITES];

// tBloc Blocs[MAX_BLOCS];

 /*****************\
| MAPA DEL ESCENARI |
 \*****************/


byte Mapa[MAX_BLOCS_Y][MAX_BLOCS_X];
byte Objectes[60*10]; // N§ Maxim de posicions.

 /********************\
| VSCREENS NECESSARIES |
 \********************/

byte far * BUFFER1; // Necessari que sigui "far" pq SEGMENT:OFFSET --> A000:0000
byte far * BUFFER2;
byte far * BUFFER3;
byte far * BUFFER4;

word VSCREEN1;
word VSCREEN2;
word VSCREEN3;
word VSCREEN4;

 /********************\
| PALETES NECESSARIES |
 \********************/


tpaleta paleta1,paleta2,paleta3;






void Quit(unsigned char *Motiu)
{
   SetMode3();

   printf("%s",Motiu);
   
   asm mov ax,4c00h // Interrupcio per sortir al MS-DOS
   asm int 21h

   Lliurar_VSBuffer(BUFFER1);
   Lliurar_VSBuffer(BUFFER2);
   Lliurar_VSBuffer(BUFFER3);

   exit(1); // Sortida amb error.
}




void InicialitzarEstructura(void)
{
 byte Motiu1[]={"No s'ha pogut inicialitzar els VSCREENS !!!\".\0"};
 byte Motiu2[]={"No s'ha pogut obrir el arxiu \"mapa1.dat !!!\".\0"};
 byte Motiu3[]={"No s'ha pogut obrir el arxiu \"blocs.raw !!!\".\0"};
 FILE *fitxer2 = NULL;
 int i,j,k=0,x,y;



 if((BUFFER1 = VScreen(&VSCREEN1))==NULL) Quit(Motiu1); // Ens entrega el punter i la seva adre‡a.
 if((BUFFER2 = VScreen(&VSCREEN2))==NULL) Quit(Motiu1); // Ens entrega el punter i la seva adre‡a.
 if((BUFFER3 = VScreen(&VSCREEN3))==NULL) Quit(Motiu1); // Ens entrega el punter i la seva adre‡a.
 if((BUFFER4 = VScreen(&VSCREEN4))==NULL) Quit(Motiu1); // Ens entrega el punter i la seva adre‡a.




 // Carreguem la estructura del mapa...

 if( (fitxer2 = fopen((byte *)&"dat//mapa1.dat","rb")) == NULL ) Quit(Motiu2);

 for(i=0;i<MAX_BLOCS_Y;i++) fread(Mapa[i],MAX_BLOCS_X,1,fitxer2) ;

 fclose(fitxer2); // Millor k el tanqui ara, k encara m'el deixar‚ obert. :)

 // Carreguem els blocs...

 // Carregar de les fonts...

 if(!CarregarFontMonoTextura()) Quit((byte *)&"Adeu.\0");
 if(!CarregarFontMitjana()) Quit((byte *)&"Adeu.\0");
 if(!CarregarFontGran()) Quit((byte *)&"Adeu.\0");




}











void main()
{
 int x=0,color=0;
 word temps=0;
 int ypos=-399,xpos=-319,upy;
 int speed = 1;


 char Motiu1[]={"No s'ha pogut inicialitzar els VSCREENS !!!\".\0"};
 char Motiu2[]={"No s'ha pogut obrir el arxiu \"mapa1.dat !!!\".\0"};
 char Motiu3[]={"No s'ha pogut obrir el arxiu \"celes.pcx !!!\".\0"};
 char Motiu4[]={"No s'ha pogut obrir el arxiu \"logo.raw !!!\".\0"};
 char Motiu5[]={"No s'ha pogut obrir el arxiu \"paleta1.pal !!!\".\0"};
 char Motiu6[]={"No s'ha pogut obrir el arxiu \"vista1.raw !!!\".\0"};
 char Motiu7[]={"No s'ha pogut obrir el arxiu \"vista2.raw !!!\".\0"};
 char Motiu8[]={"No s'ha pogut obrir el arxiu \"vista3.raw !!!\".\0"};

 tpaleta paleta1;
 tpaleta paleta2;
 


 InicialitzarEstructura();



 if(!CarregarPaleta("grafics//paleta1.pal",paleta1)) Quit(Motiu5);


 CarregarImatgeVScreen("grafics//logo.raw",BUFFER1);
 Flip_VScreen(VIDEO,VSCREEN1);





  SetMode13();
  SetPalette(paleta1,0,255);
  getch();


/*
  CarregarImatgeVScreen("grafics//enemic.raw",BUFFER1);
  InitStars(); // Setup Stars

  SetPalette(paleta1,0,255);

//  Flip_VScreen(VIDEO,VSCREEN1);

//  VisualitzarPaleta();
//  while(!(tolower(getch()) == 's')) RotatePaletteRight(paleta1,200,255);


//  delay(500);


 color = 0;
 ClearScreen(NEGRE,VSCREEN2);


  



 do
 {

   DeleteStars(VSCREEN2);
   MoveStars();
   DrawStars(VSCREEN2);

   if((temps == 500) || (temps == 1000)) ClearScreen(NEGRE,VSCREEN2);
   Flip_VScreen(VSCREEN3,VSCREEN2);
   PutSprite(0,0,BUFFER1,320,200,0,0,320,200,227,VSCREEN3);

   if((temps >= 0) && (temps<400))
   {
    OutText(0,165,(byte *)&"  HAS GUANYAT UNA BATALLA \0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+MAX_ALTURA_TEXT,(byte *)&"  PERO NO LA GUERRA.\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+2*MAX_ALTURA_TEXT,(byte *)&"  HE VINGUT DEL MES ALLA AMB UN\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+3*MAX_ALTURA_TEXT,(byte *)&"  SOL PROPOSIT.\0",0,0,0,FONTMT,VSCREEN3);
    if(color<63) {ModificarColorPaleta(color,0,0,15);color++;}

   }

   if((temps>=400) && (temps<500))
   {
    OutText(0,165,(byte *)&"  AIXO NOMES ES EL INICI !!!            \0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+MAX_ALTURA_TEXT,(byte *)&"  DEMOSTRACIO DEL MEU PODER.\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+2*MAX_ALTURA_TEXT,(byte *)&"  HE VINGUT DEL MES ALLA AMB UN\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,165+3*MAX_ALTURA_TEXT,(byte *)&"  SOL PROPOSIT.\0",0,0,0,FONTMT,VSCREEN3);
    if(color>0) {ModificarColorPaleta(color,0,0,15);color--;}
   }


   if((temps >= 500) && (temps<900))
   {
     
     OutText(0,170,(byte *)&"  CONQUISTAR A TOTES LES NOIES\0",0,0,0,FONTMT,VSCREEN3);
     OutText(0,170+MAX_ALTURA_TEXT,(byte *)&"  MAQUES DE GIRONA !!!\0",0,0,0,FONTMT,VSCREEN3);
     if(color<63) {ModificarColorPaleta(color,0,0,15);color++;}
   }

   if((temps>=900) && (temps<1000))
   {
     OutText(0,170,(byte *)&"  CONQUISTAR A TOTES LES NOIES\0",0,0,0,FONTMT,VSCREEN3);
     OutText(0,170+MAX_ALTURA_TEXT,(byte *)&"  MAQUES DE GIRONA !!!\0",0,0,0,FONTMT,VSCREEN3);
     if(color>0) {ModificarColorPaleta(color,0,0,15);color--;}
   }



   if((temps>=1000) && (temps<1400))
   {
    OutText(0,170,(byte *)&"  SI NO ME LES REUNIU EN MENYS DE 24\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,170+MAX_ALTURA_TEXT,(byte *)&"  HORES,FARE EXCLATAR AQUESTA CIUTAT ! \0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,170+2*MAX_ALTURA_TEXT,(byte *)&"  JA, JA, JA ! \0",0,0,0,FONTMT,VSCREEN3);
    if(color<63) {ModificarColorPaleta(color,0,0,15);color++;}

   }


   if((temps>=1400) && (temps<1500))
   {
    OutText(0,170,(byte *)&"  SI NO ME LES REUNIU EN MENYS DE 24\0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,170+MAX_ALTURA_TEXT,(byte *)&"  HORES,FARE EXCLATAR AQUESTA CIUTAT ! \0",0,0,0,FONTMT,VSCREEN3);
    OutText(0,170+2*MAX_ALTURA_TEXT,(byte *)&"  JA, JA, JA ! \0",0,0,0,FONTMT,VSCREEN3);
    if(color>0) {ModificarColorPaleta(color,0,0,15);color--;}
   }

   Flip_VScreen(VIDEO,VSCREEN3);
   WaitVRetrace();
   temps++;

  }while(!kbhit()&& temps < 1500);


 if(kbhit()) FadeOut(0,255);
 else
 {
  SetMode320_200X();

 SetPalette(paleta1,0,255);

 SetDimX(DIM4x1);

 PaletaNegre(paleta2,0,255);

 SetPalette(paleta2,0,255);

 if(!CarregarImatgeX(0,0,"grafics//logo.raw",1280,200,PAGINA0)) Quit(Motiu4);

 if(!kbhit())SetPalette(paleta1,0,255);

 if(!kbhit())
 {
  do{
   SetStartAddress(x);
   WaitVRetrace();
   x ++ ;
  
  }while((x <= 240) && !kbhit());
  }
 }
 FadeOut(0,255);
 
 */

 temps = 0;
 // Mega Nau

 if(!CarregarImatgeVScreen("intro//vista1.raw",BUFFER1)) Quit(Motiu6);
 if(!CarregarImatgeVScreen("intro//vista2.raw",BUFFER2)) Quit(Motiu7);
 if(!CarregarImatgeVScreen("intro//vista3.raw",BUFFER3)) Quit(Motiu8);
 CarregarImatgeVScreen("intro//nauintro.raw",BUFFER4);

 Flip_VScreen(VIDEO,VSCREEN1);
 getch();

 upy =0;

 do{


  if((ypos+200>=0))
  {
   PutBlock(xpos,ypos,BUFFER1,320,200,0,0,320,200,VSCREEN4);
   PutBlock(xpos+320,ypos,BUFFER1,320,200,0,0,320,200,VSCREEN4);
  }
  if((ypos+400>=0))
  {
   PutBlock(xpos,ypos+200,BUFFER2,320,200,0,0,320,200,VSCREEN4);
   PutBlock(xpos+320,ypos+200,BUFFER2,320,200,0,0,320,200,VSCREEN4);
  }
  if((ypos+600>=0))
  {
   PutBlock(xpos,ypos+400,BUFFER3,320,200,0,0,320,200,VSCREEN4);
   PutBlock(xpos+320,ypos+400,BUFFER3,320,200,0,0,320,200,VSCREEN4);
  }

  WaitVRetrace();
  Flip_VScreen(VIDEO,VSCREEN4);

  if((temps%13 == 0) && (temps>=300) && (speed < 10)) speed++;

   if(xpos<=0){ {if((temps % 2) == 0)xpos+= 2*speed;}
   }
  else
   xpos = -319;

  ypos+=(1*upy);

  if(temps==500) upy=1;
  if(ypos>=0) upy=0;
  
  temps++;
 }while(!kbhit());


 SetMode3();
 printf("Sortint Intro OK...");
 asm mov ax,4c00h // Interrupcio per sortir al MS-DOS
 asm int 21h
 Lliurar_VSBuffer(BUFFER1);
 Lliurar_VSBuffer(BUFFER2);
 Lliurar_VSBuffer(BUFFER3);
 Lliurar_VSBuffer(BUFFER4);

 exit(1); // Sortida amb error.

}

