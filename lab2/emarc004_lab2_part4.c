/*
 * GccApplication1.c
 *
 * Created: 4/10/2019 9:46:33 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>


int main(void) {
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	
	while(1) {
		tmpA = PINA;
		
		tmpB = tmpA >> 4; //Takes PINA7-4 [Upper Nibble] and maps it newB3-0 [Lower Nibble]
		
		tmpC = tmpA << 4; //Takes PINA3-0 [Lower Nibble] and maps it newC7-4 [Upper Nibble]
		
		PORTB = tmpB;
		PORTC = tmpC;
	}
	
	return 0;
}

