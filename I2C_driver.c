#include <lpc21xx.h>
#include "header.h"
#define SI ((I2CONSET>>3)&1)

void i2c_init(void)
{
 PINSEL0|=0x50;
 I2SCLH=I2SCLL=75; // 100kbps(std speed mode)
 I2CONSET=(1<<6); // enable i2c peripheral select master mode
}

void i2c_byte_write_frame(unsigned char slvaddr, unsigned char mraddr, unsigned char data)
{

/*generate start condition*/

I2CONSET=(1<<5);  // STA=1
I2CONCLR=(1<<3);  // clear SI flag
while(SI==0);
I2CONCLR=(1<<5); //STA=0;

if(I2STAT!=0X8)
 {
 uart0_tx_string("err : start \r\n");
 goto exit;
 }
 // 2. send SA+w & check Ack

 I2DAT=slvaddr; // send SA+W
 I2CONCLR=(1<<3); //SI=0;
 while(SI==0);
 if(I2STAT==0x20)
 {
  uart0_tx_string("err : slvaddr \r\n");
  goto exit;
 }

 // 3. send m/r addr & check ack
 
 I2DAT=mraddr;	   // SEND M/R ADDR
 I2CONCLR=(1<<3);  // SI=0
  while(SI==0);
  if(I2STAT==0x30)
  {
	uart0_tx_string("err : m/raddr \r\n");
  	goto exit;
  }

// 4. send data & check ack

 I2DAT=data;	 // SEND DATA 
 I2CONCLR=(1<<3); // SI=0
   while(SI==0);
  if(I2STAT==0x30)
  {
   uart0_tx_string("err : DATA \r\n");
  	goto exit;
  }

// generate stop condition
	exit:
	I2CONSET=(1<<4); //ST0=1
	I2CONSET=(1<<3); //SI=0
}

 unsigned char i2c_byte_read_frame(unsigned char slvaddr, unsigned char mraddr)
 {
 unsigned char temp;
  /*generate start condition*/

I2CONSET=(1<<5);
I2CONCLR=(1<<3);
while(SI==0);
I2CONCLR=(1<<5); //STA=0;

if(I2STAT!=0X8)
 {
 uart0_tx_string("err : start \r\n");
 goto exit;
 }
 // 2. send SA+w & check Ack

 I2DAT=slvaddr; // send SA+W
 I2CONCLR=(1<<3);// SI=0;
 while(SI==0);
 if(I2STAT==0x20)
 {
  uart0_tx_string("err : slvaddr+w \r\n");
  goto exit;
 }

 // 3. send m/r addr & check ack
 
 I2DAT=mraddr;	   // SEND M/R ADDR
 I2CONCLR=(1<<3);  // SI=0
  while(SI==0);
  if(I2STAT==0x30)
  {
	uart0_tx_string("err : m/raddr \r\n");
  	goto exit;
  }

// 4. Generate restart condition
 I2CONSET=(1<<5);	
 I2CONCLR=(1<<3); // SI=0
   while(SI==0);
  I2CONCLR=(1<<5);
  if(I2STAT!=0x10)
  {
   uart0_tx_string("err : restart \r\n");
  	goto exit;
  }

// 5. START SA+R & check ack\

 I2DAT=slvaddr|1;
 I2CONCLR=(1<<3);
 while(SI==0);
 if(I2STAT==0x48)
 {
   uart0_tx_string("err : SA+R \r\n");
  	goto exit;
 }

//6. Data read and semd ACK

I2CONCLR=(1<<3); // si=0
while(SI==0);
temp=I2DAT;


// 7. generate stop condition
	exit:
	I2CONSET=(1<<4); //ST0=1
	I2CONSET=(1<<3); //SI=0

// 8. return received data

return temp;
}
 
