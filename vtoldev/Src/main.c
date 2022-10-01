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
#include "ledfreq1hz.h"
#include "pwm.h"

/****************	Constats defines **********************/
#define dFreqClock 2.0	//Define frequency on MHz
#define dFreq50Hz  50.0	//Define frequency on Hz
#define dPercMotorMin	5.0	//Define percentage minimum at 5%
#define dPercMotorMax	10.0	//Define percentage maximum at 10%
//#define iFreqClock 	2000000
/***************************************************/
void dummytimer(void);
void init(void);
long iFreqClock = 0.0;
long iFreq50Hz = 0.0;

int iAnalogValue;
int iDutyCycleMin = 0.0;	//Value for CCR1
int iDutyCycleMax = 0.0;	//Value for CCR1
int iDutyCycle = 0.0;


int convert(int iAdcRead){
	int iInputMin = 1.0, iInputMax = 4096.0;
	//printf("iAdcRead %d; iInputMax %d; iInputMin %d; iDutyCycleMax: %d; iDutyCycleMin %d; \n\r", iAdcRead, iInputMax, iInputMin, iDutyCycleMax,iDutyCycleMin);
	return ((((iAdcRead - iInputMin)*(iDutyCycleMax - iDutyCycleMin))/(iInputMax - iInputMin)) + iDutyCycleMin);
}

int main(void){
	init();
	PA4_ADC1_INIT();
	//Add delay between initialization and start of converion
	dummytimer();
	start_conversion();
	ledfreq1hz();
	uart2_tx_init();
	pwm();
	while(1){
		init();
		iAnalogValue = adc_read();
		iDutyCycle = convert(iAnalogValue);
		//printf("iAnalogValue: %d; iDutyCycle %d; iDutyCycleMax: %d; iDutyCycleMin %d; \n\r",iAnalogValue, iDutyCycle, iDutyCycleMax,iDutyCycleMin);
		//printf("iDutyCycle %d, iFreq50Hz %ld, iPercDuty %f, \n\r", iDutyCycle, iFreq50Hz, iPercDuty);
		TIM2->CCR1	= 	iDutyCycle; 	//4000	5% of 20ms
	}
}

void dummytimer(void)
{
	int count;
	for(int i=0; i < 8000; i++)
	{
		count ++;
	}
}
void init(void){
	iFreqClock	=	dFreqClock * 1000000; //Multiply dFreqClock with 1000000
	iFreq50Hz	=	iFreqClock / dFreq50Hz;	//Value for ARR
	iDutyCycleMin = (((dPercMotorMin)/(100))*iFreq50Hz); //Value for CCR1
	iDutyCycleMax = (dPercMotorMax/100)*iFreq50Hz;	//Value for CCR1
	//printf("iFreqClock: %ld; iFreq50Hz %ld; iDutyCycleMin: %d; iDutyCycleMax %d; \n\r",iFreqClock, iFreq50Hz, iDutyCycleMin,iDutyCycleMax);
}

