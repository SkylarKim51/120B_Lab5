/*	Author: skim370
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {init, start, oneAdd, pressAdd, releaseAdd, oneMinus, pressMinus, releaseMinus, pressReset, releaseReset} state;
unsigned char tempA;
unsigned char count;

void stateMachine(){
	switch(state) {
		case init:
			state = start;
			break;

		case start:
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			if(tempA == 0x00){
				state = start;
			}
			break;

		case oneAdd:
			state = pressAdd;
			break;

		case pressAdd:
			if(tempA == 0x01){
				state = pressAdd;
			}
			if(tempA == 0x00){
				state = releaseAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			break;

		case releaseAdd:
			if(tempA == 0x00){
				state = releaseAdd;
			}		
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			break;
		
		case oneMinus:
			state = pressMinus;
			break;
		
		case pressMinus:
			if(tempA == 0x02){
				state = pressMinus;
			}
			if(tempA == 0x00){
				state = releaseMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			break;

		case releaseMinus:
			if(tempA == 0x00){
				state = releaseMinus;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			break;
		
		case pressReset:
			if(tempA == 0x03 || tempA == 0x01 || tempA == 0x02){
				state = pressReset;
			}
			if(tempA == 0x00){
				state = releaseReset;
			}
			break;
		
		case releaseReset:
			if(tempA == 0x00){
				state = releaseReset;
			}
			if(tempA == 0x01){
				state = oneAdd;
			}
			if(tempA == 0x02){
				state = oneMinus;
			}
			if(tempA == 0x03){
				state = pressReset;
			}
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case init:
			break;
		
		case start:
			count = 0x07;
			break;	

		case oneAdd:
			if(count >=  9){
				count = count;
			}
			else{
				count = count + 1;
			}
			break;
	
		case pressAdd:
			break;

		case releaseAdd:
			break;
		
		case oneMinus:
			if(count <= 0){
				count = count;
			}
			else{
				count = count - 1;
			}
			break;
		
		case pressMinus:
			break;

		case releaseMinus:
			break;

		case pressReset:
			count = 0;
			break;

		case releaseReset:
			break;

		default:
			count = 0x07;
			break;
	}
}		

int main() { 
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	state = init;
    while (1) {
	tempA = PINA;
	stateMachine();
	PORTC = count;	
    }
	
    return 1;
}
