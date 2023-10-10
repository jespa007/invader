#include "invader.h"


// Respecte els color.

#define START_COLOR_BORDER 227
#define OPTIONS_COLOR_BORDER 16
#define QUIT_COLOR_BORDER 136



#define DIFICULT_LEVEL_BORDER_1 16
#define DIFICULT_LEVEL_BORDER_2 227

#define LIVES_BORDER_1          159
#define LIVES_BORDER_2          67


int menu();
void options();


int menu()
{
 tPosicio mouse;
 int i1=0,i2=0,i3=0,ok1=FALS,ok2=FALS,ok3=FALS;
 int up1=CERT,up2=CERT,up3=CERT;
 int StartTicks;




 ModificarColorPaleta(paleta3,0,0,0,227);
 ModificarColorPaleta(paleta3,0,0,0,16);
 ModificarColorPaleta(paleta3,0,0,0,136);


 for(;;)
 {

     StartTicks = SDL_GetTicks();

  Posicio_Mouse(&mouse);

  if((mouse.x<205)&&(mouse.x>95)&&(mouse.y>152)&&(mouse.y<160))
  {
   if(!ok1)
   {
    ok1=CERT;
    ok2=FALS;
    ok3=FALS;
   }
   if((i1<248)&&up1) {i1+=6;ModificarColorPaleta(paleta3,i1,0,0,227);}
   else up1 = FALS;
   if((i1>6)&&!up1){i1-=6;ModificarColorPaleta(paleta3,i1,0,0,227);}
   else up1 = CERT;
   if(Buto_Pitjat()==BUTO_MOUSE_ESQUERRE)
   {
    ModificarColorPaleta(paleta3,0,0,0,227);
    ModificarColorPaleta(paleta3,0,0,0,16);
    ModificarColorPaleta(paleta3,0,0,0,136);
    return(0);
   }

  }else ok1 = FALS;


  if((mouse.x<180)&&(mouse.x>120)&&(mouse.y>168)&&(mouse.y<177))
  {
   if(!ok2)
   {
    ok1=FALS;
    ok2=CERT;
    ok3=FALS;
   }
   if((i2<248)&&up2) {i2+=6;ModificarColorPaleta(paleta3,i2,0,0,OPTIONS_COLOR_BORDER);}
   else up2 = FALS;
   if((i2>6)&&!up2){i2-=6;ModificarColorPaleta(paleta3,i2,0,0,OPTIONS_COLOR_BORDER);}
   else up2 = CERT;
   if(Buto_Pitjat()==BUTO_MOUSE_ESQUERRE)
   {
    ModificarColorPaleta(paleta3,0,0,0,227);
    ModificarColorPaleta(paleta3,0,0,0,16);
    ModificarColorPaleta(paleta3,0,0,0,136);
    return(1);
   }

  }else ok2 = FALS;

  if((mouse.x<176)&&(mouse.x>124)&&(mouse.y>184)&&(mouse.y<193))
  {
   if(!ok3)
   {
    ok1=FALS;
    ok2=FALS;
    ok3=CERT;
   }
   if((i3<248)&&up3) {i3+=6;ModificarColorPaleta(paleta3,i3,0,0,QUIT_COLOR_BORDER);}
   else up3 = FALS;
   if((i3>6)&&!up3){i3-=6;ModificarColorPaleta(paleta3,i3,0,0,QUIT_COLOR_BORDER);}
   else up3 = CERT;
   if(Buto_Pitjat()==BUTO_MOUSE_ESQUERRE)
   {
    ModificarColorPaleta(paleta3,0,0,0,227);
    ModificarColorPaleta(paleta3,0,0,0,16);
    ModificarColorPaleta(paleta3,0,0,0,136);
    return(2);
   }


  }else ok3 = FALS;



   if(!ok1)
   {

    if(i1>3)
    {
     i1-=2;
     ModificarColorPaleta(paleta3,i1,0,0,227);
    }
    else up1 = CERT;

   }


   if(!ok2)
   {

    if(i2>6)
    {
     i2-=6;
     ModificarColorPaleta(paleta3,i2,0,0,OPTIONS_COLOR_BORDER);
    }
    else up2 = CERT;

   }

   if(!ok3)
   {

    if(i3>3)
    {
     i3-=6;
     ModificarColorPaleta(paleta3,i3,0,0,QUIT_COLOR_BORDER);
    }
    else up3 = CERT;

   }




//  WaitVRetrace();
   while((SDL_GetTicks() - StartTicks) < 16);
    Flip_Video();
 }
 return -1;

}





void options()
{


 char background1[AMPLADA_LLETRAM*ALTURA_LLETRAM*7];  // Fons per les lletres
 char background2[AMPLADA_LLETRAM*ALTURA_LLETRAM];   // Fons per les lletres


 int disabled = FALS;
 int StartTicks;
 tPosicio mouse;
 int sortir = FALS;
 int i1=0,i2=0,i3=0,i4=0,i5=0;
 char ok=0x00;
 char up=0x01;


 SetPalette(paleta2,0,256);

 Flip_VScreen(ptr_video,BUFFER2);

 // Carrego el fons...

 GetBlock(134,60,background1,7*AMPLADA_LLETRAM,ALTURA_LLETRAM,BUFFER2);
 GetBlock(130,96,background2,AMPLADA_LLETRAM,ALTURA_LLETRAM,BUFFER2);




    switch(dificultat)
   {
 
    case FACIL:  OutText(134,60,"FACIL\0",0,0,0,MEDFNT);break;
    case MITJANA:  OutText(134,60,"MITJA\0",0,0,0,MEDFNT);break;
    case DIFICIL: OutText(134,60,"DIFICIL\0",0,0,0,MEDFNT);
   }


   switch(vides)
   {
   case 1:  OutText(130,96,"1\0",0,0,0,MEDFNT);break;
   case 2:  OutText(130,96,"2\0",0,0,0,MEDFNT);break;
   case 3:  OutText(130,96,"3\0",0,0,0,MEDFNT);break;
   case 4:  OutText(130,96,"4\0",0,0,0,MEDFNT);
  }

 FadeIn(paleta3,0,256);
 MostrarPunter();





 ModificarColorPaleta(paleta3,0,0,0,227);

 ModificarColorPaleta(paleta3,0,0,0,16);
 ModificarColorPaleta(paleta3,0,0,0,136);
 ModificarColorPaleta(paleta3,0,0,0,67);
 ModificarColorPaleta(paleta3,0,0,0,159);

 temps = 0;

 do{

    StartTicks = SDL_GetTicks();

    Posicio_Mouse(&mouse);


    if(disabled) temps++;
    if((temps>12) && (disabled))
    {
     disabled = FALS;
    }




    if(DIFICULT_LEVEL_BORDER_1==GetPixel(mouse.x,mouse.y))
    {
     if(!(ok & 0x10)) ok = 0x10;
     if((i1<248)&&(up&0x10)) {i1+=6;ModificarColorPaleta(paleta3,i1,0,0,DIFICULT_LEVEL_BORDER_1);}
     else up = up&0x0F;
     if((i1>6)&&!(up&0x10)){i1-=6;ModificarColorPaleta(paleta3,i1,0,0,DIFICULT_LEVEL_BORDER_1);}
     else up = up|0x10;
     if((Buto_Pitjat() ==BUTO_MOUSE_ESQUERRE) && !disabled)
     {


      if(dificultat>FACIL)
      {
       dificultat--;
       PutBlock(134,60,background1,AMPLADA_LLETRAM*7,ALTURA_LLETRAM,0,0,319,199);
      
      switch(dificultat)
      {
        case FACIL:  OutText(134,60,"FACIL\0",0,0,0,MEDFNT);break;
        case MITJANA:  OutText(134,60,"MITJA\0",0,0,0,MEDFNT);break;
        case DIFICIL:  OutText(134,60,"DIFICIL\0",0,0,0,MEDFNT);
      }
//      if(SB)start_sound(sonidos[7],7,OFF);
      disabled = CERT;
      temps = 0;
     }

     }
    }else{ ok=ok&0x0F;}


    if(DIFICULT_LEVEL_BORDER_2==GetPixel(mouse.x,mouse.y))
    {
     if(!(ok & 0x08)) ok = 0x08;
     if((i2<248)&&(up&0x08)) {i2+=6;ModificarColorPaleta(paleta3,i2,0,0,DIFICULT_LEVEL_BORDER_2);}
     else up = up&0x17;
     if((i2>6)&&!(up&0x08)){i2-=6;ModificarColorPaleta(paleta3,i2,0,0,DIFICULT_LEVEL_BORDER_2);}
     else up = up|0x08;
     if((Buto_Pitjat()==BUTO_MOUSE_ESQUERRE) && !disabled)
     {


      if(dificultat<DIFICIL)
      {
       dificultat++;
       PutBlock(134,60,background1,AMPLADA_LLETRAM*7,ALTURA_LLETRAM,0,0,319,199);
       switch(dificultat)
       {
        case FACIL:  OutText(134,60,"FACIL\0",0,0,0,MEDFNT);break;
        case MITJANA:  OutText(134,60,"MITJA\0",0,0,0,MEDFNT);break;
        case DIFICIL:  OutText(134,60,"DIFICIL\0",0,0,0,MEDFNT);
       }
//       if(SB)start_sound(sonidos[7],7,OFF);
       disabled = CERT;
       temps = 0;
       SDL_Delay(50);
      }
     }
    }else ok=ok&0x17;

    if(LIVES_BORDER_1==GetPixel(mouse.x,mouse.y))
    {
     if(!(ok & 0x04)) ok = 0x04;
     if((i3<248)&&(up&0x04)) {i3+=6;ModificarColorPaleta(paleta3,i3,0,0,LIVES_BORDER_1);}
     else up = up&0x1B;
     if((i3>6)&&!(up&0x04)){i3-=6;ModificarColorPaleta(paleta3,i3,0,0,LIVES_BORDER_1);}
     else up = up|0x04;
     if((Buto_Pitjat()==BUTO_MOUSE_ESQUERRE) && !disabled)
     {
      PutBlock(130,96,background2,AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,319,199);
      if(vides>1)
      {vides --;/*if(SB)start_sound(sonidos[7],7,OFF);*/}
      switch(vides)
      {
       case 1:  PutChar(130,96,traduccio_caracter(toupper('1')),0,0,0,0,MEDFNT);break;
       case 2:  PutChar(130,96,traduccio_caracter(toupper('2')),0,0,0,0,MEDFNT);break;
       case 3:  PutChar(130,96,traduccio_caracter(toupper('3')),0,0,0,0,MEDFNT);break;
       case 4:  PutChar(130,96,traduccio_caracter(toupper('4')),0,0,0,0,MEDFNT);break;
      }
      disabled = CERT;
      temps = 0;
      SDL_Delay(50);

     }
    }else{ ok=ok&0x1B;}

    if(LIVES_BORDER_2==GetPixel(mouse.x,mouse.y))
    {
     if(!(ok&0x02)) ok = 0x02;
     if((i4<248)&&(up&0x02)) {i4+=6;ModificarColorPaleta(paleta3,i4,0,0,LIVES_BORDER_2);}
     else up = up&0x1D;
     if((i4>6)&&!(up&0x02)){i4-=6;ModificarColorPaleta(paleta3,i4,0,0,LIVES_BORDER_2);}
     else up = up|0x02;
     if((Buto_Pitjat()==BUTO_MOUSE_ESQUERRE) && !disabled)
     {
      PutBlock(130,96,background2,AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,320-1,200-1);

      if(vides<MAX_VIDES)
      {vides ++;/*if(SB)start_sound(sonidos[7],7,OFF);*/}

      switch(vides)
      {
       case 1:  PutChar(130,96,traduccio_caracter(toupper('1')),0,0,0,0,MEDFNT);break;
       case 2:  PutChar(130,96,traduccio_caracter(toupper('2')),0,0,0,0,MEDFNT);break;
       case 3:  PutChar(130,96,traduccio_caracter(toupper('3')),0,0,0,0,MEDFNT);break;
       case 4:  PutChar(130,96,traduccio_caracter(toupper('4')),0,0,0,0,MEDFNT);break;
      }

      disabled = CERT;
      temps = 0;
      SDL_Delay(50);

     }
    }else ok=ok&0x1D;

   if((mouse.x<182)&&(mouse.x>134)&&(mouse.y>157)&&(mouse.y<183))
   {
    if(!(ok&0x01)) ok=0x01;
    if((i5<248)&&(up&0x01)) {i5+=6;ModificarColorPaleta(paleta3,i5,0,0,QUIT_COLOR_BORDER);}
    else up = up&0x1E;
    if((i5>6)&&!(up&0x01)){i5-=6;ModificarColorPaleta(paleta3,i5,0,0,QUIT_COLOR_BORDER);}
    else up = up|0x01;
    if(Buto_Pitjat()==BUTO_MOUSE_ESQUERRE)
    {
//     if(SB)start_sound(sonidos[6],6,OFF);
     sortir = CERT;
    }
   }else ok=ok&0x1E;



   if(!(ok&0x10))
   {

    if(i1<248)
    {
     i1+=6;
     ModificarColorPaleta(paleta3,i1,0,0,DIFICULT_LEVEL_BORDER_1);
    }
    else up = up&0x0F;

   }


   if(!(ok&0x08))
   {

    if(i2<248)
    {
     i2+=6;
     ModificarColorPaleta(paleta3,i2,0,0,DIFICULT_LEVEL_BORDER_2);
    }
    else up = up&0x17;

   }

   if(!(ok&0x04))
   {

    if(i3<248)
    {
     i3+=6;
     ModificarColorPaleta(paleta3,i3,0,0,LIVES_BORDER_1);
    }
    else  up = up&0x1B;

   }


   if(!(ok&0x02))
   {

    if(i4<248)
    {
     i4+=6;
     ModificarColorPaleta(paleta3,i4,0,0,LIVES_BORDER_2);
    }
    else up = up&0x1D;

   }

   if(!(ok&0x01))
   {

    if(i5>6)
    {
     i5-=6;
     ModificarColorPaleta(paleta3,i5,0,0,QUIT_COLOR_BORDER);
    }
    else up = up|0x01;

   }

   while((SDL_GetTicks()-StartTicks) < 16);

//   WaitVRetrace(); 	
   Flip_Video();
   //SDL_Delay(50);

 }while(!sortir);
 ModificarColorPaleta(paleta3,0,0,0,227);
 ModificarColorPaleta(paleta3,0,0,0,16);
 ModificarColorPaleta(paleta3,0,0,0,136);
 ModificarColorPaleta(paleta3,0,0,0,67);
 ModificarColorPaleta(paleta3,0,0,0,159);
 FadeOut(paleta3,0,256);

 


 //OcultarPunter();
}




