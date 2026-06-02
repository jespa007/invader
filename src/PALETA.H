#ifndef PALETA_H
 #define PALETA_H


#include "all_lib.h"


// COLORS

#define NEGRE 0
#define BLAU  1
#define VERD  2
#define CYAN  3
#define VERMELL 4 
#define MAGENTA 5
#define MARRO 6
#define GRIS 7
#define GRIS_FOSC 8
#define BLAU_CLAR 9
#define VERD_CLAR 10
#define CYAN_CLAR 11
#define VERMELL_CLAR 12
#define MAGENTA_CLAR 13
#define GROC 14
#define BLANC 15


// DEFINICIO DE TIPUS


typedef byte tpaleta[768];



/*
   ÉÍÍÍÍÍÍÍÍÍÍÍ»
   º           º
   º CAP€ALERA º
   º           º
   ÈÍÍÍÍÍÍÍÍÍÍÍ¼

*/


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Utilitats Paleta³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

    void ModificarColorPaleta(byte ,byte ,byte ,byte );
    void GetPalette(byte far *,word ,word );
    int  CarregarPaleta(byte *NOM_PALETA_DISC,byte *PALETA_VARIABLE);

    void SetPalette(byte far *,word ,word );
    void WaitVRetrace(void);
    void RestauraPaleta(byte *,byte *,word ,word );
    void CopiaPaleta(byte *,byte *,word ,word );
    void PaletaNegre(byte *,word ,word);
    void PaletaBlanca(byte *,word ,word);
    void VisualitzarPaleta();
    void VisualitzarPaletaX(byte );
    void XchangeColor(byte *PALETA,byte COLOR1,byte COLOR2);
    int ColorIgual(byte *paleta1,byte *paleta2,byte color1,byte color2);


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Efectes Paleta³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

    void FadeOut(word ,word);
    void FadeIn(byte  *,word ,word);
    void ImpactIn(word ,word );
    void ImpactOut(byte *,word ,word );
    void RotatePaletteLeft(byte far *,byte ,byte );
    void RotatePaletteRight(byte far *,word ,word );
    void MorphPalette(byte *,byte *,word ,word );
    void XchangeColor(byte *paleta,byte color1,byte color2);


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Gestio de Colors³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

    void Escala(unsigned char *,unsigned char);


#endif
