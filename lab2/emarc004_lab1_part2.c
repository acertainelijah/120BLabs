/*
 * emarc004_lab1_part1.c
 *
 * Created: 4/6/2019 9:07:55 AM
 * Author : elijah
 */ 

#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	while(1)
	{
		unsigned char cntAvail = 0x00;
		
		unsigned char space3 = PINA & 0x08;
		unsigned char space2 = PINA & 0x04;
		unsigned char space1 = PINA & 0x02;
		unsigned char space0 = PINA & 0x01;
		
		if(!(space3 == 0x08)) {
			cntAvail++;
		}
		if(!(space2 == 0x04)) {
			cntAvail++;
		}
		if(!(space1 == 0x02)) {
			cntAvail++;
		}
		if(!(space0 == 0x01)) {
			cntAvail++;
		}
		
		PORTC = cntAvail;
		
	}
	return 0;
}

