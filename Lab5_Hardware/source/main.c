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

int main(void) {
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char LED = 0x00;
    while (1) {
	tmpA = PINA;
	if(tmpA >= 0x01){
		LED = 0x20;
	}
	if(tmpA >= 0x03){
		LED = 0x30;
	}
	if(tmpA >= 0x05){
		LED = 0x38;
	}
	if(tmpA >= 0x07){
		LED = 0x3C;
	}
	if(tmpA >= 0x0A){
		LED = 0x3E;
	}
	if(tmpA >= 0x0D){
		LED = 0x3F;
	}
	if(tmpA <= 0x04){
		LED = LED | 0x40;
	} 
	PORTC = LED;
	tmpA = 0;
	LED = 0;
}
    return 1;
}
