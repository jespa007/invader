#include "invader.h"

byte * BUFFER1 = NULL;
word VSCREEN1;

void main()
{
 word n,i;
 tPosicio mouse;
 FILE *f=NULL;

 BUFFER1=(byte *)malloc(64000);
 BUFFER1=(byte *)MK_FP(FP_SEG(BUFFER1),0);
 VSCREEN1=FP_SEG(BUFFER1);

 f=fopen("grafics//options.raw",BUFFER1);

for(i=0;i<200;i++)
{
 n=fread(BUFFER1,i*320,1,f);
 printf("%i",n);
 getch();
}

 SetMode13();
 





 MostrarPunter();
 do{
  Posicio_Mouse(&mouse);
  PColor(mouse.x,mouse.y,VSCREEN1);
 }while(!kbhit());
 getch();
 SetMode3();
 fclose(f);
}
