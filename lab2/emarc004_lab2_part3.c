/*	Name & E-mail: Elijah Marchese  emarc004@ucr.edu
 *	Lab Section: 026
 *	Assignment: Lab #2  Exercise #1 
 *	Exercise Description: 
 *    A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). 
 *	  A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. 
 *	  If the fuel level is 1 or 2, PC5 lights. 
 *	  If the level is 3 or 4, PC5 and PC4 light. 
 *	  Level 5-6 lights PC5..PC3. 
 *	  7-9 lights PC5..PC2. 
 *	  10-12 lights PC5..PC1. 
 *	  13-15 lights PC5..PC0. 
 *	  Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	while(1)
	{
		unsigned char gasLvl = 0x00;
		// Find 1's in PINA
		for (int i = 0; i < 4; i++){
			unsigned char tempSpace = GetBit(PINA, i);
			if(tempSpace != 0x00) {
				gasLvl = SetBit(gasLvl, i, 1);
			}
		}
		
		PORTC = 0x00;
		
		//Low Fuel Light
		if (gasLvl <= 0x04) { //gasLvl <= 4, put on Low Fuel light
			PORTC = SetBit(PORTC, 6, 1);
		}
		
		//Gas Level Gauge
		if (gasLvl >= 0x01) { //gasLvl = 1..2
			PORTC = SetBit(PORTC, 5, 1);	
		}
		if (gasLvl >= 0x03) { //3..4
			PORTC = SetBit(PORTC, 4, 1);	
		}
		if (gasLvl >= 0x05) { //5..6
			PORTC = SetBit(PORTC, 3, 1);	
		}
		if (gasLvl >= 0x07) { //7..9
			PORTC = SetBit(PORTC, 2, 1);	
		}
		if (gasLvl >= 0x0A) { //10..12
			PORTC = SetBit(PORTC, 1, 1);	
		}
		if (gasLvl >= 0x0D && gasLvl <= 0x0F) { //13..15
			PORTC = SetBit(PORTC, 0, 1);	
		}
		
		
		//Fasten Seatbelt Light
		unsigned char keyIn = GetBit(PINA, 4);
		unsigned char driverIn = GetBit(PINA, 5);
		unsigned char seatbeltIn = GetBit(PINA, 6);
		if((keyIn != 0x00) && (driverIn != 0x00) && (seatbeltIn == 0x00)) { //if keyIn, driverIn, NOT seatbeltIn: light up portC[7] 
			PORTC = SetBit(PORTC, 7, 1);
		}
		
	}
}


