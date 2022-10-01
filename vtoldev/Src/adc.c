/*
 * adc.c
 *
 *  Created on: 21/09/2022
 *      Author: daniel
 */
#include "stm32l4xx.h"
#include "adc.h"

#define GPIOAEN				(1U<<0)																//Enable GPIOA Clock
#define ASCR_ASC4			(1U<<4)																//PIN 4 - Connect analog switch to the ADC input
#define ADCEN				(1U<<13)															//ADC Clock Enable
#define CFGR_CONT			(1U<<13)															//Set Continuous conversion mode
#define SEQ_LEN_1			0																	//Sets the number of conversions in the regular
#define	ISR_EOC			(1U<<2)																//End of conversion flag																								//channel conversion sequence.

void PA4_ADC1_INIT(void)
{
	/***Configure ADC PIN***/
	//Enable clock access to GPIOA
	RCC->AHB2ENR|= GPIOAEN;
	//Set PA4 mode to Analog - Analog (11) - bits 8 and 9
	GPIOA->MODER |= (1U<<8);
	GPIOA->MODER |= (1U<<9);
	//Connect GPIO Analog switch to ADC input
	GPIOA->ASCR	|=	ASCR_ASC4;

	/***Configure ADC Module***/
	//Enable clock access to ADC Module
	RCC->AHB2ENR |=	ADCEN;
	//Set ADC common clock
	ADC123_COMMON->CCR	&=~ (1U<<16);
	ADC123_COMMON->CCR	|=  (1U<<17);
	//Set continuous conversion
	ADC1->CFGR |= CFGR_CONT;
	//set sequencer length
	ADC1->SQR1	|= SEQ_LEN_1;
	//set ADC channel and rank - Since only one channel is being used, this channel is going to be he first to be converted
	//and the channel in question is IN_9 - needs to be converted to binary and inserted at SQR1 - 0b 0 1001
	ADC1->SQR1	|=	(1U<<6);
	ADC1->SQR1	|=	(1U<<9);
	//Disable ADC deep power down - Not i power Down - Default value is 1
	ADC1->CR	&=~	(1U<<29);
	//Enable ADC internal regulator
	ADC1->CR	|=	(1U<<28);
	//Start ADC calibration
	ADC1->CR	|=	(1U<<31);
	//Enable ADC
	ADC1->CR	|=	(1U<<0);
}

void start_conversion(void){
	//Start regular conversion
	ADC1->CR	|=	(1U<<2);
}

uint32_t adc_read(void){
	//Wait for end-of-conversion flag by reading the EOC flag. Using the AND operation against the bit we want
	//to read, this operation will return 1 in case of bit number 2 in the ADC1->CR is set to 1 and will return zero if not.
	//So, while the operation does not return 1, we wait
	while(!(ADC1->ISR & ISR_EOC)){}

	//Clear the End of conversion flag
	ADC1->ISR	|= ISR_EOC;
	//Returns the data converted, stored at the data register
	return (ADC1->DR);
	}



