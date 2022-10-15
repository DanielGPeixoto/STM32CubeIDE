/*
 *  Created on: 21/09/2022
 *      Author: Daniel e Paulo
 */
#include "stm32l4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "ledfreq1hz.h"
#include "pwm.h"
#include "systemclock.h"

/****************	Constats defines **********************/
#define dFreqClock 8.0	//Define frequency on MHz 2 by defoult
#define dFreq50Hz  50.0	//Define frequency on Hz
#define dPercMotorMin	1.0	//Define percentage minimum at 5%
#define dPercMotorMax	100.0	// Define percentage maximum at 10%
#define dDutyCycle		TIM2->CCR1
//#define lFreqClock 	2000000
/***************************************************/
void init(void);
long lFreqClock = 0.0;
long lFreq50Hz = 0.0;

int iAnalogValue;
int lValueDutyCycleMin = 0.0;	//Value for CCR1
int lValueDutyCycleMax = 0.0;	//Value for CCR1
long lValueDutyCycle = 0.0;
int iContTime = 0;

//apagar
double x = 0.0, z = 0.0, y = 0.0, k = 0.0;
unsigned long convert(int iAdcRead){
	int iInputMin = 1.0, iInputMax = 4096.0;
	z = (iAdcRead - iInputMin);
	x = (lValueDutyCycleMax - lValueDutyCycleMin);
	y = (iInputMax - iInputMin);
	k = (z*x);
	//printf("iAdcRead %d; iInputMax %d; iInputMin %d; lValueDutyCycleMax: %d; lValueDutyCycleMin %d; \n\r", iAdcRead, iInputMax, iInputMin, lValueDutyCycleMax,lValueDutyCycleMin);
	return (((iAdcRead - iInputMin)*((lValueDutyCycleMax - lValueDutyCycleMin)/(iInputMax - iInputMin))) + lValueDutyCycleMin);
}

int main(void){
	systemclock();
	init();
	ledfreq1hz();
	iContTime = 0;
	PA4_ADC1_INIT();
	//Add delay between initialization and start of converion
	TIM5->SR &=~ (1U<<0);
	while(iContTime < 4){
			if(TIM5->SR  & (1U<<0)){
				TIM5->SR &=~ (1U<<0);
				iContTime ++;
			}
	}
	ledfreq1hz();
	start_conversion();
	uart2_tx_init();
	pwm();
	//Add delay for do motor start
	TIM5->SR &=~ (1U<<0);
	iContTime = 0;
	while(iContTime < 16){
		if(TIM5->SR  & (1U<<0)){
			TIM5->SR &=~ (1U<<0);
			iContTime ++;
		}
	}
	//Whait at potenciometer is a low value
	while((adc_read()) > 50);

	while(1){
		iAnalogValue = adc_read();
		iAnalogValue = 2048;
		lValueDutyCycle = convert(iAnalogValue);
		//printf("iAnalogValue: %d; lValueDutyCycle %d; lValueDutyCycleMax: %d; lValueDutyCycleMin %d; \n\r",iAnalogValue, lValueDutyCycle, lValueDutyCycleMax,lValueDutyCycleMin);
		//printf("lValueDutyCycle %d, lFreq50Hz %ld, iPercDuty %f, \n\r", lValueDutyCycle, lFreq50Hz, iPercDuty);
		dDutyCycle	= 	lValueDutyCycle; 	//4000	5% of 20ms
	}
}

void init(void){
	lFreqClock	=	dFreqClock * 1000000.0; //Multiply dFreqClock with 1000000
	lFreq50Hz	=	lFreqClock / dFreq50Hz;	//Value for ARR
	lValueDutyCycleMin = (((dPercMotorMin)/(100))*lFreq50Hz); //Value for CCR1
	lValueDutyCycleMax = (dPercMotorMax/100)*lFreq50Hz;	//Value for CCR1
	//printf("lFreqClock: %ld; lFreq50Hz %ld; lValueDutyCycleMin: %d; lValueDutyCycleMax %d; \n\r",lFreqClock, lFreq50Hz, lValueDutyCycleMin,lValueDutyCycleMax);
}

