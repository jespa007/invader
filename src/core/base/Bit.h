#pragma once


//  Operacions  de  bit.
#define  TST_BIT(x,  b)  ((((x))    &  (0x1  <<  (b)))   !=0							)
#define  SET_BIT(x,  b)  ( ((x))    =  (unsigned(x))    |      (0x1        <<  (b))   )
#define  CLR_BIT(x,  b)  ((((x))    =  (unsigned(x))    &      (~    (0x1  <<  (b)))) )
#define  XOR_BIT(x,  b)  (  (x)     =  (unsigned(x)     ^      (0x1        <<  (b)))  )


#define  TST_MSK(x,  msk)  ((((x))    &  ((msk)))   		 !=		  0	 )
#define  SET_MSK(x,  msk)  ( ((x))    =  (unsigned(x))    |      (msk) )
#define  CLR_MSK(x,  msk)  ((((x))    =  (unsigned(x))    &     ~(msk)))
#define  XOR_MSK(x,  msk)  (  (x)     =  (unsigned(x)     ^      (msk)))

class Bit{

public:
	static inline unsigned int nextPow2(unsigned int v)
	{
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;
		return v;

	}
};
