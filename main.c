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

	setUpPWM();

	while(1) {

		leftSignal = readADC(LEFT_IR);							// read analog pin 1.2
		centerSignal = readADC(CENTER_IR);						// read analog pin 1.3
		rightSignal = readADC(RIGHT_IR);						// read analog pin 1.4

		if (centerSignal > CENTER_WALL) {
			stopMoving();
			__delay_cycles(1000000);
			centerSignal = readADC(CENTER_IR);
			if (centerSignal > CENTER_WALL) {					//two values in a row
				P1OUT |= BIT0;									//turn on both leds
				P1OUT |= BIT6;
				if (leftSignal < rightSignal) {
					turnLeft(90, TURN_SPEED);
				} else {
					turnRight(90, TURN_SPEED);
				}
				stopMoving();
			}

		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
			moveForward(NORMAL_SPEED);
		}
	}
}

