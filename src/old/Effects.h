#ifndef __EFECTES_H__
#define __EFECTES_H__

#include "definicions.h"

//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³ ESTRELLES 2D ³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

 #define NBR_STARS       200
 #define MinX            0
 #define MaxX            320
 #define MinY            0
 #define MaxY            200


 void InitStars(void);
 void DeleteStars(word VIRTUAL_SCREEN);
 void DeleteStarsX(byte PAGE);
 void MoveStars(void);
 void DrawStars();
 void DrawStarsX(byte PAGE);
 void Estrelles2D(word VIRTUAL_SCREEN);
 void Estrelles2DX(byte PAGE);


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³ ESTRELLES 3D ³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ


  #define maxstars 300
  #define dim 200

  void Setup(void);
  void Calc(void);
  void Moure_Estrelles(void);
  void Dibuixar_Estrelles(word VIRTUAL_SCREEN);
  void Estrelles3D(word VIRTUAL_SCREEN);

//  ÚÄÄÄÄÄ¿
//  ³ FOC ³
//  ÀÄÄÄÄÄÙ


 void mk_ytab(void);
 void cll(unsigned char *Virtual_Screen_Buffer);
 void set_hot(byte *Virtual_Buffer);
 byte average(int X,int Y,byte *Virtual_Screen_Buffer);
 void mk_lines(byte *Virtual_Screen_Buffer);
 void Foc(byte *Virtual_Screen);
 void CrearPaletaFoc(char index_i,char vermell_i,char verd_i,char blau_i,char index_f,char vermell_f,char verd_f,char blau_f);

//  ÚÄÄÄÄÄÄÄÄ¿
//  ³ PLASMA ³
//  ÀÄÄÄÄÄÄÄÄÙ

void Plasma(word VScreen);

//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³ TRANSFORMACIONS ³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

// Llista de possibles transformacions.

#define CapgirarY   0
#define CapgirarX   1
#define CapgirarXY  2
#define Augmentar   3
#define Lents       4


void TransformarBLOCK(byte *DEST, byte *ORG, word *TFM, word TAMANY_BLOCK_QUADRAT,byte TIPUS);

/* -On tipus: 0 inverteix les X (effecte de mirall)
 *            1 inverteix les Y (effecte de reflecte (ex:mar)) 
 *            2 inverteix les XY.
 *            3 augmenta el tamany x2.
 */





   //////////////////////////////
 //                             //
//  ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿               //
//  ³ CROSS FADE ³                //
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ                 //
//                                  //
// Notes de utilitzacio:             //
//                                    ///////////
// * Reservar 2 VScreens:              //       //
//                                      //       //
//   - 1 per la SCREEN1                 //        //
//   - 1 per la SCREEN2                 //         //
//   - 1 per la SCREEN_RESULT           //          //
//                                     //            //
//                                    ///////////////////      
//                                                    ////    
// * Enviar les dos paletes de cada respectiva paleta. ////
//                                                      / / 
//                                                      ///
 //                                                     //
  //////////////////////////////////////////////////////
   //     //                         //    //
    //   //                           //  //
     ////                              ////
/////////////////////////////////////////////////////////////////////////


#define MAX_COMB 256 // que es el que te una imatge.


int ExisteixCombinacio(byte *p1,byte *p2,byte color1,byte color2,byte *origen,byte *desti,int max_tamany,byte *posicio);
void IntroduirCombinacio(int posicio,byte *origen,byte *desti,byte R1,byte R2,byte G1,byte G2,byte B1,byte B2);
int InitFade(byte *S2, byte *S1, byte *S3,byte *p2, byte *p1, byte *desti,byte *origen);
void  CrossFade(byte *desti,byte *origen);

#endif