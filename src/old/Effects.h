#ifndef __EFECTES_H__
#define __EFECTES_H__

#include "definicions.h"

//  旼컴컴컴컴컴컴커
//  � ESTRELLES 2D �
//  읕컴컴컴컴컴컴켸

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


//  旼컴컴컴컴컴컴커
//  � ESTRELLES 3D �
//  읕컴컴컴컴컴컴켸


  #define maxstars 300
  #define dim 200

  void Setup(void);
  void Calc(void);
  void Moure_Estrelles(void);
  void Dibuixar_Estrelles(word VIRTUAL_SCREEN);
  void Estrelles3D(word VIRTUAL_SCREEN);

//  旼컴컴�
//  � FOC �
//  읕컴컴�


 void mk_ytab(void);
 void cll(unsigned char *Virtual_Screen_Buffer);
 void set_hot(byte *Virtual_Buffer);
 byte average(int X,int Y,byte *Virtual_Screen_Buffer);
 void mk_lines(byte *Virtual_Screen_Buffer);
 void Foc(byte *Virtual_Screen);
 void CrearPaletaFoc(char index_i,char vermell_i,char verd_i,char blau_i,char index_f,char vermell_f,char verd_f,char blau_f);

//  旼컴컴컴커
//  � PLASMA �
//  읕컴컴컴켸

void Plasma(word VScreen);

//  旼컴컴컴컴컴컴컴컴�
//  � TRANSFORMACIONS �
//  읕컴컴컴컴컴컴컴컴�

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
//  旼컴컴컴컴컴커               //
//  � CROSS FADE �                //
//  읕컴컴컴컴컴켸                 //
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