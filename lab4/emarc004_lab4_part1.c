/*
 * GccApplication1.c
 *
 * Created: 4/12/2019 12:13:18 PM
 * Author : Elijah Marchese
 * Lab Section: 026
 * Assignment: Lab #  Exercise #
 */ 

#include <avr/io.h>


// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

enum LED_States { init, start, PB1_ON, PB0_ON } LED_State;

void LEDLit(unsigned char A0)
{
	switch(LED_State) {   // Transitions
		case init: // Initial transition
		LED_State = start;
		break;
		
		case start:  
		if (!A0) {
			LED_State = start;
		}
		else if (A0) {
			LED_State = PB1_ON;		
		}
		break;

		case PB1_ON:
		if (!A0) {
			LED_State = PB1_ON;
		}
		else if (A0) {
			LED_State = PB0_ON;
		}
		break;

		case PB0_ON:
		if (!A0) {
			LED_State = PB0_ON;
		}
		else if (A0) {
			LED_State = PB1_ON;
		}
		break;

		default:
		LED_State = start;
		break;
	} // Transitions

	switch(LED_State) {   // State actions
		case PB1_ON:
		PORTB = SetBit(PORTB, 0, 0);
		PORTB = SetBit(PORTB, 1, 1);
		break;

		case PB0_ON:
		PORTB = SetBit(PORTB, 0, 1);
		PORTB = SetBit(PORTB, 1, 0);
		break;

		default:
		PORTB = SetBit(PORTB, 0, 0);
		PORTB = SetBit(PORTB, 1, 0);
		break;
	} // State actions
	
	while(A0){A0 = GetBit(PINA, 0);} //Wait until A0 is depressed
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char A0 = GetBit(PINA, 0);
	LED_State = init; // Indicates initial call

	while(1) {
		A0 = GetBit(PINA, 0);
		LEDLit(A0);
	}
	return 0;
}
