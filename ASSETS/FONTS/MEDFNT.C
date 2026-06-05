#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <dos.h>
#include <alloc.h>


#define AMPLADA 13
#define ALTURA 15
#define LLETRES 48


typedef  unsigned int word;
typedef  unsigned char byte;
typedef  unsigned long dword;

typedef  byte tpaleta[768];

typedef struct capcalera{
                        byte idpcx; // Es un fitxer PCX v…lid ?
                        byte pcxversion; // Versio del PCX.
                        byte rle; // Comprimit amb RLE?
                        byte bitspixel; // bits per pixel.(Normalment s¢n 8 bits).
                        word d_x1;
                        word d_y1;
                        word d_x2;
                        word d_y2;
                        word d_reshor;
                        word d_resver;
                        byte paleta[48];
                        byte reservat;
                        byte n_plans;
                        word byteslinea;
		       }pcx;




void PutPixel(word x, word y, byte color, word segment)

// - Funcio que posa un punt a la pantalla. (b…sic).

{
 word despl = (y<<8)+(y<<6)+x; // Realitza un offset de 320*y+x.

 asm{
     mov es,[segment] // A on volem colocar el pixel.
     mov di,[despl]
     mov al,[color]
     mov es:[di],al
    }
}



word ShowPcx(byte *nom,word intensitat,byte *paleta1,word segment)
{
 // Descripci¢: Carrega un PCX.

 tpaleta paleta2;

 struct capcalera PCX;
 FILE *fitxer = NULL;
 byte BYTE,color; // 1 byte
 word x,y,repeticio; // 1 word
 word contador; // 1 word
 dword longitud; // 2 word


 if( (fitxer = fopen(nom,"rb")) == NULL)
 {
  return 1;
 }
 // Llegim cap‡alera.

 fread((char *)&PCX,1,sizeof(PCX),fitxer);

 // Ja tenim les variables de la cap‡alera inicilitzades.

 // Mirem si ‚s un PCX v…lid.

 if(PCX.idpcx!=0x0a)  // PCX no es v…lid.
 {
  return 2;
 }

 // Ens posicionem a la paleta del PCX.(es troba al final del fitxer PCX).

 fseek(fitxer,-768L,SEEK_END);

 // Llegim la paleta.

 fread(paleta1,768,1,fitxer);

 // Decodificaci¢ de la paleta.

 for(contador=0;contador<768;contador++) paleta2[contador]=paleta1[contador]>>2; // Dividim per 4.

 // Set Up Palette.

 for(contador=0;contador<768;contador++) paleta1[contador]=(paleta2[contador]*intensitat)>>8; // Dividim per 256.

 // Ens saltem la cap‡alera.

 fseek(fitxer,128L,SEEK_SET);

 // Decodifiquem l' arxiu.

 x = PCX.d_x1; y = PCX.d_y1;

 repeticio = 0;

 while(y<PCX.d_y2+1)
 {
  BYTE = color = fgetc(fitxer);

  if((BYTE&192)==192)
  {
   repeticio += (color&63);
   color = fgetc(fitxer);
  } else ++repeticio;
  for(;x<repeticio;x++)
   PutPixel(x,y,color,segment);
  if(x>PCX.d_x2)
  {
   x = repeticio = 0;
   ++y;
  }
 }


 fclose(fitxer);
 return 0;

}






// Carrega de caracters desde el fitxer gr…fic!


int main()
{
 tpaleta paleta1;
 unsigned char *buffer = NULL;
 unsigned int vscreen;
 int actual = 0,i,j;
 FILE *fitxer = NULL;
 



 if((buffer = (byte *)malloc((word)64000L)) == NULL)
 {
  printf("\neeeeeh, sorto pq no hi ha prou memoria...\n");
  exit(1);
 }




 buffer = MK_FP(FP_SEG(buffer),0);
 vscreen = FP_SEG(buffer);
 
 // Carrega de dades a la vscreen.

 if( (fitxer = fopen("MEDFNT.raw","wb+")) == NULL)
 {
  printf("\nError, al obrir arxiu \"MEDFNT.raw\"!!! \n");
  return(1);
 }



 if( (ShowPcx("MEDFNT.pcx",255,paleta1,vscreen)) !=0)
 {
  printf("\nError, al obrir arxiu \"MEDFNT.pcx\"!!! \n");
  return(1);
 }

 // TRansfo...

 // Primer els numeros (0,1,2,3,4,5,6,7,8,9) total son 10!!!

   for(i=0;i<ALTURA;i++)
   {

      fwrite(buffer+i*320,21*AMPLADA,1,fitxer) ; // Numeros + simbols. // 260

      fwrite(buffer+i*320+320*ALTURA,24*AMPLADA,1,fitxer) ; // Lletres 26-2. // 312 

      fwrite(buffer+i*320+320*ALTURA*2,3*AMPLADA,1,fitxer) ; // Lletres 3 . // 78 

   }

 fclose(fitxer);

/*
 if( (fitxer = fopen("colors.pal","wb+")) == NULL)
 {
  printf("\nError, al obrir arxiu \"colors.pal\"!!! \n");
  return(1);
 }

 fwrite(paleta1,768,1,fitxer);

 close(fitxer);*/

 free(buffer);

}
