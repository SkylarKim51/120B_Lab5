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

enum States{init, start, configOne, releaseOne, configTwo, releaseTwo, configThree, releaseThree, configFour, releaseFour, reset} state;

unsigned char A0;
unsigned char LED;

void stateMachine(){
	switch(state){
		
		case init:
			state = start;
			break;
		
		case start:
			LED = 0x00;
			if(A0 == 1){
				state = configOne;
			}
			else{
				state = start;
			}
			break;
	
		case configOne:
			LED = 0x21;
			if(A0 == 1){
				state = configOne;
			}
			else if(A0 == 0){
				state = releaseOne;
			}
			break;

		case releaseOne:
			if(A0 == 1){
				state = configTwo;
			}
			else if(A0 == 0){
				state = releaseOne;
			}
			break;

		case configTwo:
			LED = 0x12;
			if(A0 == 1){
				state = configTwo;
			}
			else if(A0 == 0){
				state = releaseTwo;
			}
			break;
		
		case releaseTwo:
			if(A0 == 0){
				state = releaseTwo;
			}
			else if(A0 == 1){
				state = configThree;
			}	
			break;
		
		case configThree:
			LED = 0x0C;
			if(A0 == 1){
				state = configThree;
			}
			else if(A0 == 0){
				state = releaseThree;
			}
			break;

		case releaseThree:
			if(A0 == 0){
				state = releaseThree;
			}
			else if(A0 == 1){
				state = configFour;
			}
			break;
		
		case configFour:
			LED = 0x3F;
			if(A0 == 1){
				state = configFour;
			}
			else if(A0 == 0){
				state = releaseFour;
			}
			break;

		case releaseFour:
			if(A0 == 0){
				state = releaseFour;
			}
			else if(A0 == 0x01){
				state = reset;
			}
			break;
		case reset:
			LED = 0x00;
			if(A0 == 0x01){
				state = reset;
			}
			else if(A0 == 0x00){
				state = start;
			}
			break;

		default:
			LED = 0x00;
			state = start;
			break;
	}

	switch(state){
		case init:
			break;
		
		case start:
			break;
	
		case configOne:
			break;

		case releaseOne:
			break;

		case configTwo:
			break;
		
		case releaseTwo:
			break;
		
		case configThree:
			break;

		case releaseThree:
			break;
		
		case configFour:
			break;

		case releaseFour:
			break;
		
		default:
			break;	
	}
}

int main(){
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	state = init;
    while (1) {
	A0  = PINA & 0x01;
	stateMachine();
	PORTC = LED;	
    }
	
    return 1;
}
