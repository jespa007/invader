#include "pcx.h"
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>






int main(int argc,char *argv[])
{
 byte nom[40];
 byte nom2[40];
 word intensitat = 255;
 byte paleta1[768];
 word segment;

 // Descripci¢: Carrega un PCX.

 byte paleta2[768];

 struct capcalera PCX;
 FILE *fitxer = NULL;
 FILE *fitxer2 = NULL;

 byte BYTE,color; // 1 byte
 word x,y,repeticio; // 1 word
 word contador; // 1 word
 dword longitud; // 2 word

 if(argc < 3)
 {
  fprintf(stderr, "N§ de parametres incorrecte !");
  return 1;
 }
 


 if( (fitxer = fopen(argv[1],"rb")) == NULL)
 {

  printf("Error, no s'ha pogut obrir el fitxer %s ,ho sento.\n\n",argv[1]);
  return 1;
 }

 if( (fitxer2 = fopen(argv[2],"wb+")) == NULL)
 {
  printf("Error, no s'ha pogut obrir el fitxer %s ,ho sento.\n\n",argv[2]);
  return 1;
 }



 // Llegim cap‡alera.

 fread((char *)&PCX,1,sizeof(PCX),fitxer);

 // Ja tenim les variables de la cap‡alera inicilitzades.

 // Mirem si ‚s un PCX v…lid.

 if(PCX.idpcx!=0x0a)  // PCX no es v…lid.
 {
  //cerr << "Error, el fitxer " << nom << "no es un PCX v…lid,ho sento.\n\n";
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

 
 x = PCX.d_x2; y = PCX.d_y2;

 fwrite((char *)&x,1,sizeof(x),fitxer2);

 fwrite((char *)&y,1,sizeof(y),fitxer2);

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
   {
    fputc(color,fitxer2);
   }
  if(x>PCX.d_x2)
  {
   x = repeticio = 0;
   ++y;
  }
 }


 fclose(fitxer);
 fclose(fitxer2);

 return 0;

}










