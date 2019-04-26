/*
 * GccApplication1.c
 *
 * Created: 4/12/2019 5:18:57 PM
 * Author : ucrcse
 */ 

#include <avr/io.h>

enum States{START, WAIT, INC, DEC, RESET} state;

unsigned char value = 0x00;

void Tick() {
	unsigned char buttons = PINA & 0x03; //Gets bits 0-1s
	
	switch(state) { //Transitions
		case START:
		state = WAIT;
		value = 0x07;
		break;
		
		case WAIT:
		if(buttons == 0x01) { //A0 && !A1
			state = INC;
		} 
		else if (buttons == 0x02) { //!A0 && A1
			state = DEC;
		} 
		else if (buttons == 0x00) { //!A0 && !A1
			state = WAIT;
		} 
		else if (buttons == 0x03) { //A0 && A1 if both A0 and A1 are pressed
			state = RESET;
		}
		break;
		
		case INC:
		if(buttons == 0x01) { //A0 && !A1
			state = INC;
		} 
		else if(buttons == 0x03) { //A0 && A1
			state = RESET;
		} 
		else if(buttons == 0x00) { //!A0 && !A1
			state = WAIT;
			if(value < 9) {
				value = value + 1;
				PORTC = value;
			}
		} 
		else if(buttons == 0x02) { //!A0 && A1
			state = WAIT;
		}
		break;
		
		case DEC:
		if(buttons == 0x02) { //!A0 && A1
			state = DEC;
		} 
		else if(buttons == 0x03) { //A0 && A1
			state = RESET;
		} 
		else if (buttons == 0x00) { //!A0 && !A1
			state = WAIT;
			if(value > 0) {
				value = value - 1;
				PORTC = value;
			}
		} 
		else if (buttons == 0x01) { //A0 && !A1
			state = WAIT;
		}
		break;
		
		case RESET:
		state = WAIT;
		break;
		
		default:
		state = START;
		break;
	}
	
	switch(state) { //State Actions
		case START:
		break;
		case WAIT:
		break;
		case INC:
		break;
		case DEC:
		break;
		case RESET:
		value = 0x00;
		PORTC = value;
		break;
		
		default:
		break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
	
	state = START;
	
	while(1) {
		Tick();
	}
}
