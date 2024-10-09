#include <lpc21xx.h>
#include "header.h"

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(unsigned int baud)
{
int a[]={15,60,30,15,15};
 unsigned int result=0;
 unsigned int pclk=a[VPBDIV]*1000000;
 result=pclk/(16*baud);	 //97.22
 PINSEL0|=0X5; //P0.1->TXD0, P0.1-> RXD0
 U0LCR=0X83;   // 8N1,DLAB=1
 U0DLL=result&0xFF;
 U0DLM=(result>>8)&0XFF;
 U0LCR=0X03;   // 8N1, DLAB=0

}

/////// Transmitting data  using uart0


void uart0_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}

/////// Receiving data  using uart0//////////////


unsigned char uart0_rx(void)											                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
                              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
{
while(RDR==0); // waiting for data
return U0RBR;
}

//////// Sending a string  using uart0///////////

void uart0_tx_string(char *ptr)
{
while(*ptr)
{
	U0THR=*ptr;
	while(THRE==0);
	ptr++;
	}
}

//////// Receiving a string   using uart0 ///////////

void uart0_rx_string(signed char *ptr,int len)
{
int i;
 for(i=0;i<len;i++)
 {
 	while(RDR==0);
	ptr[i]=U0RBR;
	//U0THR=ptr[i];
	if(ptr[i]=='\r') // if enter key pressed
	break;
}
ptr[i]='\0' ; // null
}				   

/////////// sending integer////////////

void uart0_tx_integer(int num)
{
int a[10],i=0;
if(num==0)
{
uart0_tx('0');
return;
}

if(num<0)
{
uart0_tx('-');
num=-num;
}

while(num)
{
a[i]=num%10;
i++;
num=num/10;
}
for(i--;i>=0;i--)
uart0_tx(a[i]+48);
}
//sprintf(a,"%d",num);//
//uart0_tx_string(a);
//}

void uart0_tx_float(float num)
{
int temp;
uart0_tx_integer((int)num);
uart0_tx('.');
temp=(num-(int)num)*100;
if(num<0)
temp=-temp;
uart0_tx_integer(temp);
//sprintf(a,"%f",num);
//uart0_tx_string(a);

}

