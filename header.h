#include <lpc21xx.h>
/*header.h*/

#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)
#define CS0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)


/*Function prototype declarations*/

extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);
extern void lcd_data( unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *ptr);
extern void lcd_integer(int num);


extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern void uart0_tx_string(char *ptr);
extern void uart0_rx_string(signed char *ptr,signed int len);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float num);


extern unsigned short int adc_read(char ch_num);
extern void adc_init(void);

extern void spi0_init(void);
extern unsigned char spi0(unsigned char);
extern unsigned short int MPC3240_adc_read(unsigned char);

extern void i2c_init(void);
extern void i2c_byte_write_frame(unsigned char slvaddr, unsigned char mraddr, unsigned char data);
extern  unsigned char i2c_byte_read_frame(unsigned char slvaddr, unsigned char mraddr);

	
