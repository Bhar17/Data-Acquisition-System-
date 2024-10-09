#include <lpc21xx.h>
#include "header.h"

void spi0_init(void)
{
 PINSEL0|=0X1500;
 IODIR0|=CS0;
 IOSET0=CS0;	// 1
 S0SPCCR=15;
 S0SPCR=0X20;

}

unsigned char spi0(unsigned char data)
{
 S0SPDR=data;
 while(SPIF==0);
 return S0SPDR;

}
