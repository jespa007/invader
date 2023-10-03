#include "font.h"
#include "math.h"
#include <ctype.h>





char FntMonoText[8*MAX_LLETRES];
char LletresMitjanes[MAX_LLETRES][AMPLADA_LLETRAM*ALTURA_LLETRAM];
char LletresGrans[MAX_LLETRES][AMPLADA_LLETRAG*ALTURA_LLETRAG];



/*************- DEFINCIO DE TEXTURA-************************/


unsigned char textura[MAX_TEXTURA*MAX_AMPLADA_TEXT*MAX_ALTURA_TEXT]=
{
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5
 15,15,15,15,15,15,15,15, // Textura 5

 0,0,0,0,0,0,0,0, // Textura 2
 0,255,15,15,15,15,15,0,
 0,15,15,15,15,15,15,0,
 0,15,15,15,15,15,15,0,
 0,15,15,15,15,15,15,0,
 0,15,15,15,15,15,15,0,
 0,15,15,15,15,15,15,0,
 0,0,0,0,0,0,0,0,

 15,15,30,28,26,26,53,53,
 15,30,28,26,26,53,53,50,
 30,28,26,26,53,53,50,50,
 28,26,26,53,53,50,50,13,
 26,26,53,53,50,50,13,13,
 26,53,53,50,50,13,13,8,
 53,53,50,50,13,13,8,8,
 53,50,50,13,13,8,8,8,


 15,15,27,27,27,27,27,55, // Textura 4
 15,15,27,27,27,27,55,55, 
 27,27,27,27,27,55,55,55,
 27,27,27,27,55,55,55,83,
 27,27,27,55,55,55,83,83,
 27,27,55,55,55,83,83,83,
 27,55,55,55,83,83,83,111,
 55,55,55,83,83,83,111,111

};


int CarregarFontMonoTextura()
{

 FILE *fitxer1 = NULL;

 // Lletres...


 if( (fitxer1 = fopen("grafics//Fontmt.raw","rb")) == NULL ) return 0;
 
 fread(FntMonoText,MAX_LLETRES*8,1,fitxer1); // Llegim 8*48 chars...

 fclose(fitxer1);

 return 1;

}





int CarregarFontMitjana()
{
 int k,i;
 FILE *fitxer1 = NULL;

 // Lletres...


 if( (fitxer1 = fopen("grafics//MEDFNT.raw","rb")) == NULL ) return 0;
 
 for(i=0; i< ALTURA_LLETRAM ;i++)
 {
  for(k=0;k < MAX_LLETRES;k++)
  {
   fread(LletresMitjanes[k]+i*AMPLADA_LLETRAM,AMPLADA_LLETRAM,1,fitxer1);
  }
 }

 

 fclose(fitxer1);

 return 1;

}





int CarregarFontGran()
{
 int k,i;
 FILE *fitxer1 = NULL;

 // Lletres...


 if( (fitxer1 = fopen("grafics//BIGFNT.raw","rb")) == NULL ) return 0;
 
 for(i=0; i< ALTURA_LLETRAG ;i++)
 {
  for(k=0;k < MAX_LLETRES;k++)
  {
   fread(LletresGrans[k]+i*AMPLADA_LLETRAG,AMPLADA_LLETRAG,1,fitxer1);
  }
 }

 fclose(fitxer1);

 return 1;

}


















int traduccio_caracter(char c)
{

 switch(c)
 {
  case '0':return 0;
  case '1':return 1;
  case '2':return 2;
  case '3':return 3;
  case '4':return 4;
  case '5':return 5;
  case '6':return 6;
  case '7':return 7;
  case '8':return 8;
  case '9':return 9;
  case '.':return 10;
  case ',':return 11;
  case ':':return 12;
  case ';':return 13;
  case '!':return 14;
  case 'ญ':return 15;
  case '?':return 16;
  case 'จ':return 17;
  case '(':return 18;
  case ')':return 19;
  case '-':return 20;
  case 'A':return 21;
  case 'B':return 22;
  case 'C':return 23;
  case 'D':return 24;
  case 'E':return 25;
  case 'F':return 26;
  case 'G':return 27;
  case 'H':return 28;
  case 'I':return 29;
  case 'J':return 30;
  case 'K':return 31;
  case 'L':return 32;
  case 'M':return 33;
  case 'N':return 34;
  case 'O':return 35;
  case 'P':return 36;
  case 'Q':return 37;
  case 'R':return 38;
  case 'S':return 39;
  case 'T':return 40;
  case 'U':return 41;
  case 'V':return 42;
  case 'W':return 43;
  case 'X':return 44;
  case 'Y':return 45;
  case 'Z':return 46;
  default:return 47;
 }

}


/*
   ษออออออออออออออออออออออออออออออออป
   บ                                บ
   บ      IMPRESIO DE FONTS         บ
   บ                                บ
   ศออออออออออออออออออออออออออออออออผ
									*/


/* Escriu un caracter MonoTexturat per pantalla  (OPTIMITZAT) */



void PutChar(int x, int y,char caracter,int alt_caracter, char textura_escullida,unsigned short negreta,unsigned short invert,char TIPUS_FONT)
{
 int offset_inici,by;

 char getchar;
 char offset_textura;


 offset_textura = textura_escullida*64;
 offset_inici = caracter*8;

 switch(TIPUS_FONT)
 {
  case FONTMT:
         if(!invert)
         {
          for(by=0;by<alt_caracter;by++,offset_inici++)
          {
           getchar = FntMonoText[offset_inici];
           if ((getchar&128)!=0)
           {
            PutPixel(x,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+1,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&64)!=0) 
           {
            PutPixel(x+1,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+2,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&32)!=0) 
           { 
            PutPixel(x+2,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+3,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&16)!=0) 
           { 
            PutPixel(x+3,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+4,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&8)!=0) 
           { 
            PutPixel(x+4,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+5,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&4)!=0) 
           { 
            PutPixel(x+5,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+6,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&2)!=0) 
           { 
            PutPixel(x+6,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&1)!=0) 
           {
            PutPixel(x+7,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+8,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
          }
         }
         else
         {
          for(by=0;by<alt_caracter;by++,offset_inici++)
          {
           getchar = FntMonoText[offset_inici];
           if ((getchar&1)!=0) 
           {
            PutPixel(x,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&2)!=0) 
           { 
            PutPixel(x+1,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&4)!=0) 
           { 
            PutPixel(x+2,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&8)!=0) 
           { 
            PutPixel(x+3,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&16)!=0) 
           { 
            PutPixel(x+4,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&32)!=0) 
           {
            PutPixel(x+5,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&64)!=0) 
           {
            PutPixel(x+6,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
           getchar = FntMonoText[offset_inici];
           if ((getchar&128)!=0) 
           { 
            PutPixel(x+7,y+by,textura[offset_textura]);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura]);
           }
           offset_textura++;
        
          }
        
         }
         break;
  case MEDFNT: PutSprite(x,y,LletresMitjanes[caracter],AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,319,199,0);
               break;

  }
}              







int centred(int x,int longitud)
{

 // Retorna la coordenada x per centra un text (especial en el OutText()).

 return ( x - (longitud*MAX_AMPLADA_TEXT/2) );

}



void OutText(int x,int y,char *cadena,char textura_escullida,unsigned short negreta,unsigned short invert,char FONT)
{
 int i=0;

 while(cadena[i]!=MARCA_FI_STRING)
 {
  switch(FONT)
  {
   case FONTMT:PutChar(x+i*MAX_AMPLADA_TEXT,y,traduccio_caracter(toupper(cadena[i])),MAX_ALTURA_TEXT,textura_escullida,negreta,invert,FONTMT);
               break;
   case MEDFNT:PutSprite(x,y,LletresMitjanes[traduccio_caracter(toupper(cadena[i]))],AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,320,200,0);
               x += AMPLADA_LLETRAM;
               break;

   case BIGFNT:PutSprite(x,y,LletresGrans[traduccio_caracter(toupper(cadena[i]))],AMPLADA_LLETRAG,ALTURA_LLETRAG,0,0,320,200,0);
               x += AMPLADA_LLETRAG;

  }
  i++;
 }
}




void Visualitzar_Numero(int x, int y,int numero,int longitud,int TEXTURA)
{
 int decimal=(int)pow(10.0,longitud-1);
 int pos=0;

if(numero == 0)
{
  
 while(pos<(longitud-1)) {PutChar(x,y,traduccio_caracter(' '),MAX_ALTURA_TEXT,1,0,0,FONTMT);x+=MAX_AMPLADA_TEXT;pos++;}
 PutChar(x,y,traduccio_caracter('0'),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT);

}
else
{
 while(((int)(numero/decimal)==0)&&pos<longitud)
 {
   PutChar(x,y,traduccio_caracter(' '),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT);
  pos++;
  numero%=decimal;
  decimal/=10;
  x+=MAX_AMPLADA_TEXT;
 }


 while(pos<longitud)
 {
  PutChar(x,y,(int)(numero/decimal),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT);
  pos++;
  numero%=decimal;
  decimal/=10;
  x+=MAX_AMPLADA_TEXT;
 }
} 
}

  

