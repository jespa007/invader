#include "invader.h"




dword exponent(dword numero, word elevat)
{
 int i;
 dword base = numero;

 for(i=0;i<elevat;i++)
 {
  numero*=base;
 }

 return (numero);

}


void pause(void)
{
 getch();
}


float rad(float radi)
{
 return radi*PI/180;
}




