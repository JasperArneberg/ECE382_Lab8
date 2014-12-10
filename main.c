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
		/*
		if (leftSignal > LEFT_WALL) {
			P1OUT |= BIT0;										// turn on red led
			P1OUT &= ~BIT6;
			turnRight(1, TURN_SPEED);							// turn 5 degrees right
			while(leftSignal > LEFT_WALL - 20) {
				leftSignal = readADC(LEFT_IR);
			}
		}
		else if (rightSignal > RIGHT_WALL) {
			P1OUT &= ~BIT0;
			P1OUT |= BIT6;										// turn on green led
			turnLeft(1, TURN_SPEED);							// turn 5 degrees left
			while(leftSignal > LEFT_WALL - 20) {
				leftSignal = readADC(LEFT_IR);
			}
		}
		else*/ if (centerSignal > CENTER_WALL) {
			P1OUT |= BIT0;										//turn on both leds
			P1OUT |= BIT6;
			moveBack(NORMAL_SPEED);
			__delay_cycles(5000000);
			turnLeft(90, TURN_SPEED);
			stopMoving();
			__delay_cycles(10000000);
		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
			moveForward(NORMAL_SPEED);
		}
	}
}

