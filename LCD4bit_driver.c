#include <lpc21xx.h>
#include "header.h"


void lcd_data(unsigned char data)
{
 unsigned int temp;
 // for highernibble

 IOCLR1=0X00FE0000;
 temp=(data&0xF0)<<16;
 IOSET1=temp;

 IOSET1=RS;
 IOCLR1=RW;
 IOSET1=EN;

 delay_ms(10);
 IOCLR1=EN;

 // LOWER NIBBLE
 
 IOCLR1=0X00FE0000;
 temp=(data&0x0F)<<20;
 IOSET1=temp;

 IOSET1=RS;
 IOCLR1=RW;
 IOSET1=EN;

 delay_ms(10);
 IOCLR1=EN;
}


void lcd_cmd(unsigned char cmd)
{
 unsigned int temp;
 // for highernibble

 IOCLR1=0X00FE0000;
 temp=(cmd&0xF0)<<16;
 IOSET1=temp;

 IOCLR1=RS;
 IOCLR1=RW;
 IOSET1=EN;

 delay_ms(10);
 IOCLR1=EN;

 // LOWER NIBBLE
 
 IOCLR1=0X00FE0000;
 temp=(cmd&0x0F)<<20;
 IOSET1=temp;

 IOCLR1=RS;
 IOCLR1=RW;
 IOSET1=EN;

 delay_ms(10);
 IOCLR1=EN;
}

void lcd_init()
{
 IODIR1=0X00FE0000;
 PINSEL2|=0X0;
 IOCLR1=1<<19;
 lcd_cmd(0x02);
 lcd_cmd(0x0e);
 lcd_cmd(0x28);
}


void lcd_string(char *ptr)
{
 while(*ptr!=0)
 {
 	lcd_data(*ptr);
	ptr++;
 }
}

void lcd_integer(int num)
{
 int i;
 int a[10];
  if(num<0)
 {
  lcd_data('-');
  num=-num;
 }

 if(num==0)
 {
 lcd_data('0');
 return;
 }

 for(i=0;num;num=num/10,i++)
  a[i]=num%10+48;
 for(--i;i>=0;i--)
 lcd_data(a[i]);
 
}
