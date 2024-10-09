#include<lpc21xx.h>
#include"header.h"

int main()
{

unsigned short int extadc,adc;
float light, temper;
unsigned char hr,min,date,mon,year;
//unsigned char sec;
float vout;
int f;

lcd_init();
uart0_init(9600);
spi0_init();
adc_init();
i2c_init();

  
 // i2c write frame
 i2c_byte_write_frame(0xD0, 0x2, 0x63);
 i2c_byte_write_frame(0xD0, 0x1, 0x06);
 //i2c_byte_write_frame(0xD0, 0x0, 0x59);
 i2c_byte_write_frame(0xD0, 0x4, 0x07);
 i2c_byte_write_frame(0xD0, 0x5, 0x07);
 i2c_byte_write_frame(0xD0, 0x6, 0x24);
    

while(1)
{
  
// EXT ADC for light intensity

	extadc=MPC3240_adc_read(2);  
	light=((extadc*100)/4095);
	light=100-light;	  
	uart0_tx_string("Light : ");
	uart0_tx_integer(light);
	uart0_tx_string("% \r\n");		
	lcd_cmd(0x80);
	lcd_string("LIGHT:");
	lcd_integer(light);
	lcd_string("%  ");	
	


// ADC for Temperature
  
	adc=adc_read(1); 
	vout=(adc*3.3)/1023;
	temper=(vout-0.5)/0.01; 
	uart0_tx_string("Temperature : ");
	uart0_tx_integer(temper);
	uart0_tx_string("c \r\n");  
	lcd_cmd(0X8A);
	lcd_string("T:");
	lcd_integer(temper);
	lcd_string("c");
		
	
// RTC 
	
 hr=i2c_byte_read_frame(0xD0, 0x2);
 min=i2c_byte_read_frame(0xD0, 0x1);
// sec=i2c_byte_read_frame(0xD0, 0x0);
 date=i2c_byte_read_frame(0xD0, 0x4);
 mon=i2c_byte_read_frame(0xD0, 0x5);
 year=i2c_byte_read_frame(0xD0, 0x6);
	if((hr>>6)&1)
	hr=hr^(1<<6);

	if((hr>>5)&1)
	{
	 f=1;
	 hr=hr^(1<<5);
	}
	else
	f=0;
  
 lcd_cmd(0xC0);
 lcd_data((hr/0x10)+48);
 lcd_data((hr%0x10)+48);
 lcd_data(':');

 lcd_data((min/0x10)+48);
 lcd_data((min%0x10)+48);
 
 /*lcd_data(':');
  lcd_data((sec/0x10)+48);
 lcd_data((sec%0x10)+48);
   */

 if(f==1)
 lcd_string("AM");

 else
 lcd_string("PM");
   

 lcd_data(' ');
 lcd_data((date/0x10)+48);
 lcd_data((date%0x10)+48);
 lcd_data('/');\

 lcd_data((mon/0x10)+48);
 lcd_data((mon%0x10)+48);
 lcd_data('/');
   	  
 lcd_data((year/0x10)+48);
 lcd_data((year%0x10)+48);
 
 
 }
}
