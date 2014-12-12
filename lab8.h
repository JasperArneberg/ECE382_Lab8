/*
 * lab8.h
 *
 *  Created on: Dec 8, 2014
 *      Author: C16Jasper.Arneberg
 */

#ifndef 	LAB8_H_
#define 	LAB8_H_

#define 	LEFT_WALL 		0x280
#define		CENTER_WALL 	0x290			//needs to be higher for center sensor, was 300
#define 	RIGHT_WALL 		0x280

#define 	LEFT_IR 		2
#define 	CENTER_IR 		3
#define 	RIGHT_IR 		4
#define		LR_DIFF			0x80

#define 	LEFT_CAL		0				//used so robot drives straight forward
#define		RIGHT_CAL		-5

#define		TRUE 			1
#define		FALSE			0

#define 	PERIOD 			100
#define 	TURN_SPEED 		60
#define 	MAX_SPEED 		90
#define		NORMAL_SPEED	60
/*
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);
*/

void setUpPWM() {
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
}

void stopMoving() {
	P2OUT &= ~BIT1;							//clear left reverse select
	TA1CCTL1 = OUTMOD_7;					//Reset/Set mode
	TA1CCR1 = 0;

	P2OUT &= ~BIT3;							//clear right reverse select
	TA1CCTL2 = OUTMOD_7;					//Reset/Set mode
	TA1CCR2 = 0;
}

void moveForward(int speed) {
	P2OUT &= ~BIT1;							//clear left reverse select
	TA1CCTL1 = OUTMOD_7;					//Reset/Set mode
	TA1CCR1 = speed + LEFT_CAL;

	P2OUT &= ~BIT3;							//clear right reverse select
	TA1CCTL2 = OUTMOD_7;					//Reset/Set mode
	TA1CCR2 = speed + RIGHT_CAL;
}

void moveBack(int speed) {
	P2OUT |= BIT1;							//set left reverse select
	TA1CCTL1 = OUTMOD_3;					//Set/Reset mode
	TA1CCR1 = speed;

	P2OUT |= BIT3;							//set right reverse select
	TA1CCTL2 = OUTMOD_3;					//Set/Reset mode
	TA1CCR2 = speed;
}

/**
 * The turnLeft() method takes in two parameters, degrees and speed.
 * This allows it to be used in a variety of applications. The degrees
 * functionality is calibrated for a speed of 60.
 */
void turnLeft(int degrees, int speed) {
	P2OUT |= BIT1;							//set left reverse select
	TA1CCTL1 = OUTMOD_3;					//Set/Reset mode
	TA1CCR1 = speed;

	P2OUT &= ~BIT3;							//clear right reverse select
	TA1CCTL2 = OUTMOD_7;					//Reset/Set mode
	TA1CCR2 = speed;

	__delay_cycles(200000);					//motor start-up delay
	int i = 0;
	for (i=0; i<degrees; i++) {
		__delay_cycles(32000);				//3300 cycles per degree when speed = 60
	}
}

/**
 * The turnRight() method is calibrated for a speed of 60. A different
 * speed may be specified in order to turn the robot slower.
 */
void turnRight(int degrees, int speed) {
	P2OUT &= ~BIT1;							//clear left reverse select
	TA1CCTL1 = OUTMOD_7;					//Reset/Set mode
	TA1CCR1 = speed;

	P2OUT |= BIT3;							//set right reverse select
	TA1CCTL2 = OUTMOD_3;					//Set/Reset mode
	TA1CCR2 = speed;

	__delay_cycles(200000);					//motor start-up delay
	int i = 0;
	for (i=0; i<degrees; i++) {
		__delay_cycles(32000);				//3300 cycles per degree when speed = 60
	}
}

#endif /* LAB8_H_ */
