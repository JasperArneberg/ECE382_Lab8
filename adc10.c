/*
 * adc10.c
 *
 *  Created on: Dec 4, 2014
 *      Author: C16Jasper.Arneberg
 */

#include "adc10.h"
#include "msp430g2553.h"

int readADC(int pin) {

	BCSCTL1 = CALBC1_8MHZ;									// 8MHz clock
	DCOCTL = CALDCO_8MHZ;
	ADC10CTL0 = 0;											// Turn off ADC subsystem

	//Select input channel bsa
	if (pin == 0) {
		ADC10CTL1 = INCH_0;									// Channel 0
		ADC10AE0 = BIT0;									// Make P1.0 analog input
	} else if (pin == 1) {
		ADC10CTL1 = INCH_1;									// Channel 1
		ADC10AE0 = BIT1;									// Make P1.1 analog input
	} else if (pin == 2) {
		ADC10CTL1 = INCH_2;									// Channel 2
		ADC10AE0 = BIT2;									// Make P1.2 analog input
	} else if (pin == 3) {
		ADC10CTL1 = INCH_3;									// Channel 3
		ADC10AE0 = BIT2;									// Make P1.3 analog input
	} else if (pin == 4) {
		ADC10CTL1 = INCH_4;									// Channel 4
		ADC10AE0 = BIT4;									// Make P1.4 analog input
	} else if (pin == 5) {
		ADC10CTL1 = INCH_5;									// Channel 5
		ADC10AE0 = BIT5;									// Make P1.5 analog input
	} else if (pin == 6) {
		ADC10CTL1 = INCH_6;									// Channel 6
		ADC10AE0 = BIT6;									// Make P1.6 analog input
	} else if (pin == 7) {
		ADC10CTL1 = INCH_7;									// Channel 7
		ADC10AE0 = BIT7;									// Make P1.7 analog input
	}

	ADC10CTL1 |= ADC10DIV_3 ;								// ADC10CLK/4
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference

	ADC10CTL0 |= ADC10SC;									// Start a conversion
	while(ADC10CTL1 & ADC10BUSY);							// Wait for conversion to complete
	return ADC10MEM;										// collect that 10-bit value
}
