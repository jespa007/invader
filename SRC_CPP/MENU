#include "all_lib.h"

// Respecte els color.

#define START_COLOR_BORDER 227
#define OPTIONS_COLOR_BORDER 16
#define QUIT_COLOR_BORDER 136


int menu();



int menu()
{
 int i,ok1=FALS,ok2=FALS,ok3=FALS;


 for(;;)
 {
  Posicio_Mouse(&mouse);
  if((mouse.x<205)&&(mouse.x>95)&&(mouse.y>152)&&(mouse.y<160))
  {
   if(!ok1)
   {
    up=1;
    ok1=CERT;
    ok2=FALS;
    ok3=FALS;
    i=0;
   }
   if((i<62)&&up) {i+=2;ModificarColorPaleta(i,0,0,227);}
   else up = FALS;
   if((i>3)&&!up){i-=2;ModificarColorPaleta(i,0,0,227);}
   else up = CERT;
   if(Buto_Pitjat()==BUTO_MOUSE_ESQUERRE) return(0);


  }
  else
  {
   ModificarColorPaleta(0,0,0,227);
  }
  if((mouse.x<180)&&(mouse.x>120)&&(mouse.y>168)&&(mouse.y<177))
  {
   if(!ok2)
   {
    up=1;
    ok1=FALS;
    ok2=CERT;
    ok3=FALS;
    i=0;
   }
   if((i<62)&&up) {i+=2;ModificarColorPaleta(i,0,0,OPTIONS_COLOR_BORDER);}
   else up = FALS;
   if((i>3)&&!up){i-=2;ModificarColorPaleta(i,0,0,OPTIONS_COLOR_BORDER);}
   else up = CERT;
   if(Buto_Pitjat(void)==BUTO_MOUSE_ESQUERRE) return(1);

  }
  else
  {
   ModificarColorPaleta(0,0,0,OPTIONS_COLOR_BORDER);
  }

  if((mouse.x<176)&&(mouse.x>124)&&(mouse.y>184)&&(mouse.y<193))
  {
   if(!ok3)
   {
    up=1;
    ok1=FALS;
    ok2=FALS;
    ok3=CERT;
    i=0;
   }
   if((i<62)&&up) {i+=2;ModificarColorPaleta(i,0,0,QUIT_COLOR_BORDER);}
   else up = FALS;
   if((i>3)&&!up){i-=2;ModificarColorPaleta(i,0,0,QUIT_COLOR_BORDER);}
   else up = CERT;
   if(Buto_Pitjat(void)==BUTO_MOUSE_ESQUERRE) return(2);

  }
  else
  {
   ModificarColorPaleta(0,0,0,QUIT_COLOR_BORDER);
  }

  WaitVRetrace();
 }

}
