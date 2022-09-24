/*
 * pwm.c
 *
 *  Created on: 24/09/2022
 *      Author: daniel
 */

#include "stm32l4xx.h"


#define TIM1EN				(1U<<11)															//Enable Timer 1 Clock Access
#define CR1_CEN				(1U<<0)																//Enable counter

#define GPIOEN				(1U<<4)																//Enable clock access to GPIO

void initialize_GPIOE(void){

	/*Enable clock access to Port E*/
	RCC->AHB2ENR	|= GPIOEN;
	/*Set PE14 Mode as alternate function mode*/
	GPIOA->MODER &=~ (1U<<28);
	GPIOA->MODER |= (1U<<29);

	/*Set the alternate function AF1 to PE14*/
	GPIOE->AFR[1] |=(1U<<24);
	GPIOE->AFR[1] &=~(1U<<25);
	GPIOE->AFR[1] &=~(1U<<26);
	GPIOE->AFR[1] &=~(1U<<27);
}


void pwm(void)
{
	initialize_GPIOE();

	//Enable APB2 Clock access to Timer 1
	RCC->APB2ENR |= TIM1EN;
	//Load the Timer 1 Pre-scaler with 400
	TIM1->PSC = 400-1;
	//Load the Auto Reload with 10000
	TIM1->ARR = 10000-1;
	//Duty Cycle
	TIM1->CCR4 = 50;
	//Set CC4 Channel as output
	TIM1->CCMR2	&=~(1U<<8);
	TIM1->CCMR2	&=~(1U<<9);
	//Set Output polarity active high
	TIM1->CCER &=~(1U<<13);
	//Output Compare 4 Mode set as PWM Mode 1  0110
	TIM1->CCMR2 &=~(1U<<12);
	TIM1->CCMR2 |= (1U<<13);
	TIM1->CCMR2 |= (1U<<14);
	TIM1->CCMR2 &=~(1U<<24);
	//Enable Pre-load Register
	TIM1->CCMR2 |= (1U<<11);
	// Capture/Compare 4 Output Enable
	TIM1->CCER |= (1U<<12);
	//Reinitializes the counter and generate  an update of registers
	TIM1->EGR  |= (1U<<0);
	//
	TIM1->BDTR  |= (1U<<15);
	//Counter register starts with 0
	//TIM1->CNT = 0;

	//Enable counter
	TIM1->CR1 = CR1_CEN;

	}
