/*	Name & E-mail: Elijah Marchese  emarc004@ucr.edu
 *	Lab Section: 026
 *	Assignment: Lab #2  Exercise #1 
 *	Exercise Description: 
 *    Count the number of 1s on ports A and B and output that number on port C.	
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	while(1)
	{
		unsigned char count = 0x00;
		// Find 1's in PINA
		for (int i = 0; i < 8; i++){
			unsigned char tempSpace = GetBit(PINA, i);
			if(tempSpace != 0x00) {
				count++;
			}
		}
		// Find 1's in PINB
		for (int i = 0; i < 8; i++){
			unsigned char tempSpace = GetBit(PINB, i);
			if(tempSpace != 0x00) {
				count++;
			}
		}
		PORTC = count;
		
	}
}


