#include <lpc21xx.h>
#include "header.h"

void adc_init(void)
{
PINSEL1|= 0x15400000;// P0.27 - P0.30 Pins are AIN0-3
ADCR=0x00200400;	  // ADC control regester no ch selected, ADC clock is 3MHz burst off, 10bit resolution,ADC op, ADC stop.
}

unsigned short int adc_read(char ch_num)
{

unsigned short int result=0;
ADCR|=(1<<ch_num);	// select channel number

ADCR|=(1<<24);	   // select ADC conv

while(((ADDR>>31)&1)==0); // wait for done flag to be set

ADCR^=(1<<24);	   // stop ADC conv

ADCR^=(1<<ch_num); // deselect ch num

result=(ADDR>>6)&0x3ff;	// extract 10bis digi res

return result;	   // return result

}
