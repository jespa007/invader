#include "GRAPH\@GRAPH.H"

void SetPalette(uint8_t far * _palette,uint8_t _start,uint8_t _end){

 uint16_t end = (_end<<1)+(_end<<0); // final*=3;
 uint16_t start = (_start<<1)+(_start<<0); // inici*=3;
 end=(end-start)+3;
 asm{
     lds si,_palette //???//
     add si,[start]
     mov dx,3c8h // Direccio del registre d' escritura de la paleta DAC (Digital Analog Converter) //
     xor al,al // mov al,0 //
     out dx,al // Enviem el valor llegit al la paleta //
     inc dx // Ara dx es 3c9 podem escriure o llegir //
     mov cx,[end] // 256x3 posicions que hem de fer referencia. //
     rep outsb // Escriu en el port DX i incrementa SI+1//
    }
}
