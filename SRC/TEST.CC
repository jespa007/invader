/*
void tInvader::VisualitzarSprites()
{
 word k=0,y,x;
 byte far *video_buffer = (byte far *)MK_FP(VIDEO,0);

 do{
  ClearScreen(NEGRE,VIDEO);
  for(y=0;y<Sprites[k].dimy;y++)
   for(x=0;x<Sprites[k].dimx;x++)
     video_buffer[y*320+x] = Sprites[k].imatge[(Sprites[k].dimx)*y+x];

     if(Sprites[k].agresiu)
     {

      OutText(0,90,(byte *)&"BALA ENEMIC 1!\0",0,0,0,MEDFNT,VIDEO);
      OutText(0,90+ALTURA_LLETRAM,(byte *)&"RETARD\0",0,0,0,FONTMT,VIDEO);Visualitzar_Numero(8*8, 90+ALTURA_LLETRAM,Sprites[k].retard_dispar,3,VIDEO);

     }
     if(Sprites[k].invencible) OutText(0,90+2*ALTURA_LLETRAM,(byte *)&"INVENCIBLE!\0",0,0,0,MEDFNT,VIDEO);
     if(Sprites[k].impactable) OutText(0,90+3*ALTURA_LLETRAM,(byte *)&"IMPACTABLE!\0",0,0,0,MEDFNT,VIDEO);
     
     OutText(0,90+5*ALTURA_LLETRAM,(byte *)&"SPRITE \0",0,0,0,FONTMT,VIDEO);Visualitzar_Numero(8*8, 90+5*ALTURA_LLETRAM,k,3,VIDEO);

  k++;
 }while((tolower(getch())!='s') && k<MAX_SPRITES);

}




void tInvader::VisualitzarBlocs()
{
 word k=0,y,x;
 byte far *video_buffer = (byte far *)MK_FP(VIDEO,0);

 do{
  ClearScreen(NEGRE,VIDEO);
  for(y=0;y<ALTURA_BLOC;y++)
   for(x=0;x<AMPLADA_BLOC;x++)
     video_buffer[y*320+x] = Blocs[k][AMPLADA_BLOC*y+x];


  k++;
 }while((tolower(getch())!='s') && k<MAX_BLOCS);

}


void tInvader::VisualitzarObjectes()
{
 tObjecte PART1,PART2;
 int posx=140,posy=90;
 int i=0;

 do{
   PART1 = Objectes[i];
   PART2 = PART1;
   PART2.Centre();
   int posx=140,posy=90;

   PART2.EntrarCoordenades(posx,posy);

   do{

    ClearScreen(NEGRE,VSCREEN1);

    if(letras[DRETA]){posx += 4;}// Anirem cap a la dreta...
    if(letras[ESQUERRA]){posx -= 4;} // Anirem cap a la esquerra...
    if(letras[AVALL]) posy += 4;
    if(letras[AMUNT]) posy -= 4;

    PART2.ActualitzarCoordenades(posx,posy);

     PART2.EscriureActual(VSCREEN1);

        
     Flip_VScreen(VIDEO,VSCREEN1);
     delay(50);

     PART2.EscriureActual(VSCREEN1);

        
     Flip_VScreen(VIDEO,VSCREEN1);
     delay(100);
     PART2.SeguentFrame(0,0);

  }while(!letras[DISPAR]&&!PART2.ActualEsNul());

  delay(500);
  i++;
 }while(!letras[BOMBA]&&i<MAX_OBJECTE);


}


void tInvader::VisualitzarConjunts() // En definitiva tots som un conjunt, o no ?
{
 tConjunt Actual;
 int posx,posy;
 int i=0;
 int counter = 1;

 posx = posy = 0;

do{

 Actual=Conjunts[i];
 do{


     Actual.AfegirObjecte(Objectes[IMPACTE],0,0,NO,INFINIT);

     if(letras[ESQUERRA]) posx-=8;
     if(letras[AMUNT]) posy-=8;
     if(letras[DRETA]) posx+=8;
     if(letras[AVALL]) posy+=8;

     Actual.ActualitzarCoordenades(posx,posy);


    ClearScreen(NEGRE,VSCREEN1);
    Actual.EscriureObjectes(VSCREEN1);
    WaitVRetrace();
    Flip_VScreen(VIDEO,VSCREEN1);

    Actual.ActualitzarConjunt(0,0);
    if(counter<5) counter++;

 }while(!letras[DISPAR]);
 i++;
 delay(500);
 }while(!letras[BOMBA]&&i<MAX_CONJUNT);
}




void tInvader::ProbarMoviments()
{

 tObjecte Nau;
 int v=2;
 char c='o';
 int x=0,y=0;
 int xi=0,yi=0;
 int i=0,j,k;
 int ypos=1;
 int xpos=1;
 int swapxy=0;
 int final=0;
 int obj=0;

 PMoviment PInici,PAnterior,PNou,PActual,L = NULL; // Punter al moviment...



 // Creaci¢ de un moviment personalitzat...


 x=xi;y=yi;

 ClearScreen(NEGRE,VIDEO);
 ClearScreen(NEGRE,VSCREEN1);


do{

  switch(c)
  {
   case 'O':if(obj<MAX_OBJECTE) obj++;
            Nau=Objectes[obj];
            break;
           
   case 'o':if(obj>0) obj--;
            Nau=Objectes[obj];
            break;
   case 'e':ClearScreen(NEGRE,VIDEO);
            OutText(0,0,(byte *)&"POSA COORDENADA X",0,0,0,0,VIDEO);
            scanf("%i",&xi);
            ClearScreen(NEGRE,VIDEO);
            OutText(0,0,(byte *)&"POSA COORDENADA Y",0,0,0,0,VIDEO);
            scanf("%i",&yi);
            break;
   case 'v':if(v>1) v/=2;break;
   case 'V':if(v<8) v*=2;break;
   case '+':if(i<MAX_MOVIMENTS) i++;break;
   case '-':if(i>0) i--;break;
   case 'n':x=xi;y=yi;ClearScreen(NEGRE,VIDEO);

            PActual = L;

            if(L!=NULL)
            {

             while((PActual->PSeguent!=NULL)&&(PActual->PSeguent!=L))
            {
             PAnterior = PActual;
             PActual = PActual -> PSeguent;
             free(PAnterior);
            }

            free(PActual);
            PActual = L = NULL;

           }



            break;
   case 'y':ypos = ypos*(-1);break;
   case 'x':xpos = xpos*(-1);break;
   case 'p':
            if(L!=NULL)
            {

            ClearScreen(NEGRE,VIDEO);
        
            OutText(0,0,(byte *)&"HO VOLS AMB LOOP ?\0",0,0,0,0,VIDEO);

            c=tolower(getch());

            while((c!='s')&&(c!='n'))  c=tolower(getch());


            if(c=='n')
            {
             PActual->PSeguent = NULL;
            }
            else
            {
             PActual->PSeguent = L;
            }

            PInici = L;
            k=0;
            x=xi;
            y=yi;


            Nau.EntrarCoordenades(xi,yi);



            do{

             PInici -> vegades = 0;


             while((PInici->vegades)<MAX_POSICIONS)
             {
              ClearScreen(NEGRE,VSCREEN1);
              Nau.EscriureActual(VSCREEN1);
              Nau.ActualitzarCoordenades(x+moviments[(PInici->Moviment)][(PInici->vegades)].x*(PInici->xpos),y+moviments[(PInici->Moviment)][(PInici->vegades)].y*(PInici->ypos));
              PInici -> vegades+=PInici -> v;

              WaitVRetrace();
              delay(50);
              Nau.SeguentFrame(0,0);
              Flip_VScreen(VIDEO,VSCREEN1);
             }

             x += moviments[(PInici->Moviment)][MAX_POSICIONS-1].x*(PInici->xpos);
             y += moviments[(PInici->Moviment)][MAX_POSICIONS-1].y*(PInici->ypos);

             PInici = PInici -> PSeguent;

             if(PInici==L) k++; // Seguent volta...

            }while((PInici!=NULL)&&(k<10));

            getch();
            }

            ClearScreen(NEGRE,VSCREEN1);
            break;

   case 'd': for(j=0;j<MAX_POSICIONS;j++)
             {
              if(!final)
              {
               PutPixel(x+moviments[i][j].x*xpos,y+moviments[i][j].y*ypos,BLANC,VSCREEN1);
              }
              else
              {
               PutPixel(x+moviments[i][MAX_POSICIONS-j-1].x*xpos,y+moviments[i][MAX_POSICIONS-j-1].y*ypos,BLANC,VIDEO);delay(5);
              }
             }

             x+=moviments[i][MAX_POSICIONS-1].x*xpos;
             y+=moviments[i][MAX_POSICIONS-1].y*ypos;
         
             if( (PNou = (PMoviment)malloc(sizeof(M))) == NULL) exit(-1);

             PNou -> Moviment = i;
             PNou -> xpos = xpos;
             PNou -> ypos = ypos;
             PNou -> v = v;
             PNou -> PSeguent = NULL;

             if(L==NULL) // First;
             {

              PActual = L = PNou;

             }
             else // Apuntem al ultim punter...
             {

              PActual -> PSeguent = PNou;
              PActual = PActual->PSeguent;

             }

          

 }

 rectangle_ple(319-129,0,129,64,NEGRE,VSCREEN1);
 Nau.EntrarCoordenades(190,0);
 Nau.EscriureActual(VSCREEN1);

 WaitVRetrace();
 Flip_VScreen(VIDEO,VSCREEN1);
 rectangle(319-64,0,64,64,255);
 OutText(0,0,(byte *)&"MOVIMENT=\0",0,0,0,0,VIDEO); 
 OutText(0,8,(byte *)&"XPOS   YPOS   V\0",0,0,0,0,VIDEO);
 Visualitzar_Numero(9*8,0,i,3,VIDEO);
 if(xpos<0) Visualitzar_Numero(4*8,8,000,3,VIDEO);
 else Visualitzar_Numero(4*8,8,001,3,VIDEO);
 if(ypos<0) Visualitzar_Numero(11*8,8,000,3,VIDEO);
 else Visualitzar_Numero(11*8,8,001,3,VIDEO);
 Visualitzar_Numero(15*8,8,v,3,VIDEO);


 for(j=0;j<MAX_POSICIONS;j++)
 {
  if(!final)
  {
   if(!swapxy) { PutPixel(320-32+moviments[i][j].x*xpos,32+moviments[i][j].y*ypos,BLANC,VIDEO);delay(5); }
   else { PutPixel(320-32+moviments[i][j].y*ypos,32+moviments[i][j].x*xpos,BLANC,VIDEO); delay(5); }
  }
  else
  {
   if(!swapxy) { PutPixel(320-32+moviments[i][MAX_POSICIONS-j-1].x*xpos,32+moviments[i][MAX_POSICIONS-j-1].y*ypos,BLANC,VIDEO);delay(5); }
   else { PutPixel(320-32+moviments[i][MAX_POSICIONS-j-1].y*ypos,32+moviments[i][MAX_POSICIONS-j-1].x*xpos,BLANC,VIDEO); delay(5); }
  }
 }


 }while(!((c=getch())=='s'));

 PActual = L;

 if(L!=NULL)
 {

  while((PActual->PSeguent!=NULL)&&(PActual->PSeguent!=L))
  {
   PAnterior = PActual;
   PActual = PActual -> PSeguent;
   free(PAnterior);
  }

  free(PActual);
  PActual = L = NULL;

 }



}



void tInvader::TestMoviments()
{
 int i=51;
 tObjecte Enemic,Jo;

 int myposy = 120,x=160;
 int myposx = 100,y=-15;

 Jo = Objectes[14];
 Enemic = Objectes[19];

 do{
  x=104;
  y=0;
  Moviments[i].EntrarCoordenades(x,y);
  do{
   ClearScreen(NEGRE,VSCREEN1);

   if(letras[AMUNT]&&(myposy>=0)) myposy -= 2;
   else if(letras[AVALL]&&((myposy+16)<ALTURA_PANTALLA)) myposy += 2;

   if(letras[ESQUERRA]&&(myposx>=0)) myposx -= 2;
   else if(letras[DRETA]&&((myposx+16)<AMPLADA_PANTALLA)) myposx += 2;

   Enemic.ActualitzarCoordenades(x,y);
   Jo.ActualitzarCoordenades(myposx,myposy);
   Enemic.EscriureActual(VSCREEN1);
   Jo.EscriureActual(VSCREEN1);
   Moviments[i].SeguentPosicio(&x,&y,myposx,myposy,1,1,16);

   if(HiHaInterseccio(x,y,myposx,myposy,16,16)) OutText(0,0,"CACA",0,0,0,0,VSCREEN1);

   Enemic.SeguentFrame(0,0);
   Jo.SeguentFrame(0,0);

   WaitVRetrace();
   delay(50);
   Flip_VScreen(VIDEO,VSCREEN1);

  }while(!letras[DISPAR]&&!Moviments[i].EsNul());
 i++;
 }while(!letras[BOMBA]&&(i<52));

}


void tInvader::TestRutes()
{
 int i=0;
 int x,myposx=100;
 int y,myposy=100;
 tObjecte Enemic,Jo;

 Jo = Objectes[14];
 Enemic = Objectes[19];

 do{
  x=104;
  y=-2;
  Rutes[i].EntrarCoordenades(x,y);


  do{

   ClearScreen(NEGRE,VSCREEN1);

   if(letras[AMUNT]&&(myposy>=0)) myposy -= 2;
   else if(letras[AVALL]&&((myposy+16)<ALTURA_PANTALLA)) myposy += 2;

   if(letras[ESQUERRA]&&(myposx>=0)) myposx -= 2;
   else if(letras[DRETA]&&((myposx+16)<AMPLADA_PANTALLA)) myposx += 2;

   Enemic.ActualitzarCoordenades(x,y);
   Jo.ActualitzarCoordenades(myposx,myposy);
   Enemic.EscriureActual(VSCREEN1);
   Jo.EscriureActual(VSCREEN1);
   Rutes[i].SeguentPosicio(&x,&y,myposx,myposy,1,1,16);

   WaitVRetrace();
   Enemic.SeguentFrame(0,0);
   Jo.SeguentFrame(0,0);

//   WaitVRetrace();
   Flip_VScreen(VIDEO,VSCREEN1);
   



  }while(!letras[DISPAR]&&!Rutes[i].EsNul());
 i++;
 }while(!letras[BOMBA]&&(i<2));
}


// DISPARS



void tInvader::TestDispars()
{

typedef struct SHOTS
{
 int x,y;
 tObjecte  Shot;
 tMoviment Mov;
 SHOTS *PSeguent;
};

typedef SHOTS *PShots;

 int p;
 int myposy = 0,x=0;
 int myposx = 0,y=0;

 int Retard = RETARD_DISPAR;
 int RetardE2 = 2; 

 int PowerUp = 1;


 PShots PAnterior,PAux,Shot4=NULL,Shot1=NULL,Shot2=NULL,Shot3=NULL,MyShots=NULL,EnemyShots=NULL;

 tConjunt Enemic,Jo;


 Jo = Conjunts[0];
 Enemic = Conjunts[1];


 do{

   myposx=0;
   myposy=0;

   x=104;
   y=90;

   Moviments[51].EntrarCoordenades(x,y);

   do{



   ClearScreen(NEGRE,VSCREEN1);






   if(letras[AMUNT]&&(myposy>0)) myposy -= 2;
   else if(letras[AVALL]&&((myposy+16)<ALTURA_PANTALLA)) myposy += 2;

   if(letras[ESQUERRA]&&(myposx>0)) myposx -= 2;
   else if(letras[DRETA]&&((myposx+16)<AMPLADA_PANTALLA)) myposx += 2;

   if(letras[DISPAR]&&(Retard == 0))
   {

    if(PowerUp == 1)
    {

     Shot1= new SHOTS;
     Shot1->x=myposx+4;
     Shot1->y=myposy;
    
     Shot1->Mov = Moviments[20];
     Shot1->Mov.EntrarCoordenades(Shot1->x,Shot1->y);
     Shot1->Shot=Objectes[9];
     Shot1->PSeguent = MyShots;

    }


    else
    {

     Shot1 =(PShots) new SHOTS;Shot2 =(PShots) new SHOTS;Shot3 =(PShots) new SHOTS;


     Shot1->x=myposx;
     Shot1->y=myposy;

     Shot1->Mov=Moviments[20];
     Shot1->Mov.EntrarCoordenades(Shot1->x,Shot1->y);
     Shot1->PSeguent=Shot2;

     Shot2->x=myposx+4;
     Shot2->y=myposy;
     Shot2->Mov=Moviments[24];
     Shot2->Mov.EntrarCoordenades(Shot2->x,Shot2->y);
     Shot2->PSeguent=Shot3;

     Shot3->x=myposx+4;
     Shot3->y=myposy;
     Shot3->Mov=Moviments[16];
     Shot3->Mov.EntrarCoordenades(Shot3->x,Shot3->y);
    

     if(PowerUp == 5) 
     {
     Shot4 =(PShots) new SHOTS;

     Shot3->PSeguent=Shot4;

     Shot4->x=myposx;
     Shot4->y=myposy-4;
     Shot4->Mov=Moviments[20];
     Shot4->Mov.EntrarCoordenades(Shot4->x,Shot4->y);
     Shot4->PSeguent=Shot3;
     Shot4->PSeguent = MyShots;

     }
     else Shot3->PSeguent=MyShots;




     switch(PowerUp)
     {

      case 2:
             Shot1->x=myposx+4;
             Shot1->y=myposy;
             Shot1->Mov.EntrarCoordenades(Shot1->x,Shot1->y);

             Shot1->Shot=Objectes[9];
             Shot2->Shot=Objectes[10];
             Shot3->Shot=Objectes[10];
             break;
      case 3:Shot1->Shot=Objectes[11];
             Shot2->Shot=Objectes[10];
             Shot3->Shot=Objectes[10];
             break;
      case 4:Shot1->Shot=Objectes[11];
             Shot2->Shot=Objectes[12];
             Shot3->Shot=Objectes[12];
             break;
      case 5:Shot1->Shot=Objectes[11];
             Shot2->Shot=Objectes[12];
             Shot3->Shot=Objectes[12];
             Shot4->Shot=Objectes[13];

     }
    }
  
 

    MyShots = Shot1;
    
    Retard = RETARD_DISPAR;
   }

   if((RetardE2==0)&&((x >= myposx-16)&&(x<myposx+24)))
   {
    Shot1 = new SHOTS;Shot2 = new SHOTS;

    Shot1->x=x-4;
    Shot1->y=y;
    Shot1->Mov=Moviments[0];//Moviments[ElMeuMoviment(Shot2->x,Shot2->y,myposx+8,myposy+8,16)];
    Shot1->Mov.EntrarCoordenades(Shot1->x,Shot1->y);
    Shot1->Shot=Objectes[8];
    Shot1->PSeguent=Shot2;


    Shot2->x=x+4;
    Shot2->y=y;
    Shot2->Mov=Moviments[0];//Moviments[ElMeuMoviment(Shot2->x,Shot2->y,myposx+8,myposy+8,16)];
    Shot2->Mov.EntrarCoordenades(Shot2->x,Shot2->y);
    Shot2->Shot=Objectes[8];
    Shot2->PSeguent=EnemyShots;

    EnemyShots = Shot1;

    RetardE2 = 2;
   }

   PAux = MyShots;

   while(PAux != NULL)
   {
    if(PAux->Mov.EsNul()||(p=HiHaInterseccio(x,y,PAux->x,PAux->y,16,Sprites[PAux->Shot.SpriteActual()].dimx)))
    {

     if(p) Enemic.AfegirObjecte(Objectes[3],0,0,0,-1);


     if(PAux == MyShots)
     {
      PAnterior = PAux;
      MyShots = PAux = PAux -> PSeguent;
      delete PAnterior;
     }
     else
     {
       PAnterior = MyShots;
       while(PAnterior->PSeguent != PAux) PAnterior = PAnterior -> PSeguent;
       PAnterior -> PSeguent = PAux -> PSeguent;
       PAnterior = PAux;
       PAux = PAux -> PSeguent;
       delete PAnterior;
     }
    }
    else
    {  


     PAux->Mov.SeguentPosicio(&(PAux->x),&(PAux->y),myposx,myposy,4,4,Sprites[PAux->Shot.SpriteActual()].dimx);
     PAux->Shot.SeguentFrame(0,0);
     PAux->Shot.ActualitzarCoordenades(PAux->x,PAux->y);
     PAux->Shot.EscriureActual(VSCREEN1);
     PAux=PAux->PSeguent;
    }

   }

   PAux = EnemyShots;

   while(PAux != NULL)
   {
    if(PAux->Mov.EsNul()||(p=HiHaInterseccio(myposx,myposy,PAux->x,PAux->y,16,Sprites[PAux->Shot.SpriteActual()].dimx)))
    {

     if(p) Jo.AfegirObjecte(Objectes[0],0,0,0,-1);


     if(PAux == EnemyShots)
     {
      PAnterior = PAux;
      EnemyShots = PAux = PAux -> PSeguent;
      delete PAnterior;
     }
     else
     {
       PAnterior = EnemyShots;
       while(PAnterior->PSeguent != PAux) PAnterior = PAnterior -> PSeguent;
       PAnterior -> PSeguent = PAux -> PSeguent;
       PAnterior = PAux;
       PAux = PAux -> PSeguent;
       delete PAnterior;
     }
    }
    else
    {  

     PAux->Mov.SeguentPosicio(&(PAux->x),&(PAux->y),myposx,myposy,4,4,Sprites[PAux->Shot.SpriteActual()].dimx);

     PAux->Shot.ActualitzarCoordenades(PAux->x,PAux->y);
     PAux->Shot.SeguentFrame(0,0);
     PAux->Shot.EscriureActual(VSCREEN1);
     PAux=PAux->PSeguent;
    }




   }
  

   Moviments[51].SeguentPosicio(&x,&y,myposx,myposy,1,1,16);


   Enemic.ActualitzarCoordenades(x,y);
   Jo.ActualitzarCoordenades(myposx,myposy);
   Enemic.EscriureObjectes(VSCREEN1);
   Jo.EscriureObjectes(VSCREEN1);

   Enemic.ActualitzarConjunt(0,0);
   Jo.ActualitzarConjunt(0,0);

   WaitVRetrace();
   delay(50);



   Flip_VScreen(VIDEO,VSCREEN1);


   if(Retard>0) Retard--;
   if(RetardE2>0) RetardE2--;

  }while(!letras[BOMBA]);

 delay(500);
 PowerUp++; 

 }while(PowerUp<6);


 if(MyShots != NULL)
 {

  if((PAux=MyShots) != NULL)
  {
   while(PAux!=NULL)
   {
    PAnterior = PAux;
    PAux = PAux -> PSeguent;
    delete PAnterior;

   }
   MyShots = PAux = NULL;
  }
 }

 if((PAux=EnemyShots) != NULL)
 {
   while(PAux!=NULL)
   {
    PAnterior = PAux;
    PAux = PAux -> PSeguent;
    delete PAnterior;

   }
   EnemyShots = PAux = NULL;

 }

}



*/
