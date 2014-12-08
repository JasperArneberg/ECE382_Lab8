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

	//Set up PWM pins for robot motion
    P2DIR |= BIT1;							// P2.1 is left reverse selector
    P2OUT &= ~BIT1;							// initialize output to 0, forward drive

    P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
    P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

    P2DIR |= BIT3;							// P2.3 is right reverse selector
    P2OUT &= ~BIT3;							// initialize to 0, forward drive

    P2DIR |= BIT4;							// P2.4 is associated with TA1CCR2
    P2SEL |= BIT4;							// P2.4 is associated with TA1CCTL2

	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
    TA1CCR0 = PERIOD;						// set signal period for PWM

	while(1) {

		leftSignal = readADC(LEFT_IR);									// read analog pin 2
		centerSignal = readADC(CENTER_IR);
		rightSignal = readADC(RIGHT_IR);									// read analog pin 4

		if (leftSignal > LEFT_WALL) {
			P1OUT |= BIT0;										// turn on red led
			P1OUT &= ~BIT6;
			stopMoving();
		} else if (centerSignal > CENTER_WALL) {
			P1OUT |= BIT0;
			P1OUT |= BIT6;
			stopMoving();
		} else if (rightSignal > RIGHT_WALL) {
			P1OUT &= ~BIT0;
			P1OUT |= BIT6;										// turn on green led
			stopMoving();
		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
			moveForward(MAX_SPEED);
		}
	}
}

