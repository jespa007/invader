#ifndef FONT_H
 #define FONT_H


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



 // B�siques

 int traduccio_caracter(char c);
 void PutChar(int X, int Y,char CARACTER,int ALTURA, char TEXTURA,unsigned short NEGRETA,unsigned short INVERT,char TIPUS_FONT);
// void PutCharX(int x, int y,char caracter,int alt_caracter, char textura_acullida,unsigned short negreta,unsigned short invert, char page);

 int centred(int X,int LONGITUD_MISSATGE);

 // Acan�ades

 void OutText(int X,int Y,char *MESSAGE,char TEXTURA,unsigned short NEGRETA,unsigned short INVERT,char TIPUS_FONT);

 void Visualitzar_Numero(int X, int Y, int NUMERO,int longitud,int TEXTURA);



#endif
