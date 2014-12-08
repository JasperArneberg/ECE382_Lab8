#include "adc10.h"
#include "msp430g2553.h"
#include "lab8.h"

/*
 * main.c
 */

void main() {
	int leftSignal;
	int centerSignal;
	int rightSignal;

	void initMSP430();
	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT
	P1DIR |= BIT0 | BIT6;										// set leds to output

	while(1) {

		leftSignal = readADC(LEFT_IR);									// read analog pin 2
		centerSignal = readADC(CENTER_IR);
		rightSignal = readADC(RIGHT_IR);									// read analog pin 4

		if (leftSignal > LEFT_WALL) {
			P1OUT |= BIT0;										// turn on red led
			P1OUT &= ~BIT6;
		} else if (centerSignal > CENTER_WALL) {
			P1OUT |= BIT0;
			P1OUT |= BIT6;
		} else if (rightSignal > RIGHT_WALL) {
			P1OUT &= ~BIT0;
			P1OUT |= BIT6;										// turn on green led
		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
		}
	}
}

