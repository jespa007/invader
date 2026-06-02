#include "paleta.h"

/*
   ษอออออออออออออออออออออป
   บ                     บ
   บ  UTILITATS PALETA   บ
   บ                     บ
   ศอออออออออออออออออออออผ

*/


/***********- Modificar un color -**********************/


void ModificarColorPaleta(byte R,byte G,byte B,byte numcolor)
{
asm{
	mov dx,0x3C8
	mov al,[numcolor]   // Mou contingut color al registre baix de AX (AH+AL=AX (:)
	out dx,al
	inc dx
	mov al,[R]
	out dx,al
	mov al,[G]
	out dx,al
	mov al,[B]
	out dx,al
   }
}



/***** DAC => PALETA *****/


void GetPalette(byte far *paleta,word inici,word final)
{
 final=(final<<1)+(final<<0); // final*=3;
 inici=(inici<<1)+(inici<<0); // inici*=3;
 final=(final-inici)+3;
 asm{
     les di,paleta // llegeix   //
     add di,[inici]
     mov dx,3c7h // Registre de Lectura PEL//
     xor al,al // mov al,0 //
     out dx,al // Volem comenar a llegir el valor 0 del DAC //
     inc dx
     inc dx     // dx = 3c9h escriu en VIDEO //
     mov cx,[final] // 256x3 posicions que hem de fer referencia. //
     rep insb // Inserim els valors al vector entrat.//
    }
}


/****** PALETA => DAC ******/


void SetPalette(byte far *paleta,word inici,word final)
{
 final=(final<<1)+(final<<0); // final*=3;
 inici=(inici<<1)+(inici<<0); // inici*=3;
 final=(final-inici)+3;
 asm{
     lds si,paleta //???//
     add si,[inici]
     mov dx,3c8h // Direccio del registre d' escritura de la paleta DAC (Digital Analog Converter) //
     xor al,al // mov al,0 //
     out dx,al // Enviem el valor llegit al la paleta //
     inc dx // Ara dx es 3c9 podem escriure o llegir //
     mov cx,[final] // 256x3 posicions que hem de fer referencia. //
     rep outsb // Escriu en el port DX i incrementa SI+1//
    }
}


int  CarregarPaleta(byte *NOM_PALETA,byte *PALETA)
{
 int x;
 FILE *file;

 if( (file = fopen (NOM_PALETA,"rb")) == NULL)
 {
  return 0;
 }

 for(x=0;x<768;x++) PALETA[x] = fgetc(file);

 fclose(file);

 return 1;

}




void WaitVRetrace()
{

     asm mov dx,0x3DA
  et1:
    asm{ 
	in al,dx
	and al,0x08
	jnz et1
       }
  et2:
    asm { 
	 in al,dx
	 and al,0x08
	 jz et2
	}

}


void CopiaPaleta(byte *pal_dest,byte *pal_origen,word inici,word final)
{
 int i;
 for(i=inici*3;i<=final*3+2;i++) pal_dest[i]=pal_origen[i];
}


void RestauraPaleta(unsigned char *pal_dest,byte *pal_origen,unsigned int inici,unsigned int final)
{
 int i;
 for(i=inici*3;i<=final*3+2;i++) pal_dest[i]=pal_origen[i];
}

int ColorIgual(byte *p1,byte *p2,byte color1,byte color2)
{
 // Returna 1 si els colors (GREEN,BLUE,RED) sขn iguals segons dos color de paletes diferents.

 return ((p1[color1*3] == p2[color2*3]) && (p1[color1*3+1] == p2[color2*3+1]) && (p1[color1*3+2] == p2[color2*3+2]));

}




void XchangeColor(byte *paleta,byte color1,byte color2)
{
 // Intercanvia un color de una paleta.

 byte R,G,B;
 R=paleta[color1*3];
 G=paleta[color1*3+1];
 B=paleta[color1*3+2];
 paleta[color1*3]=paleta[color2*3];
 paleta[color1*3+1]=paleta[color2*3+1];
 paleta[color1*3+2]=paleta[color2*3+2];
 paleta[color2*3]=R;
 paleta[color2*3+1]=G;
 paleta[color2*3+2]=B;

}


void PaletaNegre(byte *paleta,word inici,word final)
{
 int i;
 for(i=inici*3;i<=final*3+2;i++) paleta[i]=0;
}

void PaletaBlanca(byte *paleta,word inici,word final)
{
 int i;
 for(i=inici*3;i<=final*3+2;i++) paleta[i]=63;
}




void VisualitzarPaleta(void)
{
 int color_actual,y=20,x=0;
 byte LONG;
 OutText(centred(160,13),5,"PALETA ACTUAL\0",0,0,0,FONTMT,VIDEO);

 for(color_actual=0;color_actual<=255;color_actual++)
 {
  if((color_actual+1<10)&&(color_actual+1>=0)) LONG=1;
  if((color_actual+1<100)&&(color_actual+1>=10)) LONG=2;
  if((color_actual+1>=100)) LONG=3;
  rectangle_ple(x,y,23,8,color_actual,VIDEO);
  Visualitzar_Numero(x,y,word(color_actual+1),LONG,0,VIDEO);
  x+=24;
  if(x>305) {y+=9; x=0;}

 }
}






/*

void Visualitzar_PaletaX(byte page)
{
 word color_actual,y=20,x=0;
 byte LONG;
 OutTextX(centred(160,13),5,"PALETA ACTUAL0",0,0,0,page);
 SetPageX(page);
 ClearScreen(NEGRE,VIDEO);
 for(color_actual=0;color_actual<=255;color_actual++)
 {
  if((color_actual+1<10)&(color_actual+1>=0)) LONG=1;
  if((color_actual+1<100)&(color_actual+1>=10)) LONG=2;
  if((color_actual+1>=100)) LONG=3;
  RectangleX(x,y,23,8,color_actual,page);
  Visualitzar_NumeroX(x,y,color_actual+1,LONG,page);
  x+=24;
  if(x>305) {y+=9; x=0;}

 }
}
*/







/*
   ษออออออออออออออออออป
   บ                  บ
   บ  EFECTES PALETA  บ
   บ                  บ
   ศออออออออออออออออออผ

*/



void FadeOut(unsigned int inici,unsigned int final)
{
 tpaleta paleta4;

 int x,y;

 GetPalette(paleta4,inici,final);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
  {
   if (paleta4[x]>0) paleta4[x]--;
  }
  WaitVRetrace();
  SetPalette(paleta4,inici,final);
 }
}



void FadeIn(byte *paleta,word inici,word final)
{
 tpaleta paleta2;

 int x,y;

 PaletaNegre(paleta2,inici,final);
 SetPalette(paleta2,inici,final);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (paleta[x]!=paleta2[x])
    paleta2[x]++;
  WaitVRetrace();
  SetPalette(paleta2,0,255);
 }
}



void ImpactIn(word inici,word final)
{
 tpaleta paleta2;

 int x,y;

 GetPalette(paleta2,inici,final);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (paleta2[x]<63)
    paleta2[x]++;
  WaitVRetrace();
  SetPalette(paleta2,inici,final);

 }
}


void ImpactOut(byte *paleta,word inici,word final)
{
 tpaleta paleta2;
 int x,y;

 PaletaBlanca(paleta2,0,255);

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (paleta[x]!=paleta2[x])
    paleta2[x]--;

  WaitVRetrace();
  SetPalette(paleta2,inici,final);
 }
}


void RotatePaletteLeft(byte far *paleta,byte color_i,byte color_f)
{
 word i;
 byte inicial[3];

 inicial[0]=paleta[(color_i)*3];
 inicial[1]=paleta[(color_i)*3+1];
 inicial[2]=paleta[(color_i)*3+2];

 for(i=color_i;i<color_f;i++)
 {
  paleta[(i*3)]=paleta[(i*3)+3];
  paleta[(i*3)+1]=paleta[(i*3)+4];
  paleta[(i*3)+2]=paleta[(i*3)+5];
 }
 paleta[(color_f)*3+2]=inicial[2];
 paleta[(color_f)*3+1]=inicial[1];
 paleta[(color_f)*3]=inicial[0];


 SetPalette(paleta,0,255);
 WaitVRetrace();


}


void RotatePaletteRight(byte far *paleta,word color_i,word color_f)
{
 word i;
 byte final[3];

 final[2]=paleta[color_f*3+2];
 final[1]=paleta[color_f*3+1];
 final[0]=paleta[color_f*3];

 for(i=color_f;i>color_i;i--)
 {
  paleta[i*3]=paleta[i*3-3];
  paleta[i*3+1]=paleta[i*3-2];
  paleta[i*3+2]=paleta[i*3-1];
 }
 paleta[color_i*3+2]=final[2];
 paleta[color_i*3+1]=final[1];
 paleta[color_i*3]=final[0];
 SetPalette(paleta,0,255);
 WaitVRetrace();

}



void MorphPalette(byte *pal_dest,byte* pal_origen,word inici,word final)
{
 // Descripcio: Fa una  igualtat de paletes observant el canvi k es produeix.

 word y,x;

 for(y=0;y<63;y++)
 {
  for(x=inici*3;x<=final*3+2;x++)
   if (pal_dest[x]<pal_origen[x])
    pal_origen[x]--;
   else
   {
      if (pal_dest[x]>pal_origen[x])
    pal_origen[x]++;


   }
  WaitVRetrace();
  SetPalette(pal_origen,inici,final);
 }


}

