#include "Invader.h"


extern INFO_ENEMY MatriuEnemicsStage1[MAX_ENEMICS_STAGE1];


void Quit(byte *);
void Scrollejar(int POSICIO_Y,int SCROLL_Y);



void Scrollejar(int POSY,int SCROLLY,int OFFSET)
{
 int i,j,POSX;

 for(i=0;i<(ALTURA_PANTALLA_JOC+ALTURA_BLOC);i+=ALTURA_BLOC) // [0,32,64,...,200]
 {
  POSX=0;

  for(j=0;j<AMPLADA_PANTALLA_JOC;j+=AMPLADA_BLOC) // [0,32,64,...,320]
  {
    PutBlock(j+OFFSET,i+(SCROLLY-1-ALTURA_BLOC),Blocs[Mapa[((POSY<<2)+(POSY<<1)+(POSY<<0))+POSX]],AMPLADA_BLOC,ALTURA_BLOC,0,0,AMPLADA_PANTALLA_JOC-1,ALTURA_PANTALLA_JOC-1);
    POSX++;
  }
   POSY++;
 }
}



 
void LoadPanel(byte *Panell)
{
 int i;
 byte Motiu1[]={"No s'ha pogut obrir el arxiu \"Panell.raw !!!\".\0"};
 FILE *fitxer = NULL;


 if((fitxer = fopen("grafics//panell.raw","rb")) == NULL)
 {
  Quit(Motiu1);
 }

 fread(Panell,(320-AMPLADA_PANTALLA_JOC)*ALTURA_PANTALLA_JOC,1,fitxer);

 fclose(fitxer);


}







int game()
{
 byte Motiu0[]={"Error al carregar el panell !!!.\0"};
 int Entrat1=FALS,Entrat2=FALS;
 int Retard_Pausa = MAX_RETARD_PAUSA;
 int vida = vides;
 int BossPresent = FALS;
 int ScoreActual = 0, ticks_ini, ticks_fi;
 byte *Panell = NULL;
 tInvader Invader;

 int k,j,i,temps;
 int ypos=MAX_BLOCS_Y-NUMERO_BLOCS_Y-1, yscroll=1;//ALTURA_BLOC;
 int up=0;
 int RetardInici = 0;
 int RetardTro = CERT;
 int NauInicialitzada = FALS;

 j=0;


 if((Panell = (byte *)malloc((320-AMPLADA_PANTALLA_JOC)*ALTURA_PANTALLA_JOC)) == NULL) Quit(Motiu0);





 Invader.LoadStage1();
// ClearScreen(NEGRE,VSCREEN1);
 ClearScreen(NEGRE);

 LoadPanel(Panell);

 up = 1;

 temps = 1;

 CarregarEnemicsStage1();

// WaitVRetrace();
 Scrollejar(ypos,yscroll,0);


 for(i=0;i<ALTURA_PANTALLA_JOC;i++) memcpy(ptr_video+(i<<8)+(i<<6)+AMPLADA_PANTALLA_JOC,Panell+i*(320-AMPLADA_PANTALLA_JOC),(320-AMPLADA_PANTALLA_JOC));
 Flip_Video();

 CopiaPaleta(paleta2,paleta1,0,256);
 paleta2[COLOR_MASCARA].r = 255;
 paleta2[COLOR_MASCARA].g = 255;
 paleta2[COLOR_MASCARA].b = 255;
 paleta2[15].r = 0;
 paleta2[15].g = 150;
 paleta2[15].b = 150;


 SetPalette(paleta2,0,256);
 


 do{

   ticks_ini = SDL_GetTicks();

   if(!BossPresent)
   {
    if((temps % 2 == 0)&&(ypos>7))
    {
 
     if(j<243 && up) {j+=12;ModificarColorPaleta(paleta2,j,j,j,COLOR_MASCARA);} else up=0;
     if(j>12 && !up) {j-=12;ModificarColorPaleta(paleta2,j,j,j,COLOR_MASCARA);} else up=1;

    }
   }
   else
   {
    if(j<243 && up) {j+=12;ModificarColorPaleta(paleta2,j,0,0,224);} else up=0;
    if(j>12 && !up) {j-=12;ModificarColorPaleta(paleta2,j,0,0,224);} else up=1;
    if(k>0) {k-=12;ModificarColorPaleta(paleta2,k,k,k,COLOR_MASCARA);}
   }
 
  if(temps > 100)
  {
   Scrollejar(ypos,yscroll,0);
   if(((temps%5)==0)&&(ypos>0))
   {

    
    if((yscroll % ALTURA_BLOC) == 0) {yscroll = 1;ypos--;}
    else yscroll++;
    

   }
  }

  for(i=0;i<ALTURA_PANTALLA_JOC;i++) memcpy(ptr_video+(i<<8)+(i<<6)+AMPLADA_PANTALLA_JOC,Panell+i*(320-AMPLADA_PANTALLA_JOC),(320-AMPLADA_PANTALLA_JOC));

  if((ypos==7)&&!Entrat2)
  {
  // if(SB) start_sound(sonidos[3],3,OFF);
  // if(SB) start_sound(sonidos[13],3,ON);
  // if(SB) start_sound(sonidos[12],3,OFF);
   k=0;
   Invader.AfegirEnemic(75,192,20,62,0);
   ModificarColorPaleta(paleta2,k,k,k,COLOR_MASCARA);
   Entrat2 = CERT;
  }






  for(i=0;i<MAX_ENEMICS_STAGE1;i++)
  {
   if(MatriuEnemicsStage1[i].temps==temps)
   {
    Invader.AfegirEnemic(MatriuEnemicsStage1[i].x,MatriuEnemicsStage1[i].y,MatriuEnemicsStage1[i].enemic,MatriuEnemicsStage1[i].ruta,MatriuEnemicsStage1[i].ataca);
   }
   
  }


  if((temps>2200&&temps<2900)&&(temps%10==0)) Invader.AfegirEnemic(10+rand()%190,-15,METEORIT2,59,1);

  if((temps>5000&&temps<8000)&&(temps%20==0))
  {
   Invader.AfegirEnemic(50+rand()%100,-15,ENEMIC1,59+rand()%3,1);
  }

  if((temps>6000&&temps<7000)&&(temps%40==0))
  {
   Invader.AfegirEnemic(50+rand()%100,-15,ENEMIC7,0,1);
  }

  if((temps>7000&&temps<9000)&&(temps%40==0))
  {
   Invader.AfegirEnemic(-15,10+rand()%100,ENEMIC6,44,1);
  }

  if((temps>7500&&temps<9000)&&(temps%50==0))
  {
   Invader.AfegirEnemic(223,10+rand()%100,ENEMIC6,45,1);
  }


  if(temps==11050)
  {
   for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
  }

  if(temps==11100)
  {
   for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
  }



  if(temps==3200)
  {
   Invader.AfegirEnemic(20,-15,ENEMIC8,0,1);
   Invader.AfegirEnemic(104,-15,ENEMIC1,59,1);
   Invader.AfegirEnemic(190,-15,ENEMIC8,0,1);
  }




  if(RetardTro == 0)
  {
   k=255;
//   if(SB)start_sound(sonidos[21],21,OFF);
   RetardTro = 100 + rand()&550;

  }
  else
  {
  // if(BossPresent) RetardTro--;
  }

  if((ypos==1&&yscroll==2)&&!Entrat1)
  {
//   if(SB)
//   {stop_sound(3);
//    stop_sound(12);
//    stop_sound(13);
//    start_sound(sonidos[4], 4, ON);
//    start_sound(sonidos[11],11,OFF);
//   }
   for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
   Invader.AfegirEnemic(80,-61,20,50,1);
   BossPresent = CERT;
   k=0;RetardTro = 100 + rand()%500;
   Entrat1 = CERT;
  }


  if(Invader.NauDestruida()) {RetardInici = 0;NauInicialitzada=FALS;}

  if(!NauInicialitzada)
  {
	/*  if(RetardInici == 100)
	  {
		  printf("");
	  }*/
   if(RetardInici<100) RetardInici++;
   else {vida--; if(!((vida<0))){Invader.InicialitzaNau();Invader.EntrarBombes(3);NauInicialitzada = CERT;}}
  }
  OutText(230,75,"Puntuacio:\0",1,0,0,FONTMT);

  if(vida<0)  Visualitzar_Numero(225,141,0,5,1);
  else  Visualitzar_Numero(225,141,vida,5,1);
  Visualitzar_Numero(246,90,puntuacio=(dword)Invader.PuntuacioActual(),7,1);
  Visualitzar_Numero(225,166,(dword)Invader.EntregarBombes(),5,1);

//  Visualitzar_Numero(0,0,(dword)coreleft()+(dword)farcoreleft(),7,2,VSCREEN1);

/*if(temps == 10000)
{
	printf("");
}*/
  Invader.Actualitzar();



  if(TECLA_PAUSA && (Retard_Pausa==0))
  {
   while(TECLA_PAUSA);
   while(!TECLA_PAUSA);
   Retard_Pausa = MAX_RETARD_PAUSA;
  }


//  WaitVRetrace();
 

  if(Retard_Pausa>0) Retard_Pausa--;
  if(!BossPresent) temps ++;

  ticks_fi = SDL_GetTicks();

  while((ticks_fi - ticks_ini) < 15) ticks_fi = SDL_GetTicks();

  Flip_Video();

 }while(!TECLA_ESCAPE && !Invader.BOSSDESTROYED()&&!(vida<0));

 paleta2[COLOR_MASCARA].r = 0;
 paleta2[COLOR_MASCARA].g = 0;
 paleta2[COLOR_MASCARA].b = 0;


 //FadeOut(paleta2,0,256);

for(i=0;i<64;i++)
{
	for(j=0;j<256;j++)
	{
 
	  if(paleta2[j].r>4) paleta2[j].r-=4;
	  if(paleta2[j].g>4) paleta2[j].g-=4;
	  if(paleta2[j].b>4) paleta2[j].b-=4;

  


	}
SetPalette(paleta2,0,256);
}
 /*if(SB)
 {
  for(i=0;i<NUMSOUNDS;i++) stop_sound(i);                                                  // detiene motor jet
 }*/

 free(Panell);

 ClearScreen(NEGRE);
// SetPalette(paleta1,0,255);
// ModificarColorPaleta(63,63,63,15);
// ClearScreen(NEGRE,VIDEO);

 Invader.UnLoadStage1();

// credits();


 if(Invader.PuntuacioActual()>maxima_puntuacio) maxima_puntuacio = Invader.PuntuacioActual();

 if(Invader.BOSSDESTROYED())return 1;
 else if(vida<0) return 2;
      else return 0;
}



