#include "SRC\GRAPH\@GRAPH.H"

void Mode13_Init(){
    
    asm{
         mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,13h  // AL Mode 320 x 200 a 256 colors. 
        int 10h
    }
}


void Mode13_DeInit(){
    
     asm{
        mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,3h  // AL (00,02,03,07 = TEXTE). 
        int 10h
    }
}