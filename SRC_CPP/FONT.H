#ifndef FONT_H
 #define FONT_H

#include "modex.h"
#include "all_lib.h"



#define MAX_LLETRES    48

// Fonts monotextura.

#define FONTMT      0
#define MAX_TEXTURA 6
#define MAX_AMPLADA_TEXT 8
#define MAX_ALTURA_TEXT  8

// Fonts Mitjanes.

#define MEDFNT          1
#define AMPLADA_LLETRAM 13
#define ALTURA_LLETRAM  15


// Lletres considerablament grosses amb mascara...

#define BIGFNT          2
#define AMPLADA_LLETRAG 26
#define ALTURA_LLETRAG  19




 // Inicialitzacions

 int CarregarFontMonoTextura();
 int CarregarFontMitjana();
 int CarregarFontGran();



 // B…siques

 int traduccio_caracter(char c);
 void PutChar(word X, word Y,byte CARACTER,word ALTURA, byte TEXTURA,unsigned short NEGRETA,unsigned short INVERT,byte TIPUS_FONT, word SEGMENT);
 void PutCharX(int x, int y,char caracter,word alt_caracter, byte textura_acullida,unsigned short negreta,unsigned short invert, byte page);

 word centred(word X,word LONGITUD_MISSATGE);

 // Acan‡ades

 void OutText(word X,word Y,byte *MESSAGE,byte TEXTURA,unsigned short NEGRETA,unsigned short INVERT,byte TIPUS_FONT,word SEGMENT);
 void OutTextX(word X,word Y,byte *MESSAGE,byte TEXTURA,unsigned short NEGRETA,unsigned short INVERT,byte page);

 void Visualitzar_Numero(word X, word Y, dword NUMERO,word LONG,word TEXTURA,word SEGMENT);
 void Visualitzar_NumeroX(word x, word y, word numero,word LONG,byte page);


#endif
