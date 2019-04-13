/*
 * GccApplication1.c
 *
 * Created: 4/12/2019 5:18:57 PM
 * Author : Elijah Marchese
 */ 

#include <avr/io.h>

enum States{INIT, WAIT, POUND, WAIT_POUND, Y_STATE, TOGGLE, LOCK} state;

unsigned char latch = 0x00;

void Tick() {
	/*
	unsigned char aX		= PINA & 0x01; //'X' input
	unsigned char aY		= PINA & 0x02; //'Y' input
	unsigned char aPound	= PINA & 0x04; //'#' input
	
	unsigned char a7		= PINA & 0x80; //Locking number
	*/
	
	unsigned char sigBits = PINA & 0x87; // Gets X Y # and locking bit
	
	//State Transitions
	switch(state) {
		case INIT:
			state = WAIT;
			break;
			
		case WAIT:
			if (sigBits == 0x04) {	//!aX && !aY && aPound && !a7
				state = POUND;
			} else if(sigBits == 0x80) {	//!aX && !aY && !aPound && a7
				state = LOCK;
			} else {
				state = WAIT;
			}
			break;
			
		case POUND:
			if(sigBits == 0x04) {	//!aX && !aY && aPound && !a7
				state = POUND;
			} else if(sigBits == 0x00) {	//!aX && !aY && !aPound && !a7
				state = WAIT_POUND;
			} else {
				state = WAIT;
			}
			break;
			
		case WAIT_POUND:
			if(sigBits == 0x00) {	//!aX && !aY && !aPound && !a7
				state = WAIT_POUND;
			} else if(sigBits == 0x02) { //!aX && aY && !aPound && !a7
				state = Y_STATE;
			} else if(sigBits == 0x80) {	//!aX && !aY && !aPound && a7
				state = LOCK;
			} else {
				state = WAIT;
			}
			break;
			
		case Y_STATE:		
			if(sigBits == 0x02) {	//!aX && aY && !aPound && !a7
				state = Y_STATE; 
			} else if(sigBits == 0x00) {	//!aX && !aY && !aPound && !a7
				state = TOGGLE;
			} else {
				state = WAIT;
			}
			break;
			
		case TOGGLE:
			state = WAIT;
			break;
			
		case LOCK:
			if(sigBits == 0x80) {	//!aX && !aY && !aPound && a7
				state = LOCK;
			} else if(sigBits == 0x00) {	//!aX && !aY && !aPound && !a7
				state = WAIT;
			} else {
				state = WAIT;
			}
			break;
			
		default:
			state = INIT;
	}
	
	//State Actions
	switch(state) {
		case INIT:
			break;
			
		case WAIT:
			break;
			
		case POUND:
			break;
			
		case WAIT_POUND:
			break;
			
		case Y_STATE:
			break;
			
		case TOGGLE:
			latch = (~latch) & 0x01;
			PORTB = latch;
			break;
			
		case LOCK:
			PORTB = 0x00;
			break;
	}
}

int main(void)
{
    DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
    while (1) 
    {
		Tick();
    }
	
	return 0;
}
