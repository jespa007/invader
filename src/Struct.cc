

void tInvader::UnLoadStage1()
{
 int i;


 for(i=0;i<MAX_MOVIMENTS;i++)
 {
  free(moviments[i]);
 }


 for(i=0;i<MAX_SPRITES;i++) free((tImatge)Imatges[i]);


 for(i=0;i<MAX_BLOCS;i++)
 {
  free(Blocs[i]);
 }

 free(Mapa);


}



void tInvader::LoadStage1()  // Carregar Imatges !!!
{

 byte Motiu0[]={"Mem�ria insuficient !!!.\0"};
 byte Motiu1[]={"No s'ha pogut obrir el arxiu \"mapa1.dat !!!\".\0"};
 byte Motiu2[]={"No s'ha pogut obrir el arxiu \"blocs1.raw !!!\".\0"};
 byte Motiu3[]={"No s'ha pogut obrir el arxiu \"sprites1.raw !!!\".\0"};

 int i,j,k=0,x,y,sprites=0;

 FILE *fitxer2 = NULL;



 tImatge I=NULL;


 if(!InicialitzarMoviments()) Quit(Motiu0);
 


 if((Mapa=(byte *)malloc(MAX_BLOCS_Y*MAX_BLOCS_X))==NULL) Quit(Motiu0);

 if( (fitxer2 = fopen("dat//mapa1.dat","rb")) == NULL ) Quit(Motiu1);

 for(i=0;i<MAX_BLOCS_Y;i++) fread(Mapa+i*MAX_BLOCS_X,MAX_BLOCS_X,1,fitxer2) ;

 fclose(fitxer2); // Millor k el tanqui ara, k encara m'el deixar� obert. :)

 // Carreguem els blocs...


 if(!CarregarImatgeVScreen("grafics//blocs1.raw",BUFFER1)) Quit(Motiu2);



 for(i=0;i<MAX_BLOCS;i++)
 {
   if( (Blocs[i] = (tImatge)malloc(AMPLADA_BLOC*ALTURA_BLOC)) == NULL) Quit(Motiu0);
 }



 for(y=0;(y<200)&&(k<MAX_BLOCS);y+=ALTURA_BLOC)
 {
  for(x=0;(x<320)&&(k<MAX_BLOCS);x+=AMPLADA_BLOC)
  {
   // Assignem memoria...

   for(i=0;i<ALTURA_BLOC;i++)
    for(j=0;j<AMPLADA_BLOC;j++)
      Blocs[k][i*AMPLADA_BLOC+j] = BUFFER1[(y+i)*320+j+x];

   k++; // Bloc pr�xim.
  }
 }


 // Crea la Matriu Inversa...

   for(y=0;y<ALTURA_BLOC;y++)
   {
    for(x=0;x<AMPLADA_BLOC;x++)
    {

     BLOCINVERS[y*AMPLADA_BLOC+x] = (AMPLADA_BLOC)*(AMPLADA_BLOC-1) - y*(AMPLADA_BLOC) + x;
    
    }
   }




 // Creem els els blocs invertits...


 for(k=48;k<MAX_BLOCS;k++)
 {

  for(j=0;j<=((AMPLADA_BLOC)*(AMPLADA_BLOC)-1);j++)
  Blocs[k][j] = Blocs[k-48+14][BLOCINVERS[j]];

 }






 if(!CarregarImatgeVScreen((char *)&"grafics//sprites1.raw",BUFFER1)) Quit(Motiu3);

 // Carreguem Imatges 8x8 tot reservant mem�ria...


 k=0;

 while(k<MAX_SPR_8X8)
 {
  I = (tImatge)malloc(DIM_SPR_8X8*DIM_SPR_8X8+2);
  if((Imatges[k]=I) == NULL)
  {
   UnLoadStage1();
   Quit(Motiu0);
  }
  Imatges[k][0] = DIM_SPR_8X8;
  Imatges[k][1] = DIM_SPR_8X8;
  k++;
  
 }

 k = 0;

 for(y=0;(y<ALTURA_PANTALLA)&&(k<MAX_SPR_8X8);y+=DIM_SPR_8X8)
 {
  for(x=0;(x<320)&&(k<MAX_SPR_8X8);x+=DIM_SPR_8X8)
  {

   for(i=0;i<DIM_SPR_8X8;i++)
    for(j=0;j<DIM_SPR_8X8;j++)
      Imatges[k][2+i*DIM_SPR_8X8+j] = BUFFER1[(y+i)*320+j+x];

   k++; // Bloc pr�xim.
  }
 }

 sprites = sprites + k; // M�s sprites!


 // Carreguem Imatges 16x16 tot reservant mem�ria...

 for(k=0;k<MAX_SPR_16X16;k++)
 {

  I = (tImatge)malloc(DIM_SPR_16X16*DIM_SPR_16X16+2);
  if((Imatges[sprites+k]=I) == NULL)
  {
   UnLoadStage1();
   Quit(Motiu0);
  }
  Imatges[sprites+k][0] = DIM_SPR_16X16;
  Imatges[sprites+k][1] = DIM_SPR_16X16;

 }

 k=0;

 for(y=0;(y<ALTURA_PANTALLA)&&(k<MAX_SPR_16X16);y+=DIM_SPR_16X16)
 {
  for(x=0;(x<320)&&(k<MAX_SPR_16X16);x+=DIM_SPR_16X16)
  {

   for(i=0;i<DIM_SPR_16X16;i++)
    for(j=0;j<DIM_SPR_16X16;j++)
      Imatges[sprites+k][2+i*DIM_SPR_16X16+j] = BUFFER1[N_FILES_SPR_8X8*320*DIM_SPR_8X8+(y+i)*320+j+x];

   k++; // Bloc pr�xim.
  }
 }

 sprites = sprites + k; // M�s sprites!

 // Carreguem Imatges 32x32 tot reservant mem�ria...

 for(k=0;k<MAX_SPR_32X32;k++)
 {
  I = (tImatge)malloc(DIM_SPR_32X32*DIM_SPR_32X32+2);
  if((Imatges[sprites+k]=I) == NULL)
  {
   UnLoadStage1();
   Quit(Motiu0);
  }
  Imatges[sprites+k][0] = DIM_SPR_32X32;
  Imatges[sprites+k][1] = DIM_SPR_32X32;

 }

 k=0;

 for(y=0;(y<ALTURA_PANTALLA)&&(k<MAX_SPR_32X32);y+=DIM_SPR_32X32)
 {
  for(x=0;(x<320)&&(k<MAX_SPR_32X32);x+=DIM_SPR_32X32)
  {

   for(i=0;i<DIM_SPR_32X32;i++)
    for(j=0;j<DIM_SPR_32X32;j++)
      Imatges[sprites+k][2+i*DIM_SPR_32X32+j] = BUFFER1[(N_FILES_SPR_8X8*320*DIM_SPR_8X8) + (N_FILES_SPR_16X16*320*DIM_SPR_16X16) + ((y+i)*320 + j + x)];

   k++; // Bloc pr�xim.
  }
 }
 
 sprites = sprites + k; // M�s sprites!

 // Carreguem Imatges 64x64 tot reservant mem�ria...

 for(k=0;k<MAX_SPR_64X64;k++)
 {
  I = (tImatge)malloc(DIM_SPR_64X64*DIM_SPR_64X64+2);
  if((Imatges[sprites+k]=I) == NULL)
  {
   UnLoadStage1();
   Quit(Motiu0);
  }
  Imatges[sprites+k][0] = DIM_SPR_64X64;
  Imatges[sprites+k][1] = DIM_SPR_64X64;

 }

 k=0;

 for(y=0;(y<ALTURA_PANTALLA)&&(k<MAX_SPR_64X64);y+=DIM_SPR_64X64)
 {
  for(x=0;(x<320)&&(k<MAX_SPR_64X64);x+=DIM_SPR_64X64)
  {

   for(i=0;i<DIM_SPR_64X64;i++)
    for(j=0;j<DIM_SPR_64X64;j++)
      Imatges[sprites+k][2+i*DIM_SPR_64X64+j] = BUFFER1[(N_FILES_SPR_8X8*320*DIM_SPR_8X8) + (N_FILES_SPR_16X16*320*DIM_SPR_16X16) + (N_FILES_SPR_32X32*320*DIM_SPR_32X32) + ((y+i)*320 + j + x)];

   k++; // Bloc pr�xim.
  }
 }



 // Definim els tipus de sprite...

 // DEFINICIONS SPRITES 8X8...


  Sprites[0].impactable = NO;
  Sprites[0].invencible = NO;
  Sprites[0].agresiu = NO;
  Sprites[0].retard_dispar = 0;
  Sprites[0].vx = Sprites[0].vy = 2;
  Sprites[0].dimx = Sprites[0].dimy = 8;
  
  Sprites[1].impactable = NO;
  Sprites[1].invencible = NO;
  Sprites[1].agresiu = NO;
  Sprites[1].retard_dispar = 0;
  Sprites[1].vx = Sprites[1].vy = 2;
  Sprites[1].dimx = Sprites[1].dimy = 8;
  
  Sprites[2].impactable = NO;
  Sprites[2].invencible = NO;
  Sprites[2].agresiu = NO;
  Sprites[2].retard_dispar = 0;
  Sprites[2].vx = Sprites[2].vy = 4;
  Sprites[2].dimx = Sprites[2].dimy = 8;

  Sprites[3].impactable = NO;
  Sprites[3].invencible = NO;
  Sprites[3].agresiu = NO;
  Sprites[3].retard_dispar = 0;
  Sprites[3].vx = Sprites[3].vy = 4;
  Sprites[3].dimx = Sprites[3].dimy = 8;

  Sprites[4].impactable = SI;
  Sprites[4].invencible = NO;
  Sprites[4].agresiu = NO;
  Sprites[4].retard_dispar = 0;
  Sprites[4].vx = Sprites[4].vy = 1;
  Sprites[4].dimx = Sprites[4].dimy = 8;

  for(i=5;i<17;i++)
  {
   Sprites[i].impactable = NO;
   Sprites[i].invencible = NO;
   Sprites[i].agresiu = NO;
   Sprites[i].retard_dispar = 0;
   Sprites[i].vx = Sprites[i].vy = 0;
   Sprites[i].dimx = Sprites[i].dimy = 8;
  }


  Sprites[17].impactable = NO;
  Sprites[17].invencible = NO;
  Sprites[17].agresiu = NO;
  Sprites[17].retard_dispar = 0;
  Sprites[17].vx = Sprites[17].vy = 4;
  Sprites[17].dimx = Sprites[17].dimy = 16;

  Sprites[18].impactable = NO;
  Sprites[18].invencible = NO;
  Sprites[18].agresiu = NO;
  Sprites[18].retard_dispar = 0;
  Sprites[18].vx = Sprites[18].vy = 4;
  Sprites[18].dimx = Sprites[18].dimy = 16;

  Sprites[19].impactable = NO;
  Sprites[19].invencible = NO;
  Sprites[19].agresiu = NO;
  Sprites[19].retard_dispar = 0;
  Sprites[19].vx = Sprites[19].vy = 4;
  Sprites[19].dimx = Sprites[19].dimy = 16;

  Sprites[20].impactable = NO;
  Sprites[20].invencible = NO;
  Sprites[20].agresiu = NO;
  Sprites[20].retard_dispar = 0;
  Sprites[20].vx = Sprites[20].vy = 4;
  Sprites[20].dimx = Sprites[20].dimy = 16;


 for(i=21;i<28;i++)
 {
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 0;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }

 // La meva nau...
 
 for(i=28;i<30;i++)
 {

  Sprites[i].impactable = SI;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = SI;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 2;
  Sprites[i].dimx = Sprites[i].dimy = 16;

 }

 for(i=30;i<33;i++)
 {
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 0;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }


  Sprites[33].impactable = SI;
  Sprites[33].invencible = NO;
  Sprites[33].agresiu = NO;
  Sprites[33].retard_dispar = 0;
  Sprites[33].vx = Sprites[33].vy = 1;
  Sprites[33].dimx = Sprites[33].dimy = 16;


  Sprites[34].impactable = NO;
  Sprites[34].invencible = NO;
  Sprites[34].agresiu = NO;
  Sprites[34].retard_dispar = 0;
  Sprites[34].vx = Sprites[34].vy = 0;
  Sprites[34].dimx = Sprites[34].dimy = 16;


  Sprites[35].impactable = SI;
  Sprites[35].invencible = NO;
  Sprites[35].agresiu = NO;
  Sprites[35].retard_dispar = 0;
  Sprites[35].vx = Sprites[35].vy = 1;
  Sprites[35].dimx = Sprites[35].dimy = 16;


  Sprites[36].impactable = NO;
  Sprites[36].invencible = NO;
  Sprites[36].agresiu = NO;
  Sprites[36].retard_dispar = 0;
  Sprites[36].vx = Sprites[36].vy = 0;
  Sprites[36].dimx = Sprites[36].dimy = 16;


 for(i=36;i<40;i++)
 {
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 1;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }


 for(i=40;i<43;i++)
 {
  Sprites[i].impactable = SI;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = BALA1;
  Sprites[i].retard_dispar = 100;
  Sprites[i].vx = Sprites[i].vy = 1;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }

 
  Sprites[43].impactable = SI;
  Sprites[43].invencible = NO;
  Sprites[43].agresiu = NO;
  Sprites[43].retard_dispar = 0;
  Sprites[43].vx = Sprites[43].vy = 2;
  Sprites[43].dimx = Sprites[43].dimy = 16;


  Sprites[44].impactable = SI;
  Sprites[44].invencible = NO;
  Sprites[44].agresiu = NO;
  Sprites[44].retard_dispar = 0;
  Sprites[44].vx = Sprites[44].vy = 2;
  Sprites[44].dimx = Sprites[44].dimy = 16;


  Sprites[45].impactable = SI;
  Sprites[45].invencible = NO;
  Sprites[45].agresiu = BALA3;
  Sprites[45].retard_dispar = SEGUENT_POSICIO_AMB_TRANSICIO_Y;
  Sprites[45].vx = Sprites[45].vy = 2;
  Sprites[45].dimx = Sprites[45].dimy = 16;


  Sprites[46].impactable = SI;
  Sprites[46].invencible = SI;
  Sprites[46].agresiu = NO;
  Sprites[46].retard_dispar = 0;
  Sprites[46].vx = Sprites[46].vy = 2;
  Sprites[46].dimx = Sprites[46].dimy = 16;

  Sprites[47].impactable = SI;
  Sprites[47].invencible = NO;
  Sprites[47].agresiu = NO;
  Sprites[47].retard_dispar = 0;
  Sprites[47].vx = Sprites[47].vy = 0;
  Sprites[47].dimx = Sprites[47].dimy = 16;

  Sprites[48].impactable = SI;
  Sprites[48].invencible = NO;
  Sprites[48].agresiu = BALA1;
  Sprites[48].retard_dispar = 9;
  Sprites[48].vx = Sprites[48].vy = 0;
  Sprites[48].dimx = Sprites[48].dimy = 16;

for(i=49;i<53;i++)
{
  Sprites[i].impactable = SI;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 2;
  Sprites[i].dimx = Sprites[i].dimy = 16;
}


  Sprites[53].impactable = SI;
  Sprites[53].invencible = NO;
  Sprites[53].agresiu = NO;
  Sprites[53].retard_dispar = 0;
  Sprites[53].vx = Sprites[53].vy = 2;
  Sprites[53].dimx = Sprites[53].dimy = 16;


  Sprites[54].impactable = SI;
  Sprites[54].invencible = NO;
  Sprites[54].agresiu = NO;
  Sprites[54].retard_dispar = 0;
  Sprites[54].vx = Sprites[54].vy = 1;
  Sprites[54].dimx = Sprites[54].dimy = 16;

  Sprites[55].impactable = SI;
  Sprites[55].invencible = NO;
  Sprites[55].agresiu = BALA1;
  Sprites[55].retard_dispar = 0;
  Sprites[55].vx = Sprites[55].vy = 0;
  Sprites[55].dimx = Sprites[55].dimy = 16;

  Sprites[56].impactable = SI;
  Sprites[56].invencible = NO;
  Sprites[56].agresiu = NO;
  Sprites[56].retard_dispar = 0;
  Sprites[56].vx = Sprites[56].vy = 1;
  Sprites[56].dimx = Sprites[56].dimy = 16;


  Sprites[57].impactable = SI;
  Sprites[57].invencible = NO;
  Sprites[57].agresiu = NO;
  Sprites[57].retard_dispar = 0;
  Sprites[57].vx = Sprites[57].vy = 2;
  Sprites[57].dimx = Sprites[57].dimy = 16;

  Sprites[58].impactable = SI;      // BOLA 1...
  Sprites[58].invencible = NO;
  Sprites[58].agresiu = BALA1;
  Sprites[58].retard_dispar = 100;
  Sprites[58].vx = Sprites[58].vy = 2;
  Sprites[58].dimx = Sprites[58].dimy = 16;

  Sprites[59].impactable = SI;      // BOLA 2...
  Sprites[59].invencible = NO;
  Sprites[59].agresiu = BALA1;
  Sprites[59].retard_dispar = 100;
  Sprites[59].vx = Sprites[59].vy = 2;
  Sprites[59].dimx = Sprites[59].dimy = 16;

  Sprites[60].impactable = SI;       // ENEMIC 7
  Sprites[60].invencible = NO;
  Sprites[60].agresiu = BALA1;
  Sprites[60].retard_dispar = 100;
  Sprites[60].vx = Sprites[60].vy = 1;
  Sprites[60].dimx = Sprites[60].dimy = 16;


  Sprites[61].impactable = SI;
  Sprites[61].invencible = NO;
  Sprites[61].agresiu = BALA1;
  Sprites[61].retard_dispar = 100;
  Sprites[61].vx = Sprites[61].vy = 1;
  Sprites[61].dimx = Sprites[61].dimy = 16;


  Sprites[62].impactable = SI;
  Sprites[62].invencible = NO;
  Sprites[62].agresiu = BALA1;
  Sprites[62].retard_dispar = 100;
  Sprites[62].vx = Sprites[62].vy = 1;
  Sprites[62].dimx = Sprites[62].dimy = 16;


  Sprites[63].impactable = SI;
  Sprites[63].invencible = NO;
  Sprites[63].agresiu = BALA1;
  Sprites[63].retard_dispar = 100;
  Sprites[63].vx = Sprites[63].vy = 1;
  Sprites[63].dimx = Sprites[63].dimy = 16;


  Sprites[64].impactable = SI;    // TORRETA
  Sprites[64].invencible = NO;
  Sprites[64].agresiu = BALA1;
  Sprites[64].retard_dispar = 80;
  Sprites[64].vx = Sprites[64].vy = 1;
  Sprites[64].dimx = Sprites[64].dimy = 16;


  Sprites[65].impactable = SI;     // PERSEGUIDOR
  Sprites[65].invencible = NO;
  Sprites[65].agresiu = BALA1;
  Sprites[65].retard_dispar = 100;
  Sprites[65].vx = Sprites[65].vy = 1;
  Sprites[65].dimx = Sprites[65].dimy = 16;


  Sprites[66].impactable = SI;
  Sprites[66].invencible = NO;
  Sprites[66].agresiu = LASER1;
  Sprites[66].retard_dispar = RETARD_DISPAR >> dificultat;
  Sprites[66].vx = Sprites[66].vy = 2;
  Sprites[66].dimx = Sprites[66].dimy = 16;


  Sprites[67].impactable = SI;
  Sprites[67].invencible = NO;
  Sprites[67].agresiu = SI;
  Sprites[67].retard_dispar = 10;
  Sprites[67].vx = Sprites[67].vy = 2;
  Sprites[67].dimx = Sprites[67].dimy = 16;


  Sprites[68].impactable = SI;
  Sprites[68].invencible = SI;
  Sprites[68].agresiu = NO;
  Sprites[68].retard_dispar = 0;
  Sprites[68].vx = Sprites[68].vy = 1;
  Sprites[68].dimx = Sprites[68].dimy = 16;



  Sprites[69].impactable = SI;
  Sprites[69].invencible = SI;
  Sprites[69].agresiu = NO;
  Sprites[69].retard_dispar = 0;
  Sprites[69].vx = Sprites[69].vy = 1;
  Sprites[69].dimx = Sprites[69].dimy = 16;


  Sprites[70].impactable = SI;
  Sprites[70].invencible = SI;
  Sprites[70].agresiu = NO;
  Sprites[70].retard_dispar = 0;
  Sprites[70].vx = Sprites[70].vy = 1;
  Sprites[70].dimx = Sprites[70].dimy = 16;

  Sprites[71].impactable = SI;
  Sprites[71].invencible = NO;
  Sprites[71].agresiu = BALA1;
  Sprites[71].retard_dispar = 14;
  Sprites[71].vx = Sprites[71].vy = 1;
  Sprites[71].dimx = Sprites[71].dimy = 16;


  Sprites[72].impactable = SI;
  Sprites[72].invencible = NO;
  Sprites[72].agresiu = BALA1;
  Sprites[72].retard_dispar = RETARD_DISPAR >> dificultat;
  Sprites[72].vx = Sprites[72].vy = 1;
  Sprites[72].dimx = Sprites[72].dimy = 16;

 for(i=73;i<77;i++)
 {
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 1;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }

  Sprites[77].impactable = NO;
  Sprites[77].invencible = NO;
  Sprites[77].agresiu = ENEMICD;
  Sprites[77].retard_dispar = 24;
  Sprites[77].vx = Sprites[77].vy = 1;
  Sprites[77].dimx = Sprites[77].dimy = 16;



 for(i=78;i<82;i++)
 {
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 1;
  Sprites[i].dimx = Sprites[i].dimy = 16;
 }

  Sprites[82].impactable = NO;
  Sprites[82].invencible = NO;
  Sprites[82].agresiu = ENEMICE;
  Sprites[82].retard_dispar = 24;
  Sprites[82].vx = Sprites[82].vy = 1;
  Sprites[82].dimx = Sprites[82].dimy = 16;


  Sprites[83].impactable = NO;
  Sprites[83].invencible = NO;
  Sprites[83].agresiu = NO;
  Sprites[83].retard_dispar = 0;
  Sprites[83].vx = Sprites[83].vy = 4;
  Sprites[83].dimx = Sprites[83].dimy = 16;

// Sprites 32 X 32

for(i=84;i<88;i++)
{
  Sprites[i].impactable = NO;
  Sprites[i].invencible = NO;
  Sprites[i].agresiu = NO;
  Sprites[i].retard_dispar = 0;
  Sprites[i].vx = Sprites[i].vy = 0;
  Sprites[i].dimx = Sprites[i].dimy = 32;
}

  Sprites[88].impactable = SI;
  Sprites[88].invencible = NO;
  Sprites[88].agresiu = LASER2;
  Sprites[88].retard_dispar = 10;
  Sprites[88].vx = Sprites[88].vy = 4;
  Sprites[88].dimx = Sprites[88].dimy = 32;

// Sprites 64 X 64

  Sprites[89].impactable = NO;
  Sprites[89].invencible = NO;
  Sprites[89].agresiu = LASER1;
  Sprites[89].retard_dispar = 100;
  Sprites[89].vx = Sprites[89].vy = 1;
  Sprites[89].dimx = Sprites[89].dimy = 64;


  for(i=0;i<MAX_SPRITES;i++) Sprites[i].imatge = (tImatge) (Imatges[i]+2);


 // Inicialitzem Objectes...




  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+7,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+8,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+9,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+10,5,SI);


  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+1,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+2,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+3,5,SI);
  Objectes[ENEMIC_1].EntrarDades(10<<dificultat,150,0,0);

  Objectes[TURBO].AfegirFrame(1,MAX_SPR_8X8+14,5,NO);
  Objectes[TURBO].AfegirFrame(1,MAX_SPR_8X8+15,5,NO);


  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+4,5,NO);
  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+5,5,NO);
  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+6,5,SI);

  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+2,10,NO);
  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+5,10,NO);
  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+6,10,SI);



  Objectes[ITEM1].AfegirFrame(1,MAX_SPR_8X8+20,0,NO);
  Objectes[ITEM2].AfegirFrame(1,MAX_SPR_8X8+21,0,NO);
  Objectes[ITEM3].AfegirFrame(1,MAX_SPR_8X8+22,0,NO);


  Objectes[BALA_ENEMIC_1].AfegirFrame(1,0,5,NO);
  Objectes[BALA_ENEMIC_1].AfegirFrame(1,1,5,NO);


  Objectes[BALA_ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+66,0,NO);

  Objectes[LA_MEVA_BALA_1].AfegirFrame(1,2,0,NO);
  Objectes[LA_MEVA_BALA_1].EntrarDades(10,150,0,0);

  Objectes[LA_MEVA_BALA_2].AfegirFrame(1,3,0,NO);
  Objectes[LA_MEVA_BALA_2].EntrarDades(10,150,0,0);

  Objectes[LA_MEVA_BALA_3].AfegirFrame(1,MAX_SPR_8X8,0,NO);
  Objectes[LA_MEVA_BALA_3].EntrarDades(20,0,0,0);


  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,3,12,NO);
  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,MAX_SPR_8X8+2,12,NO);
  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,MAX_SPR_8X8+3,INFINIT,NO);
  Objectes[LA_MEVA_BALA_4].EntrarDades(25,0,0,0);

  Objectes[LA_MEVA_BALA_5].AfegirFrame(1,MAX_SPR_8X8+1,0,NO);
  Objectes[LA_MEVA_BALA_5].EntrarDades(20,0,0,0);


  Objectes[_PERSONATGE].AfegirFrame(0,MAX_SPR_8X8+11,0,NO);
  Objectes[_PERSONATGE].AfegirFrame(1,MAX_SPR_8X8+12,0,NO);
  Objectes[_PERSONATGE].AfegirFrame(2,MAX_SPR_8X8+13,0,NO);
  Objectes[_PERSONATGE].EntrarDades(2,0,0,200);


  Objectes[_CAIXA1].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);
  Objectes[_CAIXA2].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);
  Objectes[_CAIXA3].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);

  Objectes[CAIXA_DESTRUIDA].AfegirFrame(1,MAX_SPR_8X8+17,2,SI);

  Objectes[_METEORIT1].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT1].EntrarDades(10<<dificultat,100,ITEM1,0);

  Objectes[_METEORIT2].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT2].EntrarDades(10<<dificultat,100,ITEM2,0);

  Objectes[_METEORIT3].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT3].EntrarDades(10<<dificultat,100,ITEM3,0);

  Objectes[METEORIT_DESTRUIT].AfegirFrame(1,MAX_SPR_8X8+19,5,SI);

  Objectes[ENEMIC_1].AfegirFrame(0,MAX_SPR_8X8+23,10,NO);
  Objectes[ENEMIC_1].AfegirFrame(1,MAX_SPR_8X8+24,10,NO);
  Objectes[ENEMIC_1].AfegirFrame(2,MAX_SPR_8X8+25,10,NO);
  Objectes[ENEMIC_1].EntrarDades(10<<dificultat,100,0,0);
  
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+26,SEGUENT_MOVIMENT_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+27,6,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+28,12,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+27,6,NO);
  Objectes[ENEMIC_2].EntrarDades(15<<dificultat,430,0,0);


  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+29,30,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+30,5,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+31,10,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+30,5,NO);
  Objectes[ENEMIC_3].EntrarDades(15<<dificultat,300,0,0);

  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+32,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+33,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+34,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+35,5,NO);
  Objectes[ENEMIC_4].EntrarDades(5<<dificultat,200,BALA3,0);


  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+36,SEGUENT_POSICIO_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+37,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+38,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+39,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+40,SEGUENT_POSICIO_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+39,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+38,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+37,0,NO);
  Objectes[ENEMIC_5].EntrarDades(15<<dificultat,200,0,0);


  Objectes[ENEMIC_6].AfegirFrame(1,MAX_SPR_8X8+41,5,NO);
  Objectes[ENEMIC_6].AfegirFrame(1,MAX_SPR_8X8+42,5,NO);
  Objectes[ENEMIC_6].EntrarDades(20<<dificultat,150,0,0);

  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+43,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+44,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+45,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+46,5,NO);
  Objectes[ENEMIC_7].EntrarDades(20<<dificultat,300,0,0);


  Objectes[ENEMIC_8].AfegirFrame(1,MAX_SPR_8X8+47,0,NO);
  Objectes[ENEMIC_8].EntrarDades(50<<dificultat,500,0,0);

  Objectes[ENEMIC_9].AfegirFrame(1,MAX_SPR_8X8+48,0,NO);
  Objectes[ENEMIC_9].EntrarDades(100<<dificultat,500,0,0);

  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+51,300,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_10].EntrarDades(200<<dificultat,1000,0,0);

  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+51,200,NO);  // iguaL
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_11].EntrarDades(200<<dificultat,1000,0,0);


  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+51,100,NO);  // iguaL
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_12].EntrarDades(400<<dificultat,1000,0,0);




  Objectes[ENEMIC_13].AfegirFrame(1,MAX_SPR_8X8+55,0,NO);

  Objectes[BOLA_ENERGIA].AfegirFrame(1,4,1,NO);
  Objectes[BOLA_ENERGIA].EntrarDades(700<<dificultat,2000,0,0);

  Objectes[_BOSS1].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+MAX_SPR_32X32,1,NO);

  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+56,200,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+57,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+58,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+59,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+60,50,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+59,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+58,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+57,5,NO);

  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+61,100,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+62,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+63,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+64,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+65,50,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+64,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+63,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+62,5,NO);

  // Definicio dels Conjunts..



  Conjunts[PERSONATGE].AfegirObjecte(Objectes[_PERSONATGE],0,0,NO,INFINIT);

//  Conjunts[BALA].AfegirObjecte(Objectes[BALA_ENEMIC1],0,0,NO,INFINIT);
//  Conjunts[LASER].AfegirObjecte(Objectes[BALA_ENEMIC2],0,0,NO,INFINIT);


  Conjunts[ENEMIC1].AfegirObjecte(Objectes[ENEMIC_1],0,0,NO,INFINIT);

  Conjunts[ENEMIC2].AfegirObjecte(Objectes[ENEMIC_2],0,0,NO,INFINIT);
  Conjunts[ENEMIC3].AfegirObjecte(Objectes[ENEMIC_3],0,0,NO,INFINIT);
  Conjunts[ENEMIC4].AfegirObjecte(Objectes[ENEMIC_4],0,0,NO,INFINIT);
  Conjunts[ENEMIC5].AfegirObjecte(Objectes[ENEMIC_5],0,0,NO,INFINIT);
  Conjunts[ENEMIC6].AfegirObjecte(Objectes[ENEMIC_6],0,0,NO,INFINIT);
  Conjunts[ENEMIC7].AfegirObjecte(Objectes[ENEMIC_7],0,0,NO,INFINIT);
  Conjunts[ENEMIC8].AfegirObjecte(Objectes[ENEMIC_8],0,0,NO,INFINIT);
  Conjunts[ENEMIC9].AfegirObjecte(Objectes[ENEMIC_9],0,0,NO,INFINIT);
  Conjunts[ENEMIC10].AfegirObjecte(Objectes[ENEMIC_10],0,0,NO,INFINIT);
  Conjunts[ENEMIC11].AfegirObjecte(Objectes[ENEMIC_11],0,0,NO,INFINIT);
  Conjunts[ENEMIC12].AfegirObjecte(Objectes[ENEMIC_12],0,0,NO,INFINIT);
  Conjunts[ENEMIC13].AfegirObjecte(Objectes[ENEMIC_13],0,0,NO,INFINIT);

  Conjunts[METEORIT1].AfegirObjecte(Objectes[_METEORIT1],0,0,NO,INFINIT);
  Conjunts[METEORIT2].AfegirObjecte(Objectes[_METEORIT2],0,0,NO,INFINIT);
  Conjunts[METEORIT3].AfegirObjecte(Objectes[_METEORIT3],0,0,NO,INFINIT);

  Conjunts[CAIXA1].AfegirObjecte(Objectes[_CAIXA1],0,0,NO,INFINIT);
  Conjunts[CAIXA2].AfegirObjecte(Objectes[_CAIXA2],0,0,NO,INFINIT);
  Conjunts[CAIXA3].AfegirObjecte(Objectes[_CAIXA3],0,0,NO,INFINIT);


  Conjunts[BOSS1].AfegirObjecte(Objectes[_BOSS1],0,0,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_10],8,25,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_11],40,25,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_12],24,40,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[COMPORTES_DRETA],48,0,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[BOLA_ENERGIA],28,10,SI,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[COMPORTES_ESQUERRA],0,0,NO,INFINIT);


  // Moviments b�siques per fer rutes...

  for(i=0;i<10;i++) {Moviments[i].AfegirPart(20-(2*i),1,1,0,1,14);Moviments[10+i].AfegirPart((i*2),1,-1,0,1,14);Moviments[20+i].AfegirPart(20-(i*2),-1,-1,0,1,14);Moviments[30+i].AfegirPart(0+(i*2),-1,1,0,1,14);}
  Moviments[40].AfegirPart(20,1,1,0,1,7);
  Moviments[40].AfegirPart(15,-1,1,0,1,1);
  Moviments[40].AfegirPart(8,-1,1,0,1,1);
  Moviments[40].AfegirPart(4,-1,1,0,1,1);
  Moviments[40].AfegirPart(2,-1,1,0,1,1);
  Moviments[40].AfegirPart(2,-1,-1,0,1,1);
  Moviments[40].AfegirPart(4,-1,-1,0,1,1);
  Moviments[40].AfegirPart(8,-1,-1,0,1,1);
  Moviments[40].AfegirPart(15,-1,-1,0,1,1);

  Moviments[40].AfegirPart(20,1,-1,0,1,3);

  Moviments[40].AfegirPart(15,1,-1,0,1,1);
  Moviments[40].AfegirPart(8,1,-1,0,1,1);
  Moviments[40].AfegirPart(4,1,-1,0,1,1);
  Moviments[40].AfegirPart(2,1,-1,0,1,1);

  Moviments[40].AfegirPart(0,1,1,0,1,2);

  Moviments[40].AfegirPart(2,1,1,0,1,1);
  Moviments[40].AfegirPart(4,1,1,0,1,1);
  Moviments[40].AfegirPart(8,1,1,0,1,1);
  Moviments[40].AfegirPart(15,1,1,0,1,1);

  Moviments[40].AfegirPart(20,1,1,0,1,10);



  Moviments[41].AfegirPart(20,1,1,0,1,7);
  Moviments[41].AfegirPart(15,1,1,0,1,1);
  Moviments[41].AfegirPart(8,1,1,0,1,1);
  Moviments[41].AfegirPart(4,1,1,0,1,1);
  Moviments[41].AfegirPart(2,1,1,0,1,1);
  Moviments[41].AfegirPart(2,1,-1,0,1,1);
  Moviments[41].AfegirPart(4,1,-1,0,1,1);
  Moviments[41].AfegirPart(8,1,-1,0,1,1);
  Moviments[41].AfegirPart(15,1,-1,0,1,1);

  Moviments[41].AfegirPart(20,1,-1,0,1,3);

  Moviments[41].AfegirPart(15,-1,-1,0,1,1);
  Moviments[41].AfegirPart(8,-1,-1,0,1,1);
  Moviments[41].AfegirPart(4,-1,-1,0,1,1);
  Moviments[41].AfegirPart(2,-1,-1,0,1,1);

  Moviments[41].AfegirPart(0,-1,1,0,1,2);

  Moviments[41].AfegirPart(2,-1,1,0,1,1);
  Moviments[41].AfegirPart(4,-1,1,0,1,1);
  Moviments[41].AfegirPart(8,-1,1,0,1,1);
  Moviments[41].AfegirPart(15,-1,1,0,1,1);

  Moviments[41].AfegirPart(20,1,1,0,1,10);



  Moviments[42].AfegirPart(21,-1,1,0,1,1);
  Moviments[42].AfegirPart(2,-1,1,0,1,6);
  Moviments[42].AfegirPart(22,-1,1,0,1,1);
  Moviments[42].AfegirPart(21,1,1,0,1,1);
  Moviments[42].AfegirPart(2,1,1,0,1,6);
  Moviments[42].AfegirPart(22,1,1,0,1,1);

  Moviments[42].AfegirPart(21,-1,1,0,1,1);
  Moviments[42].AfegirPart(2,-1,1,0,1,6);
  Moviments[42].AfegirPart(22,-1,1,0,1,1);
  Moviments[42].AfegirPart(21,1,1,0,1,1);
  Moviments[42].AfegirPart(2,1,1,0,1,6);
  Moviments[42].AfegirPart(22,1,1,0,1,1);
  Moviments[42].AfegirPart(20,1,1,0,2,7);




  Moviments[43].AfegirPart(21,1,1,0,1,1);
  Moviments[43].AfegirPart(2,1,1,0,1,6);
  Moviments[43].AfegirPart(22,1,1,0,1,1);
  Moviments[43].AfegirPart(21,-1,1,0,1,1);
  Moviments[43].AfegirPart(2,-1,1,0,1,6);
  Moviments[43].AfegirPart(22,-1,1,0,1,1);
  Moviments[43].AfegirPart(21,1,1,0,1,1);
  Moviments[43].AfegirPart(2,1,1,0,1,6);
  Moviments[43].AfegirPart(22,1,1,0,1,1);
  Moviments[43].AfegirPart(21,-1,1,0,1,1);
  Moviments[43].AfegirPart(2,-1,1,0,1,6);
  Moviments[43].AfegirPart(22,-1,1,0,1,1);
  Moviments[43].AfegirPart(20,1,1,0,2,7);


  Moviments[44].AfegirPart(0,1,1,0,1,10);
  Moviments[44].AfegirPart(21,1,1,0,1,1);

  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,-1,1,0,1,1);
  Moviments[44].AfegirPart(0,-1,1,0,1,7);
  Moviments[44].AfegirPart(21,-1,1,0,1,1);
  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,1,1,0,1,1);
  Moviments[44].AfegirPart(0,1,1,0,1,7);
  Moviments[44].AfegirPart(21,1,1,0,1,1);

  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,-1,1,0,1,1);
  Moviments[44].AfegirPart(0,-1,1,0,1,7);
  Moviments[44].AfegirPart(21,-1,1,0,1,1);
  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,1,1,0,1,1);
  Moviments[44].AfegirPart(0,1,1,0,1,7);
  Moviments[44].AfegirPart(21,1,1,0,1,1);

  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,-1,1,0,1,1);
  Moviments[44].AfegirPart(0,-1,1,0,1,7);
  Moviments[44].AfegirPart(21,-1,1,0,1,1);
  Moviments[44].AfegirPart(20,-1,1,0,1,1);
  Moviments[44].AfegirPart(22,1,1,0,1,1);
  Moviments[44].AfegirPart(0,1,1,0,1,7);
  Moviments[44].AfegirPart(21,1,1,0,1,1);
  Moviments[44].AfegirPart(20,-1,1,0,1,1);


  Moviments[45].AfegirPart(0,-1,1,0,1,10);
  Moviments[45].AfegirPart(21,-1,1,0,1,1);

  Moviments[45].AfegirPart(20,-1,1,0,1,1);
  Moviments[45].AfegirPart(22,1,1,0,1,1);
  Moviments[45].AfegirPart(0,1,1,0,1,7);
  Moviments[45].AfegirPart(21,1,1,0,1,1);
  Moviments[45].AfegirPart(20,-1,1,0,1,1);
  Moviments[45].AfegirPart(22,-1,1,0,1,1);
  Moviments[45].AfegirPart(0,-1,1,0,1,7);
  Moviments[45].AfegirPart(21,-1,1,0,1,1);
  Moviments[45].AfegirPart(20,-1,1,0,1,1);
  Moviments[45].AfegirPart(22,1,1,0,1,1);
  Moviments[45].AfegirPart(0,1,1,0,1,7);
  Moviments[45].AfegirPart(21,1,1,0,1,1);
  Moviments[45].AfegirPart(20,-1,1,0,1,1);
  Moviments[45].AfegirPart(22,-1,1,0,1,1);
  Moviments[45].AfegirPart(0,-1,1,0,1,7);
  Moviments[45].AfegirPart(21,-1,1,0,1,1);
  Moviments[45].AfegirPart(20,-1,1,0,1,1);
  Moviments[45].AfegirPart(22,1,1,0,1,1);
  Moviments[45].AfegirPart(0,1,1,0,1,7);
  Moviments[45].AfegirPart(21,1,1,0,1,1);
  Moviments[45].AfegirPart(20,-1,1,0,1,1);

  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);

  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);

  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(0,-1,1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);
  Moviments[46].AfegirPart(21,-1,1,0,1,1);
  Moviments[46].AfegirPart(20,1,1,0,1,1);
  Moviments[46].AfegirPart(22,1,1,0,1,1);
  Moviments[46].AfegirPart(0,1,1,0,1,1);
  Moviments[46].AfegirPart(21,1,-1,0,1,1);
  Moviments[46].AfegirPart(22,-1,-1,0,1,1);






  Moviments[47].AfegirPart(20,1,-1,0,1,5);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(16,1,-1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(8,1,-1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(2,1,-1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(0,1,1,0,1,1);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(2,1,1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(8,1,1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(16,1,1,0,1,2);// Surt de Sota... de l'esquerre.
  Moviments[47].AfegirPart(20,1,1,0,1,5);// Surt de Sota... de l'esquerre.


  Moviments[48].AfegirPart(20,-1,-1,0,1,5);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(16,-1,-1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(8,-1,-1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(2,-1,-1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(0,-1,1,0,1,1);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(2,-1,1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(8,-1,1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(16,-1,1,0,1,2);// Surt de Sota... de la dreta.
  Moviments[48].AfegirPart(20,-1,1,0,1,5);// Surt de Sota... de la dreta.


  Moviments[49].AfegirPart(20,1,1,0,1,6);// Surt de Sota...
  Moviments[49].AfegirPart(23,1,1,0,1,1);// Surt de Sota...
  Moviments[49].AfegirPart(16,1,-1,0,1,12);// Surt de Sota...


  Moviments[50].AfegirPart(20,1,1,0,2,4);
  Moviments[50].AfegirPart(16,-1,1,AUTO2,1,INFINIT);

  Moviments[51].AfegirPart(16,-1,1,AUTO1,1,INFINIT);

  Moviments[52].AfegirPart(20,1,-1,0,2,7);
  Moviments[52].AfegirPart(20,1,1,0,1,1);
  Moviments[52].AfegirPart(20,1,1,MANUAL,1,INFINIT);

  Moviments[53].AfegirPart(20,1,1,0,1,6);// Surt de Sota...
  Moviments[53].AfegirPart(23,-1,1,0,1,1);// Surt de Sota...
  Moviments[53].AfegirPart(16,-1,-1,0,1,12);// Surt de Sota...

/*
  Moviments[54].AfegirPart(16,1,1,0,1,10);
  Moviments[54].AfegirPart(16,1,-1,0,1,10);
*/

  Moviments[55].AfegirPart(0,1,1,DETECTA_POSX1,1,23);
  Moviments[55].AfegirPart(16,1,1,0,2,23);

  Moviments[56].AfegirPart(0,-1,1,DETECTA_POSX2,1,23);
  Moviments[56].AfegirPart(16,-1,1,0,2,23);

  Moviments[59].AfegirPart(20,1,1,0,2,13);
  Moviments[60].AfegirPart(10,1,1,0,2,23);
  Moviments[61].AfegirPart(10,-1,1,0,2,23);
  Moviments[62].AfegirPart(20,1,-1,0,5,23);


}






