ECE382_Lab8
===========

Lab 8: Robot Maze

C2C Jasper Arneberg  
T5 ECE 382  
Capt Trimble  

##Introduction
This lab requires combining the functionalites developed in Lab 6 and Lab 7. 

##Prelab
The strategy to complete this lab changes as the level of functionality increases. In order to get required functionality, only one left turn is required. To get B functionality, one left and one right turn is required. To get A functionality, however, the game changes. A minimum of four 90-degree turns are required, posing a problem. It is very hard to determine when to turn right versus left. For this functionality, perhaps a right edge-following strategy would work the best.

####Pseudocode for Required Functionality
```
infinite loop:
leftSignal = readADC(2);
centerSignal = readADC(3);
rightSignal = readADC(4);

if(centerWall == false) moveForward;
if (centerWall) {
  if (leftSignal > rightSignal) {
    turnRight90;
  }
  else {
    turnLeft90;
  }
}
```

####Schematic
![alt text](https://github.com/JasperArneberg/ECE382_Lab8/blob/master/schematic.png?raw=true "Schematic")

##Required Functionality
In order to obtain required functionality, the robot was programmed to drive forward until it hit a wall. Then it would turn 90 degrees to the left using the turnLeft(degrees, speed) command. Below is the primary loop:
```
	while(1) {
		leftSignal = readADC(LEFT_IR);							// read analog pin 1.2
		centerSignal = readADC(CENTER_IR);						// read analog pin 1.3
		rightSignal = readADC(RIGHT_IR);						// read analog pin 1.4
		
		if (centerSignal > CENTER_WALL) {
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
```

The most difficult pult was calibrating the turnLeft() method so that it actually turned the robot 90 degrees. As the robot's batteries drained, the voltage decreased. This changed the amount of time that was needed for the turn to accomplish appropriately.

Once the center sensor detected a wall, the robot moved backwards. This was to prevent it from smashing into the wall as the momentum would carry the robot forward otherwise. 

The <adc10.h> library was used frequently for this lab whenever the readADC() command was called. This library was created as part of Lesson 7, and it helped to greatly simplify the code.

##B Functionality
From the required functionality to the B functionality, a few minor changes were made. Here is the primary loop for B functionality:
```
while(1) {

		leftSignal = readADC(LEFT_IR);							// read analog pin 1.2
		centerSignal = readADC(CENTER_IR);						// read analog pin 1.3
		rightSignal = readADC(RIGHT_IR);						// read analog pin 1.4

		if (centerSignal > CENTER_WALL) {
			P1OUT |= BIT0;										//turn on both leds
			P1OUT |= BIT6;
			moveBack(NORMAL_SPEED);
			__delay_cycles(5000000);
			if (firstTurn == TRUE) {
				turnLeft(90, TURN_SPEED);
				firstTurn = FALSE;
			} else {
				turnRight(90, TURN_SPEED);
			}
			stopMoving();
			__delay_cycles(10000000);
		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
			moveForward(NORMAL_SPEED);
		}
```
The parameter firstTurn was used to determine whether or not to turn right or left. The B functionality only required two turns: a left turn and then a right turn. This parameter implemented this functionality very efficiently.

##A Functionality
One simple change was made for completed A functionality. Again, this took under 5 minutes to complete after B functionality was demonstrated. Instead of pre-determining the direction that the robot would turn, the robot used the left and right sensors to determine which way to turn. Here's the code:
```
	while(1) {

		leftSignal = readADC(LEFT_IR);							// read analog pin 1.2
		centerSignal = readADC(CENTER_IR);						// read analog pin 1.3
		rightSignal = readADC(RIGHT_IR);						// read analog pin 1.4

		if (centerSignal > CENTER_WALL) {
			P1OUT |= BIT0;										//turn on both leds
			P1OUT |= BIT6;
			moveBack(NORMAL_SPEED);
			__delay_cycles(2000000);
			if (leftSignal < rightSignal + LR_DIFF) {
				turnLeft(90, TURN_SPEED);
			} else {
				turnRight(90, TURN_SPEED);
			}
			stopMoving();
			__delay_cycles(5000000);
		} else {
			P1OUT &= ~BIT0;										// turn off both leds
			P1OUT &= ~BIT6;
			moveForward(NORMAL_SPEED);
		}
	}
```

The most difficult part about A functionality is that the robot was not allowed to touch any of the walls. If the robot starting veering off to one side, it would fail to complete the task.

##Bonus Functionality
The robot was able to traverse the maze backwards using the code developed for A funtionality. This was worth of bonus functionality.

##Debugging
When the moveForward() command was called, the robot veered off the left. Here was the original code:
```
void moveForward(int speed) {
	P2OUT &= ~BIT1;							//clear left reverse select
	TA1CCTL1 = OUTMOD_7;					//Reset/Set mode
	TA1CCR1 = speed;

	P2OUT &= ~BIT3;							//clear right reverse select
	TA1CCTL2 = OUTMOD_7;					//Reset/Set mode
	TA1CCR2 = speed;
}
```

This method was changed to allow for variation is natural wheel speeds:
```
void moveForward(int speed) {
	P2OUT &= ~BIT1;							//clear left reverse select
	TA1CCTL1 = OUTMOD_7;					//Reset/Set mode
	TA1CCR1 = speed + LEFT_CAL;

	P2OUT &= ~BIT3;							//clear right reverse select
	TA1CCTL2 = OUTMOD_7;					//Reset/Set mode
	TA1CCR2 = speed + RIGHT_CAL;
}
```

The LEFT_CAL and RIGHT_CAL allowed the motor speeds to be tweaked individually. After some brief testing, the right calibration was set to -5 and the left calibration was left at 0. The robot drove straight ahead as desired.

##Conclusion

##Documentation
I used http://www.tablesgenerator.com/markdown_tables to generate markdown tables efficiently.  

