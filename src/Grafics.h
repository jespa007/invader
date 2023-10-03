
#include "definicions.h"

#ifdef __SDL__
 
    extern SDL_Surface *Video;

	#define SDL_WORK_VRAM  ((char *)Video->pixels)

	#define	ptr_video SDL_WORK_VRAM

#endif



 //  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 //  ³Mode Video 320x200 a 256 colors³
 //  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ



 void SetVideo(void);

 void Flip_Video();
 void ClearScreen(char COLOR);
 
 void ClearRect(int X, int Y,int AMPLADA, int ALTURA,char color);
 
	 void PutPixel(int X,int Y,char COLOR);
 byte GetPixel(int X ,int Y);
 void PColor(int x,int y);

 void GetBlock(word X,word Y,char *BUFFER,word TAMANY_X ,word TAMANY_Y,char *BUFF);
 void PutBlock(int X,int Y,char * BLOC,int AMPLADA,int ALTURA,int MIN_AMPLADA,int MIN_ALTURA,int MAX_AMPLADA,int MAX_ALTURA);
 void PutSprite(int X,int Y,char * SPRITE,int AMPLADA,int ALTURA,int MIN_PANTALLA_X,int MIN_PANTALLA_Y,int MAX_PANTALLA_X,int MAX_PANTALLA_Y, byte Color_Mascara);


// void SetMode3(void);


 void recta_horitzontal(int X,int Y,int GRUIX,char COLOR);
 void recta_vertical(int X,int Y,int ALT,char COLOR);
 void rectangle_ple(unsigned int x,unsigned int y,unsigned int gruix,unsigned int alt,char color);
// void rectangle(word X,word Y,word GRUIX,word ALT,byte COLOR);



