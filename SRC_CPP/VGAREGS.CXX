#include "VgaRegs.h"




void RegisterOut(int CONTROLADOR,char INDEX,byte VALOR)
{

 switch(CONTROLADOR)
 {

  case ATTR_ADDR:

   asm{

    mov dx,STATUS_ADDR
    in al,dx
    mov dx,ATTR_ADDR
    mov al,INDEX
    out dx,al
    mov al,VALOR
    out dx,al

   }
   break;

  case SEQU_ADDR:

   if(INDEX == 1)
   {
    outportw(SEQU_ADDR,0x0100);
    outportw(SEQU_ADDR,VALOR << 8 | 0x01);
    outportw(SEQU_ADDR,0x0300);
    break;
   }

  case GRAC_ADDR:
  case CRTC_ADDR:
  
   outportw(CONTROLADOR,INDEX | VALOR << 8);
   break;

  case MISC_ADDR:
  default:

   outportb(CONTROLADOR,VALOR);
   break;
 }

 asm{
  mov dx,ATTR_ADDR
  mov al,0x20
  out dx,al
 }

}



byte RegisterIn(word CONTROLADOR,byte INDEX)
{

 byte VALOR; // Valor a returnar.

 switch(CONTROLADOR)
 {
  case MISC_ADDR:

    VALOR = inportb(0x3cc);
    break;

  case ATTR_ADDR:

   asm{

    mov dx,STATUS_ADDR
    in al,dx
    mov dx,ATTR_ADDR
    mov al,INDEX
    out dx,al
    mov al,VALOR
    in al,dx

   }

   VALOR = _AL;

   break;

  case SEQU_ADDR:
  case GRAC_ADDR:
  case CRTC_ADDR:

   asm{
    mov dx,CONTROLADOR
    mov al,INDEX
    out dx,al
    inc dx
    in al,dx
   }

   VALOR = _AL;

   break;

  case VGAENABLE_ADDR:
  default:

   asm{
    mov dx,CONTROLADOR
    in al,dx
   }

   VALOR = _AL;

   break;
   
 }

 asm{
  mov dx,ATTR_ADDR
  mov al,0x20
  out dx,al
 }

 return (VALOR);

}



void SetOffsetRegister(unsigned char amplada)
{
 asm{
     mov dx,CRTC_ADDR
     mov al,0x13
     out dx,al
     inc dx
     mov al,[amplada]
     out dx,al

    }
}



void SetStartAddress(unsigned int offset)
{
 // Aquesta funci¢ ens permet iniciar el punt (0,0) a la posici¢ que volguem.

 RegisterOut(CRTC_ADDR,0x0C,offset>>8);// Enviem el valor alt de l' offset (els ports del PC s¢n de 8 bits).
 RegisterOut(CRTC_ADDR,0x0D,offset&0xFF);// Enviem el valor alt de l' offset.
}


void MaskPlanes(char mask)
{
 // Enmascara els plans solicitats per impedir la escriptura.

 RegisterOut(SEQU_ADDR,0x02,mask);


}


void EnableAllPlanes(void)
{
 // Desmascara tots els plans.

 MaskPlanes(0x0F);


}

