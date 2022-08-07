#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU     8000000L
#include <util/delay.h>

//            0  1  2  3  4  5  6  7  8  9  -
//PD6 - (g)   0  0  1  1  1  1  1  0  1  1  0
//PD5 - (f)   1  0  0  0  1  1  1  1  1  1  0
//PD4 - (e)   1  0  1  0  0  0  1  0  1  0  0
//PD3 - (d)   1  0  1  1  0  1  1  0  1  1  0
//PD2 - (c)   1  1  0  1  1  1  1  1  1  1  0
//PD1 - (b )  1  1  1  1  1  0  0  1  1  1  0
//PD0 - (a)   1  0  1  1  0  1  1  1  1  1  0
//           3f 06 5b 4f 66 6d 7d 27 ff 6f 00

uint8_t num[] =
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0xff, 0x6f, 0
};

volatile uint8_t dg_val[5]={0,0,0,0,0};
volatile uint8_t bcnt = 0;
uint8_t dat;

int main(void)
{
	uint8_t dgcnt = 0;

	DDRB = 0x1f;
	DDRD = 0x7f;
	
	//USIOIE: counter overflow interrupt enable
	//USIWM1,0=01: Three wire mode
	//USICS1,0,USICLK=100: clock source select, External positive edge
	USICR = (1<<USIOIE)|(1<<USIWM0)|(1<<USICS1);
	sei();
	
	while (1)
	{
		if(dgcnt == 1)
			PORTB = 0x10 + (1<<dgcnt);
		else
			PORTB = 1<<dgcnt;
		PORTD = num[dg_val[dgcnt]];
		
		dgcnt++;
		if(dgcnt == 4)
			dgcnt = 0;
		_delay_ms(2);
	}
}

ISR (USI_OVERFLOW_vect)
{
	USISR |= (1<<USIOIF);

	dat = USIDR;
	if(dat == 0xff)
		bcnt = 0;
	else{
		dg_val[bcnt] = dat;
		bcnt++;
	}
}