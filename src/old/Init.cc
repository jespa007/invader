void Quit(byte *Motiu);
//void UnLoadStage1(void);


void InicialitzarDrivers()
{
 
	SetVideo();
	InicialitzarTeclat();

}



int InicialitzarEstructura(void)
{

// if(SB) loadsounds("snd\\sons.snd");// arxiu de sons

 if((BUFFER1 = VScreen())==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
 if((BUFFER2 = VScreen())==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
 if((BUFFER3 = VScreen())==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
// if((BUFFER4 = VScreen())==NULL) return 0; // Ens entrega el punter i la seva adre‡a.



 // Carregar de les fonts...



 if(!CarregarFontMonoTextura()) return 0;
 if(!CarregarFontMitjana()) return 0;
 if(!CarregarFontGran()) return 0;

 return 1;

}



void Quit(byte *Motiu)
{


   Lliurar_VSBuffer(BUFFER1);
   Lliurar_VSBuffer(BUFFER2);
   Lliurar_VSBuffer(BUFFER3);
//   Lliurar_VSBuffer(BUFFER4);

   printf("%s",Motiu);
   
//   SetPalette(paleta3,0,255);
}




