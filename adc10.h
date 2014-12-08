/*
 * 		Title: adc10.h
 *  	Date: Dec 4, 2014
 *      Author: C16Jasper.Arneberg
 *
 *      Description: This library allows the user to
 *      directly convert an analog signal to a hexidecimal
 *      value using the ADC10 on the MSP430. The readADC() method
 *      takes in 1 paramter, the pin that is to be converted.
 */

#ifndef ADC10_H_
#define ADC10_H_

int readADC(int pin);

#endif /* ADC10_H_ */
