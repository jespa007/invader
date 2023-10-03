#include "grafics.h"

/*
   ษออออออออออออออออออออออออออออออออออออออออออออป
   บ                                            บ
   บ INICIALITZACIONS MODE VIDEO <-> TEXT       บ
   บ                                            บ
   ศออออออออออออออออออออออออออออออออออออออออออออผ
                                                  */

#ifdef __SDL__

SDL_Surface *Video;
#endif


void SetVideo(void) // Mode Video.
{
#ifdef __SDL__
  
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

	atexit(SDL_Quit);


	Video = SDL_SetVideoMode(AMPLADA_PANTALLA, ALTURA_PANTALLA, 8, 0/* 0SDL_SWSURFACE |SDL_HWPALETTE | SDL_FULLSCREEN*/ );
    if ( Video == NULL ) {
        fprintf(stderr, "No ้s port inicialitzar el mode %ix%i: %s\n",
                        AMPLADA_PANTALLA,ALTURA_PANTALLA,SDL_GetError());
        exit(1);
    }
#endif

}


void Flip_Video()
{
#ifdef __SDL__
	SDL_Flip(Video);
#endif
}


/*
   ษออออออออออออออออออออออออออออออออออออออออออออป
   บ                                            บ
   บ UTILITATS GRAFICS A 320 x 200 a 256 colors บ
   บ                                            บ
   ศออออออออออออออออออออออออออออออออออออออออออออผ
                                                  */

void ClearRect(int X, int Y,int AMPLADA, int ALTURA,char color)
// - Funcio que neteja una porci๓ de pantalla en una regi๓ de tipus rectangle.
{
#ifdef __SDL__
		SDL_Rect Regio;

		Regio.x = X;
		Regio.y = Y;

		Regio.w = AMPLADA;
		Regio.h = ALTURA;

		SDL_FillRect(Video,&Regio,color);
#endif
}


void ClearScreen(char color)
// - Funcio que neteja la pantalla.
{
#ifdef __SDL__
		SDL_FillRect(Video,NULL,color);
#endif
}
/*
	_asm{


			mov     edx, y2d
			mov     edi, dest_ptr
			mov     esi, ptr_textura
			mov		ecx, log2_amplada
			mov     ebx, v
	cont:
			mov     eax, ebx
			and     eax, Mascara_Altura_Textura
			shr     eax, PART_FRACCIONAL
			shl		eax, cl
			mov     al,  [esi+eax]
			mov     [edi],  al
                
			add     edi, AMPLADA_PANTALLA
			add		ebx, Escale_v;
			dec     edx
        
			jne     cont

        }
*/


void PutPixel(int x, int y, char color)

// - Funcio que posa un punt a la pantalla. (b…sic).

{
	char *video_ptr;

#ifdef _WINDOWS

 video_ptr = SDL_WORK_VRAM;
 _asm{

	 push edi

     mov edi,video_ptr // A on volem colocar el pixel.
	 mov eax,y
	 mov ebx,y
	 mov ecx,x
	 shl eax,8
	 shl ebx,6
	 add eax,ebx
	 add eax,ecx
	 mov bl,color
	 
	    
     mov [edi+eax],bl

	 pop edi
    }
#endif
}



byte GetPixel(int x,int y)
{
 byte valor; 
 char *video_ptr;
 unsigned desplacament=(y<<8)+(y<<6)+x;

#ifdef _WINDOWS

 video_ptr = SDL_WORK_VRAM;
 _asm{
     mov edi,video_ptr
     mov eax,desplacament
     mov al,[edi+eax]
	 mov valor,al 
    }
#endif

    return valor;
}

/*
void PColor(int x,int y,int segment)
{

  rectangle_ple(0,0,72,24,NEGRE,VIDEO);
  OutText(0,0,"Color:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(48,0,dint(GetPixel(x,y,segment)),3,0,VIDEO);
  OutText(0,8,"X:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(16,8,dint(x),3,0,VIDEO);
  OutText(0,16,"Y:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(16,16,dint(y),3,0,VIDEO);

}


*/

void GetBlock(unsigned int X,unsigned int Y,char *desti,unsigned int gruix,unsigned int alt,char *BUFF)
{
 // Carrega un tros de block a un punter buffer declarat.

 unsigned int i,j;


 for(i=Y;i<=Y+alt-1;i++)
 {
  memcpy(desti+(i-Y)*(gruix),BUFF+320*i+X,gruix);
 }

}


void PutBlock(int X,int Y,char * BLOC,int AMPLADA,int ALTURA,int MIN_AMPLADA,int MIN_ALTURA,int MAX_AMPLADA,int MAX_ALTURA)
{

char *video_ptr;

#ifdef _WINDOWS

 video_ptr = SDL_WORK_VRAM;

 _asm{

  mov eax,Y
  mov ebx,ALTURA
  add eax,ebx
  cmp eax,MIN_ALTURA
  jge si1
  jmp NoPutSprite



si1:



  mov eax,X
  mov ebx,AMPLADA
  add eax,ebx
  cmp eax,MIN_AMPLADA
  jge si2
  jmp NoPutSprite
 


si2:


  push edi
  push esi

  mov edi,video_ptr  // Punter video...
  mov esi,BLOC     // Punter textura...
  mov eax,Y
  mov ebx,Y
  shl eax,8
  shl ebx,6
  add eax,ebx
  add eax,X

  mov edx,eax

  
  
  xor ebx,ebx

NovaLinea: 

  xor ecx,ecx

NouPixel:

  mov eax,Y
  add eax,ebx
  cmp eax,MIN_ALTURA
  jge cond1
  jmp NoPutPixel

cond1:

  mov eax,Y
  add eax,ebx
  cmp eax,MAX_ALTURA
  jle cond2
  jmp NoPutPixel

cond2:

  mov eax,X
  add eax,ecx
  cmp eax,MIN_AMPLADA
  jge cond3
  jmp NoPutPixel

cond3:

  mov eax,X
  add eax,ecx
  cmp eax,MAX_AMPLADA
  jg  NoPutPixel

// Posem pixel

  mov al,[esi]
  mov [edi+edx],al       // Posem el Pixel!!!

NoPutPixel:

  inc esi
  inc edx
  inc ecx
  cmp ecx,AMPLADA
  jne NouPixel
  add edx,320
  sub edx,AMPLADA
  inc ebx
  cmp ebx,ALTURA
  jne NovaLinea

  pop esi
  pop edi

  
NoPutSprite: 
  


  }
#endif


}



void PutSprite(int X,int Y,char * BLOC,int AMPLADA,int ALTURA,int MIN_AMPLADA,int MIN_ALTURA,int MAX_AMPLADA,int MAX_ALTURA, unsigned char Color_Mascara)
{

char *video_ptr;

#ifdef _WINDOWS

 video_ptr = SDL_WORK_VRAM;

 _asm{

  mov eax,Y
  mov ebx,ALTURA
  add eax,ebx
  cmp eax,MIN_ALTURA
  jge si1
  jmp NoPutSprite



si1:



  mov eax,X
  mov ebx,AMPLADA
  add eax,ebx
  cmp eax,MIN_AMPLADA
  jge si2
  jmp NoPutSprite
 


si2:


  push edi
  push esi

  mov edi,video_ptr  // Punter video...
  mov esi,BLOC     // Punter textura...
  mov eax,Y
  mov ebx,Y
  shl eax,8
  shl ebx,6
  add eax,ebx
  add eax,X

  mov edx,eax

  
  
  xor ebx,ebx

NovaLinea: 

  xor ecx,ecx

NouPixel:

  mov eax,Y
  add eax,ebx
  cmp eax,MIN_ALTURA
  jge cond1
  jmp NoPutPixel

cond1:

  mov eax,Y
  add eax,ebx
  cmp eax,MAX_ALTURA
  jle cond2
  jmp NoPutPixel

cond2:

  mov eax,X
  add eax,ecx
  cmp eax,MIN_AMPLADA
  jge cond3
  jmp NoPutPixel

cond3:

  mov eax,X
  add eax,ecx
  cmp eax,MAX_AMPLADA
  jle cond4
  jmp NoPutPixel


cond4:

  mov al,[esi]
  cmp al,Color_Mascara
  je  NoPutPixel

  // Posem pixel
  mov [edi+edx],al       // Posem el Pixel!!!

 
NoPutPixel:

  inc esi
  inc edx
  inc ecx
  cmp ecx,AMPLADA
  jne NouPixel
  add edx,320
  sub edx,AMPLADA
  inc ebx
  cmp ebx,ALTURA
  jne NovaLinea

  pop esi
  pop edi

  
NoPutSprite: 
  


  }
#endif


}







//   ษออออออออออออออออออออออออออออออออป
//   บ                                บ
//   บ          GEOMETRIA             บ
//   บ                                บ
//   ศออออออออออออออออออออออออออออออออผ
                                                                         


/*
void recta_horitzontal(unsigned int x,unsigned int y,unsigned int gruix,char color,unsigned int segment)
{

 int desp=(y<<8)+(y<<6)+x;

 asm{
     mov es,[segment]
     mov di,[desp]
     mov cx,[gruix]
     mov al,[color]
     mov es:[di],al
     rep stosb
    }
}
*/

void recta_vertical(unsigned int x,unsigned int y,unsigned int alt,char color)
{
    int desp=(y<<8)+(y<<6)+x;
	char *video_ptr;

#ifdef _WINDOWS

 video_ptr = SDL_WORK_VRAM + desp;

 _asm{
     mov edi,video_ptr
     mov ecx,alt
     mov al,color
   
    
 bucleRECTA:

     mov [edi],al
     add edi,AMPLADA_PANTALLA
     dec ecx
     jnz bucleRECTA
    }
#endif

}


void rectangle_ple(unsigned int x,unsigned int y,unsigned int gruix,unsigned int alt,char color)
{

 unsigned i;
 for(i=0;i<gruix;i++) recta_vertical(x+i,y,alt,color);

}

/*
void rectangle(unsigned int x,unsigned int y,unsigned int gruix,unsigned int alt,char color)
{
 recta_horitzontal(x,y,gruix,color,VIDEO);
 recta_horitzontal(x,y+alt,gruix,color,VIDEO);
 recta_vertical(x,y,alt+1,color,VIDEO);
 recta_vertical(x+gruix,y,alt+1,color,VIDEO);
}



*/


