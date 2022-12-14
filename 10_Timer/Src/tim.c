/*
 * tim.c
 *
 *  Created on: 22/09/2022
 *      Author: daniel
 */


#include "stm32l4xx.h"
#include "tim.h"

#define TIM1EN				(1U<<11)															//Enable Timer 1 Clock Access
#define CR1_CEN				(1U<<0)																//Enable counter

void tim_1hz_init(void)
{
	//Enable APB2 Clock access to Timer 1
	RCC->APB2ENR |= TIM1EN;
	//Load the Timer 1 Pre-scaler with 400
	TIM1->PSC = 400-1;
	//Load the Auto Reload with 10000
	TIM1->ARR = 10000-1;
	//Counter register starts with 0
	TIM1->CNT = 0;
	//Enable counter
	TIM1->CR1 = CR1_CEN;

	}
