#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <dos.h>



char FntMonoText[8*256]={0,126,114,114,114,114,126,0, /* 0 */
                         0,120,56,56,56,56,56,0,      /* 1 */
                         0,124,28,124,112,124,124,0,  /* 2 */
                         0,124,28,124,28,124,124,0,   /* 3 */
                         0,116,116,124,28,28,28,0,    /* 4 */
                         0,124,112,124,28,124,124,0,  /* 5 */
                         0,124,112,124,116,124,124,0, // 6 */
                         0,124,28,60,28,28,28,0,      //* 7 */
                         0,124,116,124,116,124,124,0, //* 8 */
                         0,124,92,124,28,28,28,0,     //* 9 */
                         0,60,102,94,94,102,60,0,     //* Copyright */
                         0,0,24,24,0,24,24,0,         //* : */
                         0,0,24,24,0,24,48,0,         //* ; */
                         0,0,0,0,0,24,48,0,           //* , */
                         0,0,0,0,0,24,24,0,           //* . */
                         8,0,8,48,96,100,56,0,        //* ¨ */
                         28,38,6,12,16,0,16,0,        //* ? */
                         24,0,24,24,60,60,24,0,       //* ­ */
                         24,60,60,24,24,0,24,0,       //* ! */
                         0,48,96,96,96,96,48,0,       //* ( */
                         0,24,12,12,12,12,24,0,       //* ) */
                         0,60,102,102,126,126,102,0,  //* A */
                         0,124,116,126,114,114,126,0, //* B */
                         0,126,114,112,112,114,126,0, //* C */
                         0,124,114,114,114,114,124,0, //* D */
                         0,126,112,124,112,112,126,0, //* E */
                         0,126,112,124,112,112,112,0, //* F */
                         0,126,114,112,118,114,126,0, //* G */
                         0,114,114,126,114,114,114,0, //* H */
                         0,126,24,24,24,24,126,0,     //* I */
                         0,14,14,14,78,78,126,0,      //* J */
                         0,116,120,120,116,114,114,0, //* K */
                         0,112,112,112,112,112,126,0, //* L */
                         0,102,126,90,66,66,66,0,     //* M */
                         0,98,114,122,110,102,98,0,   //* N */
                         0,60,102,102,102,102,60,0,   //* O */
                         0,124,114,114,124,112,112,0, //* P */
                         0,56,100,100,100,100,58,0,   //* Q */
                         0,124,114,114,124,126,114,0, //* R */
                         0,62,112,56,28,30,124,0,     //* S */
                         0,124,24,24,24,24,24,0,      //* T */
                         0,114,114,114,114,126,60,0,  //* U */
                         0,114,114,114,118,60,24,0,   //* V */
                         0,66,90,90,90,126,102,0,     //* W */
                         0,102,36,24,24,36,102,0,     //* X */
                         0,98,98,60,24,24,24,0,       //* Y */
                         0,126,14,28,56,112,126,0,    //* Z */
                         0,0,0,0,0,0,0,0};            //*   */



int main()
{
 tpaleta paleta1;
 unsigned char *buffer = NULL;
 unsigned int vscreen;
 int actual = 0,i,j;
 FILE *fitxer = NULL;
 unsigned char cadena[12*26];
 



 if((buffer = (byte *)malloc((word)64000L)) == NULL)
 {
  printf("\neeeeeh, sorto pq no hi ha prou memoria...\n");
  exit(1);
 }




 buffer = MK_FP(FP_SEG(buffer),0);
 vscreen = FP_SEG(buffer);
 
 // Carrega de dades a la vscreen.

 if( (fitxer = fopen("Lletres.raw","wb+")) == NULL)
 {
  printf("\nError, al obrir arxiu \"lletres.raw\"!!! \n");
  return(1);
 }



 if( (ShowPcx("lletres.pcx",255,paleta1,vscreen)) !=0)
 {
  printf("\nError, al obrir arxiu \"lletres.pcx\"!!! \n");
  return(1);
 }

 // TRansfo...

 // Primer els numeros (0,1,2,3,4,5,6,7,8,9) total son 10!!!

   for(i=0;i<ALTURA;i++)
   {

      fwrite(buffer+i*320,10*AMPLADA,1,fitxer) ; // Numeros. // 260

      fwrite(buffer+i*320+320*19,11*AMPLADA,1,fitxer) ; // Simbols. // 286 

      fwrite(buffer+i*320+320*19*2,12*AMPLADA,1,fitxer) ; // Lletres 1. // 312 

      fwrite(buffer+i*320+320*19*3,12*AMPLADA,1,fitxer) ; // Lletres 2. // 312 

      fwrite(buffer+i*320+320*19*4,3*AMPLADA,1,fitxer) ; // Lletres 3. // 78 

   }

 fclose(fitxer);


 if( (fitxer = fopen("colors.pal","wb+")) == NULL)
 {
  printf("\nError, al obrir arxiu \"colors.pal\"!!! \n");
  return(1);
 }

 fwrite(paleta1,768,1,fitxer);

 close(fitxer);

 free(buffer);

}

