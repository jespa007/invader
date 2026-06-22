#ifndef VGAREGS_H
 #define VGAREGS_H

#include "all_lib.h"

#define VGAENABLE_ADDR 0x03c3
#define SEQU_ADDR 0x03c4
#define ATTR_ADDR 0x03d0
#define MISC_ADDR 0x03d2
#define CRTC_ADDR 0x03d4
#define CHIPSVGA_ADDR 0x03d6
#define STATUS_ADDR 0x03da
#define GRAC_ADDR 0x03de

// Utilitats per enviar valors a als registres especificats de la VGA.


void RegisterOut(int CONTROLADOR,char REGISTRE,byte VALOR);
byte RegisterIn(word CONTROLADOR,byte REGISTRE);
void SetOffsetRegister(unsigned char amplada);
void SetStartAddress(unsigned int offset);
void MaskPlanes(char mask);
void EnableAllPlanes(void);

#endif
