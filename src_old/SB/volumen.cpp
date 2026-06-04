/*  SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */
/*  VOLUMEN.C   Traducci¢n: Oswaldo Varela C.  */

#pragma option -w- // Desactiva warnings
void writemixer(unsigned char reg, unsigned char value){
	outp(mixeraddrport, reg);
	outp(mixerdataport, value);
}
void setmastervolume(unsigned char left, unsigned char right){
	writemixer(0x22, (left << 4) + right);
}
void setvoicevolume(unsigned char left, unsigned char right){
	writemixer(0x04, (left << 4) + right);
}
void setfmvolume(unsigned char left, unsigned char right){
	writemixer(0x26, (left << 4) + right);
}
void setcdvolume(unsigned char left, unsigned char right){
	writemixer(0x28, (left << 4) + right);
}
void setlinevolume(unsigned char left, unsigned char right){
	writemixer(0x2E, (left << 4) + right);
}
#pragma option -w  // Activa warnings nuevamente

