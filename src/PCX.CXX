#include "pcx.h"



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



word ShowPcxX(byte *nom,word intensitat,byte *paleta1,byte page)
{
 // Descripci¢: Carrega un PCX utilitzant rutines
 //             MODEX.

 struct capcalera PCX;
 FILE *Xfitxer;
 byte BYTE,color; // 1 byte
 word x,y,repeticio; // 1 word
 word Xcontador; // 1 word
 tpaleta paleta2;

 if( (Xfitxer = fopen(nom,"rb")) == NULL)
 {
  return 1;
 }


 // Llegim cap‡alera.

 fread((char *)&PCX,1,sizeof(PCX),Xfitxer);

 // Ja tenim les variables de la cap‡alera inicilitzades.

 // Mirem si ‚s un PCX v…lid.

 if(PCX.idpcx != 0x0a)  // PCX no es v…lid.
 {
  return 2;
 }

 // Ens posicionem a la paleta del PCX.(es troba al final del fitxer PCX).

 fseek(Xfitxer,-768L,SEEK_END);

 // Llegim la paleta.

 fread(paleta1,768,1,Xfitxer);

 // Decodificaci¢ de la paleta.

 for(Xcontador=0;Xcontador<768;Xcontador++) paleta2[Xcontador]=paleta1[Xcontador]>>2; // Dividim per 4.

 // Set Up Palette.

 for(Xcontador=0;Xcontador<768;Xcontador++) paleta1[Xcontador]=(paleta2[Xcontador]*intensitat)>>8; // Dividim per 256.

 // Ens saltem la cap‡alera.

 fseek(Xfitxer,128L,SEEK_SET);

 x = PCX.d_x1; y = PCX.d_y1;

 repeticio = 0;

 while(y<PCX.d_y2+1)
 {
  BYTE = color = fgetc(Xfitxer);

  if((BYTE & 192) == 192)
  {
   repeticio += (color&63);
   color = fgetc(Xfitxer);
  } else ++repeticio;
  for(;x<repeticio;x++)

   PutPixelX(x,y,color,page);

  if(x>PCX.d_x2)
  {
   x = repeticio = 0;
   ++y;
  }

 }

 fclose(Xfitxer);
 return 0;
           
}

