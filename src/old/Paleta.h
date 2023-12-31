#ifndef PALETA_H
 #define PALETA_H

#include "definicions.h"
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




/*
   浜様様様様様�
   �           �
   � CAP�ALERA �
   �           �
   藩様様様様様�

*/




//  敖陳陳陳陳陳陳陳朕
//  �Utilitats Paleta�
//  青陳陳陳陳陳陳陳潰

    void ModificarColorPaleta(tColor *paleta, unsigned char ,unsigned char  ,unsigned char  ,unsigned char );
//    void GetPalette(char far *,int ,int );
    int  CarregarPaleta(char *NOM_PALETA_DISC,tColor *PALETA_VARIABLE);

    void SetPalette(tColor *,int ,int );
    //void WaitVRetrace(void);
    //void RestauraPaleta(char *,char *,int ,int );
    
	void CopiaPaleta(tColor *,tColor *,int ,int );
    void PaletaNegre(tColor *,int ,int);
    void PaletaBlanca(tColor *,int ,int);
    void VisualitzarPaleta();

    void XchangeColor(tColor *PALETA,char COLOR1,char COLOR2);



//  敖陳陳陳陳陳陳朕
//  �Efectes Paleta�
//  青陳陳陳陳陳陳潰

    void FadeOut(tColor *,int ,int);
    void FadeIn(tColor  *,int ,int);
    void ImpactIn(int ,int );
    void ImpactOut(tColor *,int ,int );
	void RotatePaletteLeft(tColor *paleta,int color_i,int color_f);
    void RotatePaletteRight(tColor *,int ,int );
    void MorphPalette(tColor *,tColor *,int ,int );
    void XchangeColor(tColor *paleta,char color1,char color2);


//  敖陳陳陳陳陳陳陳朕
//  �Gestio de Colors�
//  青陳陳陳陳陳陳陳潰

    void Escala(unsigned char *,unsigned char);


#endif
