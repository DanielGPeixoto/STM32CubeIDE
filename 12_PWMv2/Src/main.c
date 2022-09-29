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

#define dFreqClock 4000000

//void dummytimer(void);

int iAnalogValue;
int iDutyCycleMin = ((dFreqClock/50)*5)/100;
int iDutyCycleMax = ((dFreqClock/50)*10)/100;
float fDutyCycle = 0.0;

int convert(int iAdcRead){
	iInputMin = 1, iInputMax = 4096;
	return (iAdcRead - iInputMin)*(iDutyCycleMax - iDutyCycleMin)/(iInputMax - iInputMin) + iDutyCycleMax;
}
int main(void){
	PA4_ADC1_INIT();
	//Add delay between initialization and start of converion
	dummytimer();
	start_conversion();
	//tim_1hz_init();
	//uart2_tx_init();
	pwm();

	while(1){
		iAnalogValue = adc_read();
		fDutyCycle = convert(iAnalogValue);
		printf("Analog Value, Value converted: %d\n\r", iAnalogValue, fDutyCycle);
		TIM2->CCR1	= 	fDutyCycle; 	//4000	5% of 20ms
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
