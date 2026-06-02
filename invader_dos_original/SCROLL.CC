
void Scrollejar(int POSICIO_Y,int SCROLL_Y,word SEGMENT);



void Scrollejar(int POSY,int SCROLLY,int OFFSET,word SEGMENT)
{
 int i,j,POSX;

 for(i=0;i<(ALTURA_PANTALLA+ALTURA_BLOC);i+=ALTURA_BLOC) // [0,32,64,...,200]
 {
  POSX=0;

  for(j=0;j<AMPLADA_PANTALLA;j+=AMPLADA_BLOC) // [0,32,64,...,320]
  {
    PutBlock(j+OFFSET,i+(SCROLLY-1-ALTURA_BLOC),Blocs[Mapa[((POSY<<2)+(POSY<<1)+(POSY<<0))+POSX]],AMPLADA_BLOC,ALTURA_BLOC,0,0,AMPLADA_PANTALLA-1,ALTURA_PANTALLA-1,SEGMENT);
    POSX++;
  }
   POSY++;
 }
}


