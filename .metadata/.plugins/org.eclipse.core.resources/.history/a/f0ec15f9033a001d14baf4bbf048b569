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
																								//channel conversion sequence.

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
	//Disable ADC deep power down


	//Enable ADC internal regulator
	//Start ADC calibration
	//Enable ADC


	}




