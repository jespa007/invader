#ifndef MODEX_H
 #define MODEX_H

#include "all_lib.h"


#define MODE1x4 0
#define MODE2x2 1
#define MODE4x1 2

#define DIM1x4 40
#define DIM2x2 80
#define DIM4x1 160

#define PLA1 0x01
#define PLA2 0x02
#define PLA3 0x04
#define PLA4 0x08

#define PAGINA0 0
#define PAGINA1 1
#define PAGINA2 2
#define PAGINA3 3





/*

                ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
                ³Mode Video 320x200 X a 256 colors³
                ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

 
 
        REPRESENTACIO DELS PLANS DESENCADENATS (UNCHAINED)
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
                                                  
           ÚÄÄÄÄÄÄÄÄÄ--ùùú      úùù-ÄÄÄÄÄÄÄÄÄÄ¿  /^\
           ³3,7,...                 ...315,319³   ³
        ÚÄÄÁÄÄÄÄÄ--ùùú      úùù-ÄÄÄÄÄÄÄÄ¿     ³   |
        ³2,6,...              ...314,318³     |   :
     ÚÄÄÁÄÄÄÄÄ--ùùú      úùù-ÄÄÄÄÄ¿     |     :  
     ³1,5,...           ...313,317³     :        
   ÚÄÁÄÄ--ùùú       úùù-ÄÄÄÄ¿     |            
   ³0,4,...       ...312,316³     :           
   ³                        |                     800 files
   ³                        :                  
   ³                                           
   ³                                              :
   ³                                          :   |
   ³                                    :     |   ³
   ³                              :     |     ³   ³
   ³                        :     |     ³     ³   ³
   ³                        |     ³     ³Pla 3³   ³
   ³                        ³     ³     ÃÄÄÄÄÄÙ  \_/ 
   ³                        ³     ³Pla 2³       
   ³                        ³     ÃÄÄÄÄÄÙ
   ³                        ³Pla 1³
   ³                        ÃÄÄÄÄÄÙ
   ³                   Pla 0³
   ÀÄÄÄ--ùùú       úùù-ÄÄÄÄÄÙ
   <ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ>
       320 bytes(pixels)
 
  Per tant tenim:
 
   4 (p…gines) x 80 bytes x 800 (files) = 256 Kbytes. (Tota la mem•ria.)

  Cada p…gina es de:

   80 bytes x 200 linees x 4 = 64000 Kbytes


  Nota: Per seleccionar els PLANS hem de procedir de la segent forma:

       0x01 = Pla n§ 0 ( 0001 )
       0x02 = Pla n§ 1 ( 0010 )
       0x04 = Pla n§ 2 ( 0100 )
       0x08 = Pla n§ 3 ( 1000 )

       Per seleccionar a m‚s d'un pl… seria:

       0x03 = Selecciona pla 0 i 1 a la vegada. ( 0011 )
       0x07 = Selecciona plans 0,1 i 2 . ( 0111)
        ù
        ù
        ù


 Gr…cies aquest mode podem obtenir resolucions tals com:

       200x800           640x400                800x200
       ( 1x4 )           ( 2x2 )                ( 4x1 )
        
       ÚÄÄÄÄÄ¿        ÚÄÄÄÄÄÂÄÄÄÄÄ¿     ÚÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄÂÄÄÄÄÄ¿
       ³Pla 0³        ³Pla 0³Pla 1³     ³Pla 0³Pla 1³Pla 2³Pla 3³
       ÃÄÄÄÄÄ´        ÃÄÄÄÄÄÅÄÄÄÄÄ´     ÀÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÁÄÄÄÄÄÙ
       ³Pla 1³        ³Pla 2³Pla 3³
       ÃÄÄÄÄÄ´        ÀÄÄÄÄÄÁÄÄÄÄÄÙ
       ³Pla 2³
       ÃÄÄÄÄÄ´
       ³Pla 3³
       ÀÄÄÄÄÄÙ                

*/


// Rutines B…siques

 void SetMode320_200X(); // Iniciem el Mode X 320x200.
 void SetMode320_240X(); // Iniciem el Mode X 320x240.

 void ClearScreenX(byte COLOR,char page); // (0x0F selecciona tots).
 void PutPixelX(word X,word Y,byte COLOR,byte page);
 byte GetPixelX(word X,word Y,byte page); 

 void Flip_VScreenX(byte PAGE,word segment);
 int CarregarImatgeX(word X,word Y,byte *nom,word AMPLADA,word ALTURA,byte PAGE);



// Rutines per canviar de p…gina...


void SetPageX(int page);


// Rutines per canviar de p…gina, amb el seu corresponent DESPLA€AMENT!



void SetDimX(byte DIM);



#endif






