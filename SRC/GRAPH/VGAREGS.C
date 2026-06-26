#include "SRC\GRAPH\@GRAPH.H"




void VgaRegs_RegisterOut(uint16_t _controller,uint8_t _register,uint8_t _value)
{

 switch(_controller){

  case ATTR_ADDR:

   asm{

    mov dx,STATUS_ADDR
    in al,dx
    mov dx,ATTR_ADDR
    mov al,_register
    out dx,al
    mov al,_value
    out dx,al

   }
   break;

  case SEQU_ADDR:

   if(_register == 1) {
    outport(SEQU_ADDR,0x0100);
    outport(SEQU_ADDR,_value << 8 | 0x01);
    outport(SEQU_ADDR,0x0300);
    break;
   }

  case GRAC_ADDR:
  case CRTC_ADDR:
  
   outport(_controller,(uint16_t)_register | ((uint16_t)(_value) << 8));
   break;

  case MISC_READ_ADDR:
  default:

   outportb(_controller,_value);
   break;
 }

 asm{
  mov dx,ATTR_ADDR
  mov al,0x20
  out dx,al
 }

}

uint8_t VgaRegs_RegisterIn(uint16_t _controller,uint8_t _register) {

 uint8_t value; // Valor a returnar.

 switch(_controller) {
  case MISC_WRITE_ADDR:
    value = inportb(0x3cc);
    break;

  case ATTR_ADDR:

   asm{

    mov dx,STATUS_ADDR
    in al,dx
    mov dx,ATTR_ADDR
    mov al,_register
    out dx,al
    mov al,value
    in al,dx

   }

   value = _AL;

   break;

  case SEQU_ADDR:
  case GRAC_ADDR:
  case CRTC_ADDR:

   asm{
    mov dx,_controller
    mov al,_register
    out dx,al
    inc dx
    in al,dx
   }

   value = _AL;

   break;

  case VGAENABLE_ADDR:
  default:

   asm{
    mov dx,_controller
    in al,dx
   }

   value = _AL;

   break;
   
 }

 asm{
  mov dx,ATTR_ADDR
  mov al,0x20
  out dx,al
 }

 return (value);

}



void VgaRegs_SetOffsetRegister(uint8_t _width)
{
 asm{
     mov dx,CRTC_ADDR
     mov al,0x13
     out dx,al
     inc dx
     mov al,[_width]
     out dx,al

    }
}



void VgaRegs_SetStartAddress(uint16_t _offset)
{
 // Aquesta funci� ens permet iniciar el punt (0,0) a la posici� que volguem.

 VgaRegs_RegisterOut(CRTC_ADDR,0x0C,_offset >> 8);// Enviem el valor alt de l' offset (els ports del PC s�n de 8 bits).
 VgaRegs_RegisterOut(CRTC_ADDR,0x0D,_offset & 0xFF);// Enviem el valor alt de l' offset.
}


void VgaRegs_MaskPlanes(uint8_t _mask)
{
 // Enmascara els plans solicitats per impedir la escriptura.

 VgaRegs_RegisterOut(SEQU_ADDR,0x02,_mask);


}


void VgaRegs_EnableAllPlanes(void){
 // Desmascara tots els plans.
 VgaRegs_MaskPlanes(0x0F);


}

