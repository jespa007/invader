#ifndef PCX_H
 #define PCX_H

#include "all_lib.h"

// Definicions del PCX

typedef struct capcalera{
                        byte idpcx; // Es un fitxer PCX v…lid ?
                        byte pcxversion; // Versio del PCX.
                        byte rle; // Comprimit amb RLE?
                        byte bitspixel; // bits per pixel.(Normalment s¢n 8 bits).
                        word d_x1;
                        word d_y1;
                        word d_x2;
                        word d_y2;
                        word d_reshor;
                        word d_resver;
                        byte paleta[48];
                        byte reservat;
                        byte n_plans;
                        word byteslinea;
		       }pcx;



word ShowPcx(byte *NOM_ARXIU,word INTENSITAT,byte *PALETA_SORTIDA,word SEGMENT);
word ShowPcxX(byte *NOM,word INTENSITAT,byte *PALETA_SORTIDA,byte PAGE);


#endif
