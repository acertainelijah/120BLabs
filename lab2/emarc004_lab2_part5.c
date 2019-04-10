/*
 * GccApplication1.c
 *
 * Created: 4/10/2019 9:46:33 AM
 * Author : ucrcse
 */ 

#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void) {
	
	DDRB = 0xFE; PORTB = 0x01; // Setting B0 to input. B7-B2 to output.
	DDRD = 0x00; PORTD = 0xFF; // Setting Port D to input.
	
	while(1) {
		unsigned long PB_zero = GetBit(PINB, 0);
		unsigned long weight = (PIND << 1) + PB_zero; //input PD7..PD0PB0 on the microcontroller
		
		if (weight >= 0x46) { //if weight is greater than 70lbs, set PB1 to 1
			PORTB = SetBit(PORTB, 1, 1); //Airbag Enabled
			PORTB = SetBit(PORTB, 2, 0); //turn off disabled
		}
		else if (weight >= 0x05) {
			PORTB = SetBit(PORTB, 2, 1); //Airbag Disabled
			PORTB = SetBit(PORTB, 1, 0); //turn off enabled
		}
		else{
			PORTB = 0x01;
		}
	}
	
}


