#include "all_lib.h"

 //  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 //  ³Mode Video 320x200 a 256 colors³
 //  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ



 void SetMode13(void);
 void ClearScreen(byte COLOR,word SEGMENT);
 void PutPixel(word X,word Y,byte COLOR,word SEGMENT);
 byte GetPixel(word X ,word Y ,word SEGMENT );
 void PColor(int x,int y,word SEGMENT);

 void GetBlock(word X,word Y,byte *BUFFER,word TAMANY_X ,word TAMANY_Y,byte far *BUFF);
 void PutBlock(int X,int Y,byte far * BLOC,word AMPLADA,word ALTURA,word MIN_AMPLADA,word MIN_ALTURA,word MAX_AMPLADA,word MAX_ALTURA,word SEGMENT);

 void PutSprite(int X,int Y,byte far * SPRITE,word AMPLADA,word ALTURA,word MIN_PANTALLA_X,word MIN_PANTALLA_Y,word MAX_PANTALLA_X,word MAX_PANTALLA_Y,char ColorMascara,word SEGMENT);


 void SetMode3(void);


 void recta_horitzontal(word X,word Y,word GRUIX,byte COLOR,word SEGMENT);
 void recta_vertical(word X,word Y,word ALT,byte COLOR,word SEGMENT);
 void rectangle_ple(word X,unsigned Y,word GRUIX,word ALT,byte COLOR,word SEGMENT);
 void rectangle(word X,word Y,word GRUIX,word ALT,byte COLOR);



