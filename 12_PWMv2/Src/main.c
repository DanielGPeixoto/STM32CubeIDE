/*UART Transmitter Driver using USART2 Peripheral*/

	/***********************Configure UART pin***************************/
	/*	Enable clock access to GPIOA for PA2 as TX line					*/
	/*	Set PA2 Mode as alternate function mode							*/
	/*	Set the alternate function typed to UART						*/
	/********************************************************************/

	/********************Configure the UART module***********************/
	/*	Enable clock access to UART2									*/
	/*	Configure baudrate												*/
	/*	Configure transfer direction									*/
	/*	Enable UART module												*/
	/********************************************************************/

#include "stm32l4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "pwm.h"

//void dummytimer(void);

int iAnalogValue;

int main(void){

	//PA4_ADC1_INIT();

	//Add delay between initialization and start of converion
	//dummytimer();

	//start_conversion();

	uart2_tx_init();


	pwm();

	while(1){
		for(int i=0; i<10000000; i++)
			TIM2->CCR1	= 	((4000000/50)*40)/100; 	//4000	5% of 20ms
		for(int i=0; i<1000000; i++)
			TIM2->CCR1	= 	((4000000/50)*0)/100; 	//4000	5% of 20ms
	}
}

/*void dummytimer(void)
{
	int count;

	for(int i=0; i < 8000; i++)
	{
		count ++;


	}
}
*/
