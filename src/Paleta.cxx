#include "invader.h"


//   ���������������������ͻ
//   �                     �
//   �  UTILITATS PALETA   �
//   �                     �
//   ���������������������ͼ




//***********- Modificar un color -**********************/


void ModificarColorPaleta(tColor *paleta,unsigned char  R,unsigned char  G,unsigned char  B,unsigned char numcolor)
{

   paleta[numcolor].r=R;
   paleta[numcolor].g=G;
   paleta[numcolor].b=B;

   SDL_SetColors(Video, paleta, 0, 256);

}

/*

//***** DAC => PALETA *****


void GetPalette(byte far *paleta,word inici,word final)
{
 final=(final<<1)+(final<<0); // final*=3;
 inici=(inici<<1)+(inici<<0); // inici*=3;
 final=(final-inici)+3;

 asm{
     les di,paleta // llegeix   //
     add di,[inici]
     mov dx,3c7h // Registre de Lectura PEL//
     xor al,al // mov al,0 //
     out dx,al // Volem comen�ar a llegir el valor 0 del DAC //
     inc dx
     inc dx     // dx = 3c9h escriu en VIDEO //
     mov cx,[final] // 256x3 posicions que hem de fer referencia. //
     rep insb // Inserim els valors al vector entrat.//
    }
}

*/
//****** PALETA => DAC ******


void SetPalette(tColor *paleta,int inici,int final)
{
	if(inici < 0 || final > 256) return;

	SDL_SetPalette(Video, SDL_LOGPAL|SDL_PHYSPAL, paleta, inici, final);
}


int  CarregarPaleta(char *NOM_PALETA,tColor *PALETA)
{
 
 int x;
 FILE *file;
 
 if( (file = fopen (NOM_PALETA,"rb")) == NULL)
 {
  return 0;
 }

 for(x=0;x<256;x++) 
 {

	  // La paleta a carrega defineix 6 bits per cada component rgb. Per aix�, s'ha de amplificar
	  // x4, perqu� SDL utilitza els 8 bits per cada component.
	 
	  PALETA[x].r = fgetc(file) << 2;
	  PALETA[x].g = fgetc(file) << 2;
	  PALETA[x].b = fgetc(file) << 2;

 }

 fclose(file);

 return 1;

}


void CopiaPaleta(tColor *pal_dest,tColor *pal_origen,int inici,int final)
{
 int i;
 for(i=inici; i<final ;i++) 
 {
	 pal_dest[i].r = pal_origen[i].r;
	 pal_dest[i].g = pal_origen[i].g;
	 pal_dest[i].b = pal_origen[i].b;
 }
}







void XchangeColor(tColor *paleta,char color1,char color2)
{
 // Intercanvia un color de una paleta.
 tColor Color_Aux;

 Color_Aux.r = paleta[color1].r;
 Color_Aux.g = paleta[color1].g;
 Color_Aux.b = paleta[color1].b;
 
 paleta[color1].r = paleta[color2].r;
 paleta[color1].g = paleta[color2].g;
 paleta[color1].b = paleta[color2].b;
 
 paleta[color2].r = Color_Aux.r;
 paleta[color2].g = Color_Aux.g;
 paleta[color2].b = Color_Aux.b;
}


void PaletaNegre(tColor *paleta,int inici,int final)
{
 int i;
 for(i=inici;i<final;i++) { paleta[i].r=0;paleta[i].g=0;paleta[i].b=0;}
}

void PaletaBlanca(tColor *paleta,int inici,int final)
{
 int i;
 for(i=inici;i<final;i++) {paleta[i].r=255,paleta[i].b=255;paleta[i].b=255;}
}




void VisualitzarPaleta(void)
{
 int color_actual,y=20,x=0;
 char longitud;
 OutText(centred(160,13),5,"PALETA ACTUAL\0",0,0,0,FONTMT);

 for(color_actual=0;color_actual< 256; color_actual++)
 {
  if((color_actual+1<10)&&(color_actual+1>=0)) longitud=1;
  if((color_actual+1<100)&&(color_actual+1>=10)) longitud=2;
  if((color_actual+1>=100)) longitud=3;
  rectangle_ple(x,y,23,8,color_actual);
  Visualitzar_Numero(x,y,int(color_actual+1),longitud,0);
  x+=24;
  if(x>305) {y+=9; x=0;}

 }
}

















//   ������������������ͻ
//   �                  �
//   �  EFECTES PALETA  �
//   �                  �
//   ������������������ͼ





void FadeOut(tColor *paleta,int inici,int final)
{
 tPaleta paleta4;
 int StartTicks;

 int x,y;

 CopiaPaleta(paleta4,paleta,inici,final);

 for(y=0;y<64;y++)
 {

  StartTicks = SDL_GetTicks();

  for(x=inici;x<final;x++)
  {
   if (paleta4[x].r>4) paleta4[x].r-= 4;
   else paleta4[x].r = 0;
   if (paleta4[x].g>4) paleta4[x].g-= 4;
   else paleta4[x].g = 0;
   if (paleta4[x].b>4) paleta4[x].b-= 4;
   else paleta4[x].b = 0;
  }

  SetPalette(paleta4,inici,final);
  while((SDL_GetTicks() - StartTicks) < 16);

 }
}



void FadeIn(tColor *paleta,int inici,int final)
{
 tPaleta paleta2;
 int StartTicks;

 int x,y;

 PaletaNegre(paleta2,inici,final);
 SetPalette(paleta2,inici,final);

 for(y=0;y<64;y++)
 {
StartTicks = SDL_GetTicks();
  for(x=inici;x<final;x++)
  {

   if (paleta2[x].r<paleta[x].r) paleta2[x].r += 4;
   else paleta2[x].r = paleta[x].r;
   if (paleta2[x].b<paleta[x].b) paleta2[x].b += 4;
   else paleta2[x].g = paleta[x].g;
   if (paleta2[x].g<paleta[x].g) paleta2[x].g += 4;
   else paleta2[x].b = paleta[x].b;

  }

  while((SDL_GetTicks() - StartTicks) < 16); 
  SetPalette(paleta2,inici,final);
 }
}


/*
void ImpactIn(word inici,word final)
{
 tPaleta paleta2;

 int x,y;

 GetPalette(paleta2,inici,final);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (paleta2[x]<63)
    paleta2[x]++;
  WaitVRetrace();
  SetPalette(paleta2,inici,final);

 }
}


void ImpactOut(byte *paleta,word inici,word final)
{
 tPaleta paleta2;
 int x,y;

 PaletaBlanca(paleta2,0,255);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (paleta[x]!=paleta2[x])
    paleta2[x]--;

  WaitVRetrace();
  SetPalette(paleta2,inici,final);
 }
}

*/


void RotatePaletteLeft(tColor *paleta,int color_i,int color_f)
{
 int i;
 tColor color_inicial;

 if(color_i >= color_f) return; // No es pot donar aquest cas...


 color_inicial = paleta[color_i];
 
 for(i = color_i; i < (color_f-1); i++)
 {

	paleta[i]=paleta[i+1];
 }

 paleta[color_f-1]=color_inicial;
 

 SetPalette(paleta,color_i,color_f);
 
}

/*
void RotatePaletteRight(byte far *paleta,word color_i,word color_f)
{
 word i;
 byte final[3];

 final[2]=paleta[color_f*3+2];
 final[1]=paleta[color_f*3+1];
 final[0]=paleta[color_f*3];

 for(i=color_f;i>color_i;i--)
 {
  paleta[i*3]=paleta[i*3-3];
  paleta[i*3+1]=paleta[i*3-2];
  paleta[i*3+2]=paleta[i*3-1];
 }
 paleta[color_i*3+2]=final[2];
 paleta[color_i*3+1]=final[1];
 paleta[color_i*3]=final[0];
 SetPalette(paleta,0,255);
 WaitVRetrace();

}



void MorphPalette(byte *pal_dest,byte* pal_origen,word inici,word final)
{
 // Descripcio: Fa una  igualtat de paletes observant el canvi k es produeix.

 word y,x;

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (pal_dest[x]<pal_origen[x])
    pal_origen[x]--;
   else
   {
      if (pal_dest[x]>pal_origen[x])
    pal_origen[x]++;


   }
  WaitVRetrace();
  SetPalette(pal_origen,inici,final);
 }


}

*/