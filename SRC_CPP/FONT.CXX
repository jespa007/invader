#include "font.h"




char FntMonoText[8*MAX_LLETRES];
byte LletresMitjanes[MAX_LLETRES][AMPLADA_LLETRAM*ALTURA_LLETRAM];
byte LletresGrans[MAX_LLETRES][AMPLADA_LLETRAG*ALTURA_LLETRAG];



/*************- DEFINCIO DE TEXTURA-************************/


byte textura[MAX_TEXTURA*MAX_AMPLADA_TEXT*MAX_ALTURA_TEXT]=
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
 int k,i,j;
 FILE *fitxer1 = NULL;

 // Lletres...


 if( (fitxer1 = fopen("grafics//FONTMT.raw","rb")) == NULL ) return 0;
 
 fread(FntMonoText,MAX_LLETRES*8,1,fitxer1); // Llegim 8*48 bytes...

 fclose(fitxer1);

 return 1;

}





int CarregarFontMitjana()
{
 int k,i,j;
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



void PutChar(word x, word y,byte caracter,word alt_caracter, byte textura_escullida,unsigned short negreta,unsigned short invert,byte TIPUS_FONT,word segment)
{
 word offset_inici,by;

 byte getbyte;
 byte offset_textura;


 offset_textura = textura_escullida*64;
 offset_inici = caracter*8;

 switch(TIPUS_FONT)
 {
  case FONTMT:
         if(!invert)
         {
          for(by=0;by<alt_caracter;by++,offset_inici++)
          {
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&128)!=0)
           {
            PutPixel(x,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+1,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&64)!=0) 
           {
            PutPixel(x+1,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+2,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&32)!=0) 
           { 
            PutPixel(x+2,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+3,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&16)!=0) 
           { 
            PutPixel(x+3,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+4,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&8)!=0) 
           { 
            PutPixel(x+4,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+5,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&4)!=0) 
           { 
            PutPixel(x+5,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+6,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&2)!=0) 
           { 
            PutPixel(x+6,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&1)!=0) 
           {
            PutPixel(x+7,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+8,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
          }
         }
         else
         {
          for(by=0;by<alt_caracter;by++,offset_inici++)
          {
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&1)!=0) 
           {
            PutPixel(x,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&2)!=0) 
           { 
            PutPixel(x+1,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&4)!=0) 
           { 
            PutPixel(x+2,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&8)!=0) 
           { 
            PutPixel(x+3,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&16)!=0) 
           { 
            PutPixel(x+4,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&32)!=0) 
           {
            PutPixel(x+5,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&64)!=0) 
           {
            PutPixel(x+6,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
           getbyte = FntMonoText[offset_inici];
           if ((getbyte&128)!=0) 
           { 
            PutPixel(x+7,y+by,textura[offset_textura],segment);
            if(negreta) PutPixel(x+7,y+by+1,textura[offset_textura],segment);
           }
           offset_textura++;
        
          }
        
         }
         break;
  case MEDFNT: PutSprite(x,y,LletresMitjanes[caracter],AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,319,199,0,segment);
               break;

  }
}              



void PutCharX(int x, int y,char caracter,word alt_caracter, byte textura_acullida,unsigned short negreta,unsigned short invert,byte page)
{

 word offset_inici,by;

 byte getbyte;
 byte offset_textura;


 offset_textura = textura_acullida*64;
 offset_inici = caracter*8;

 getbyte = textura[offset_textura];

 if(!invert)
 {
  for(by=0;by<alt_caracter;by++,offset_inici++)
  {
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&128)!=0)
   {
    PutPixelX(x,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+1,y+by+1,textura[offset_textura],page);
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&64)!=0) 
   {
    PutPixelX(x+1,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+2,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&32)!=0) 
   { 
    PutPixelX(x+2,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+3,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&16)!=0) 
   { 
    PutPixelX(x+3,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+4,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&8)!=0) 
   { 
    PutPixelX(x+4,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+5,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&4)!=0) 
   { 
    PutPixelX(x+5,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+6,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&2)!=0) 
   { 
    PutPixelX(x+6,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&1)!=0) 
   {
    PutPixelX(x+7,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+8,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
  }
 }
 else
 {
  for(by=0;by<alt_caracter;by++,offset_inici++)
  {
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&1)!=0) 
   {
    PutPixelX(x,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&2)!=0) 
   { 
    PutPixelX(x+1,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&4)!=0) 
   { 
    PutPixelX(x+2,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&8)!=0) 
   { 
    PutPixelX(x+3,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&16)!=0) 
   { 
    PutPixelX(x+4,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&32)!=0) 
   {
    PutPixelX(x+5,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&64)!=0) 
   {
    PutPixelX(x+6,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;
   getbyte = FntMonoText[offset_inici];
   if ((getbyte&128)!=0) 
   { 
    PutPixelX(x+7,y+by,textura[offset_textura],page );
    if(negreta) PutPixelX(x+7,y+by+1,textura[offset_textura],page );
   }
   offset_textura++;

  }

 }

}




word centred(word x,word LONG)
{

 // Retorna la coordenada x per centra un text (especial en el OutText()).

 return ( x - (LONG*MAX_AMPLADA_TEXT/2) );

}



void OutText(word x,word y,byte *cadena,byte textura_escullida,unsigned short negreta,unsigned short invert,byte FONT,word segment)
{
 int i=0;

 while(cadena[i]!=MARCA_FI_STRING)
 {
  switch(FONT)
  {
   case FONTMT:PutChar(x+i*MAX_AMPLADA_TEXT,y,traduccio_caracter(toupper(cadena[i])),MAX_ALTURA_TEXT,textura_escullida,negreta,invert,FONTMT,segment);
               break;
   case MEDFNT:PutSprite(x,y,LletresMitjanes[traduccio_caracter(toupper(cadena[i]))],AMPLADA_LLETRAM,ALTURA_LLETRAM,0,0,320,200,0,segment);
               x += AMPLADA_LLETRAM;
               break;

   case BIGFNT:PutSprite(x,y,LletresGrans[traduccio_caracter(toupper(cadena[i]))],AMPLADA_LLETRAG,ALTURA_LLETRAG,0,0,320,200,0,segment);
               x += AMPLADA_LLETRAG;

  }
  i++;
 }
}

void OutTextX(word x,word y,byte *cadena,byte textura_escullida,unsigned short negreta,unsigned short invert,byte page)
{
 int i=0;

 while(cadena[i]!=MARCA_FI_STRING)
 {

  PutCharX(x+i*MAX_AMPLADA_TEXT,y,traduccio_caracter(toupper(cadena[i])),MAX_ALTURA_TEXT,textura_escullida,negreta,invert,page);
  i++;                                                                                  

 }
}



void Visualitzar_Numero(word x, word y,dword numero,word LONG,word TEXTURA,word segment)
{
 dword decimal=(dword)exponent(dword(10),LONG-1);
 word pos=0;

if(numero == 0)
{
  
 while(pos<=LONG-1) {PutChar(x,y,traduccio_caracter(' '),MAX_ALTURA_TEXT,1,0,0,FONTMT,segment);x+=MAX_AMPLADA_TEXT;pos++;}
 PutChar(x,y,traduccio_caracter('0'),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT,segment);

}
else
{
 while(((word)(numero/decimal)==0)&&pos<=LONG)
 {
   PutChar(x,y,traduccio_caracter(' '),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT,segment);
  pos++;
  numero%=decimal;
  decimal/=10;
  x+=MAX_AMPLADA_TEXT;
 }


 while(pos<=LONG)
 {
  PutChar(x,y,(word)(numero/decimal),MAX_ALTURA_TEXT,TEXTURA,0,0,FONTMT,segment);
  pos++;
  numero%=decimal;
  decimal/=10;
  x+=MAX_AMPLADA_TEXT;
 }
} 
}

  

void Visualitzar_NumeroX(word x, word y,word numero,word LONG,byte page)
{
 dword decimal=(dword)exponent((dword)10,LONG-1);
 word pos=0;


 while(pos<LONG)
 {
  PutCharX(x,y,(word)(numero/decimal),MAX_ALTURA_TEXT,1,0,0,page);
  pos++;
  numero=numero%decimal;
  decimal=decimal/10;
  x+=MAX_AMPLADA_TEXT;
 }
}
