#ifndef __VGAREGS_H__
#define __VGAREGS_H__




#define ATTR_ADDR           0x03c0
#define ATTR_DATA_READ_ADDR 0x03c1
#define MISC_WRITE_ADDR     0x03c2
#define VGAENABLE_ADDR      0x03c3
#define SEQU_ADDR           0x03c4
#define MISC_READ_ADDR      0x03cc
#define GRAC_ADDR           0x03ce
#define CRTC_ADDR           0x03d4
#define CHIPSVGA_ADDR       0x03d6
#define STATUS_ADDR         0x03da



// Utilitats per enviar valors a als registres especificats de la VGA.


void    VgaRegs_RegisterOut(uint16_t _controller,uint8_t _register,uint8_t _value);
uint8_t VgaRegs_RegisterIn(uint16_t _controller,uint8_t _register);
void    VgaRegs_SetOffsetRegister(uint8_t _width);
void    VgaRegs_SetStartAddress(uint16_t _offset);
void    VgaRegs_MaskPlanes(uint8_t _mask);
void    VgaRegs_EnableAllPlanes(void);

#endif
