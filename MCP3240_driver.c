#include <lpc21xx.h>
#include "header.h"

unsigned short int MPC3240_adc_read(unsigned char ch_num)
{
 unsigned char hbyte, lbyte;
 unsigned short int result=0;
 ch_num<<=6;

 IOCLR0=CS0; //0

 spi0(0x06);
 hbyte=spi0(ch_num);
 lbyte=spi0(0x00);

 IOSET0=CS0; //1

 	hbyte&=0x0f;  /////masking the msb 4 bits////
	result= (hbyte<<8)|lbyte;

 return result;

}
