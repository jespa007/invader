//#include "Invader.cc"
#include "Enemics.h"

extern INFO_ENEMY MatriuEnemicsStage1[MAX_ENEMICS_STAGE1];


void Quit(byte *);





 
void LoadPanel(byte *Panell)
{
 int i;
 byte Motiu1[]={"No s'ha pogut obrir el arxiu \"Panell.raw !!!\".\0"};
 FILE *fitxer = NULL;


 if((fitxer = fopen("grafics//panell.raw","rb")) == NULL)
 {
  Quit(Motiu1);
 }

 fread(Panell,(320-AMPLADA_PANTALLA)*ALTURA_PANTALLA,1,fitxer);

 fclose(fitxer);


}







int game()
{
 byte Motiu0[]={"Error al carregar el panell !!!.\0"};
 int Entrat1=FALS,Entrat2=FALS;
 int Retard_Pausa = MAX_RETARD_PAUSA;
 int vida = vides;
 int BossPresent = FALS;
 int ScoreActual = 0;
 byte *Panell = NULL;
 tInvader Invader;

 int k,j,i;
 int ypos=MAX_BLOCS_Y-NUMERO_BLOCS_Y-1, yscroll=1;//ALTURA_BLOC;
 int up=0;
 int RetardInici = 0;
 int RetardTro = CERT;
 int NauInicialitzada = FALS;

 j=0;


 if((Panell = (byte *)malloc((320-AMPLADA_PANTALLA)*ALTURA_PANTALLA)) == NULL) Quit(Motiu0);





 Invader.LoadStage1();
 ClearScreen(NEGRE,VSCREEN1);
 ClearScreen(NEGRE,VIDEO);

 LoadPanel(Panell);

 up = 1;

 temps =1;

 CarregarEnemicsStage1();

 WaitVRetrace();
 Scrollejar(ypos,yscroll,0,VSCREEN1);


 for(i=0;i<ALTURA_PANTALLA;i++) memcpy(BUFFER1+(i<<8)+(i<<6)+AMPLADA_PANTALLA,Panell+i*(320-AMPLADA_PANTALLA),(320-AMPLADA_PANTALLA));
 Flip_VScreen(VIDEO,VSCREEN1);

 CopiaPaleta(paleta2,paleta1,0,255);
 paleta2[COLOR_MASCARA*3] = 63;
 paleta2[COLOR_MASCARA*3+1]= 63;
 paleta2[COLOR_MASCARA*3+2]= 63;
 paleta2[15*3] = 63;
 paleta2[15*3+1]= 63;
 paleta2[15*3+2]= 63;



 SetPalette(paleta2,0,255);
 


 do{

   if(!BossPresent)
   {
    if((temps % 2 == 0)&&(ypos>7))
    {
 
     if(j<60 && up) {j+=3;ModificarColorPaleta(j,j,j,COLOR_MASCARA);} else up=0;
     if(j>3 && !up) {j-=3;ModificarColorPaleta(j,j,j,COLOR_MASCARA);} else up=1;

    }
   }
   else
   {
    if(j<60 && up) {j+=3;ModificarColorPaleta(j,0,0,224);} else up=0;
    if(j>3 && !up) {j-=3;ModificarColorPaleta(j,0,0,224);} else up=1;
    if(k>0) {k-=3;ModificarColorPaleta(k,k,k,COLOR_MASCARA);}
   }
 
  if(temps > 100)
  {
   Scrollejar(ypos,yscroll,0,VSCREEN1);
   if(((temps%5)==0)&&(ypos>0))
   {

    /*
    if((yscroll % ALTURA_BLOC) == 0) {yscroll = 1;ypos--;}
    else yscroll++;
    */

   }
  }

  for(i=0;i<ALTURA_PANTALLA;i++) memcpy(BUFFER1+(i<<8)+(i<<6)+AMPLADA_PANTALLA,Panell+i*(320-AMPLADA_PANTALLA),(320-AMPLADA_PANTALLA));

  if((ypos==7)&&!Entrat2)
  {
   if(SB) start_sound(sonidos[3],3,OFF);
   if(SB) start_sound(sonidos[13],3,ON);
   if(SB) start_sound(sonidos[12],3,OFF);
   k=0;
   Invader.AfegirEnemic(75,192,20,62,0);
   ModificarColorPaleta(k,k,k,COLOR_MASCARA);
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
   k=63;
   if(SB)start_sound(sonidos[21],21,OFF);
   RetardTro = 100 + rand()&550;

  }
  else
  {
   if(BossPresent) RetardTro--;
  }

  if((ypos==1&&yscroll==2)&&!Entrat1)
  {
   if(SB)
   {stop_sound(3);
    stop_sound(12);
    stop_sound(13);
    start_sound(sonidos[4], 4, ON);
    start_sound(sonidos[11],11,OFF);
   }
   for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
   Invader.AfegirEnemic(80,-61,20,50,1);
   BossPresent = CERT;
   k=0;RetardTro = 100 + rand()%500;
   Entrat1 = CERT;
  }


  if(Invader.NauDestruida()) {RetardInici = 0;NauInicialitzada=FALS;}

  if(!NauInicialitzada)
  {
   if(RetardInici<100) RetardInici++;
   else {vida; if(!((vida<0))){Invader.InicialitzaNau();Invader.EntrarBombes(3);NauInicialitzada = CERT;}}
  }
  OutText(230,75,"Puntuacio:\0",3,0,0,FONTMT,VSCREEN1);

  if(vida<0)  Visualitzar_Numero(225,141,0,5,3,VSCREEN1);
  else  Visualitzar_Numero(225,141,vida,5,3,VSCREEN1);
  Visualitzar_Numero(246,90,puntuacio=(dword)Invader.PuntuacioActual(),7,3,VSCREEN1);
  Visualitzar_Numero(225,166,(dword)Invader.EntregarBombes(),5,3,VSCREEN1);

  Visualitzar_Numero(0,0,(dword)coreleft()+(dword)farcoreleft(),7,2,VSCREEN1);


  Invader.Actualitzar();



  if(letras[P]&&(Retard_Pausa==0))
  {
   while(letras[P]);
   while(!letras[P]);
   Retard_Pausa = MAX_RETARD_PAUSA;
  }


  WaitVRetrace();
  Flip_VScreen(VIDEO,VSCREEN1);

  if(Retard_Pausa>0) Retard_Pausa--;
  if(!BossPresent) temps ++;

 }while(!letras[ESCAPE]&&!Invader.BOSSDESTROYED()&&!(vida<0));

 paleta2[COLOR_MASCARA*3] = 0;
 paleta2[COLOR_MASCARA*3+1]= 0;
 paleta2[COLOR_MASCARA*3+2]= 0;



for(j=0;j<63;j++)
{
 for(i=0;i<768;i++)
 {
  if(paleta2[i]>0) paleta2[i]--;
 }
 WaitVRetrace();
 SetPalette(paleta2,0,255);

}
 if(SB)
 {
  for(i=0;i<NUMSOUNDS;i++) stop_sound(i);                                                  // detiene motor jet
 }

 free(Panell);

 ClearScreen(NEGRE,VIDEO);
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



