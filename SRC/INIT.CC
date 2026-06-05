void Quit(byte *Motiu);
//void UnLoadStage1(void);


void InicialitzarDrivers()
{
  gotoxy(1,3);
  textcolor(GROC);
  cprintf(" * Ratol¡ : ");


  if(!Init_Mouse())
  {
   textcolor(VERMELL_CLAR);
   cprintf("No s'ha detectat !");
   gotoxy(1,24);
   clrscr();
   exit(EXIT_FAILURE);
  }

  textcolor(VERD_CLAR);
  cprintf("Ok");

  SB=FALSE; // Per defecte...



   gotoxy(1,5);
   textcolor(GROC);
   cprintf(" * Sound Blaster : ");
   if (!detect_settings(&baseio, &irq, &dma, &dma16)){
        textcolor(VERMELL_CLAR);
        cprintf("Variable BLASTER inv lida o no existent !");
             gotoxy(1,24);

    }
    else{
         if (!init_sb(baseio, irq, dma, dma16)){
          textcolor(VERMELL_CLAR);
          cprintf("No es pot inicialitzar la tarjeta de so !");
             gotoxy(1,24);

        }
        else
        {

         textcolor(VERD_CLAR);
         cprintf("OK");
         gotoxy(1,7);
         textcolor(GROC);
         cprintf(" * Memoria XMS : ");

         if (!init_xms()){
                textcolor(VERMELL_CLAR);
                cprintf("No s'ha detectat el controlador !  (SOUND BLASTER DESCTIVADA)");
             gotoxy(1,24);

           }
           if (getfreexms() < XMSREQUIRED){
                textcolor(VERMELL_CLAR);
                cprintf("%uk  Mem¢ria XMS insuficient !  (SOUND BLASTER DESCTIVADA)",getfreexms());
                gotoxy(1,24);

                
           } else
           {
             init_mixing();
             textcolor(VERD_CLAR);
             cprintf("Ok");
             gotoxy(1,24);
             SB = CERT;


           }



        }
   }


 delay(1000);


/*
 gotoxy(1,24);
 delay(1000);
*/
 InstalarTeclado();
  

}



int InicialitzarEstructura(void)
{

 if(SB) loadsounds("snd\\sons.snd");// arxiu de sons

 if((BUFFER1 = VScreen(&VSCREEN1))==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
 if((BUFFER2 = VScreen(&VSCREEN2))==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
 if((BUFFER3 = VScreen(&VSCREEN3))==NULL) return 0; // Ens entrega el punter i la seva adre‡a.
// if((BUFFER4 = VScreen(&VSCREEN4))==NULL) return 0; // Ens entrega el punter i la seva adre‡a.



 // Carregar de les fonts...



 if(!CarregarFontMonoTextura()) return 0;
 if(!CarregarFontMitjana()) return 0;
 if(!CarregarFontGran()) return 0;

 return 1;

}



void Quit(byte *Motiu)
{
   SetMode3();

  DesinstalarTeclado();

   if(SB)
   {
    shutdown();
    freesounds();
   }

   Lliurar_VSBuffer(BUFFER1);
   Lliurar_VSBuffer(BUFFER2);
   Lliurar_VSBuffer(BUFFER3);
//   Lliurar_VSBuffer(BUFFER4);

   printf("%s",Motiu);
   
   asm mov ax,4c00h // Interrupcio per sortir al MS-DOS
   asm int 21h

//   SetPalette(paleta3,0,255);
}




