/*
 *  Created on: 21/09/2022
 *      Author: Daniel e Paulo
 */

#include "stm32l4xx.h"


#define TIM2EN				(1U<<0)			//Enable Timer 2 Clock Access
#define dFreqClock			80.0				//2
#define dFreq50Hz			50.0
#define dPercDutyCycle		5.0


void initialize_GPIOE_PA5(){
	//Configure PA5 as Alterative function
	GPIOA->MODER &=~	(1U<<10); //Coloca no pino 0 o valor 1 negado ou seja 0
	GPIOA->MODER |=		(1U<<11);
	//Configure PA5 as push-pull
	GPIOA->OTYPER &=~	(1u<<5);
	//Configure PA5 as very high speed
	GPIOA->OSPEEDR |=	(1U<<10);
	GPIOA->OSPEEDR |=	(1U<<11);
	//Configure AF1 low register, this register is connect with timer
	GPIOA->AFR[0]  |=	(1U<<20);
	GPIOA->AFR[0]  &=~	(1U<<21);
	GPIOA->AFR[0]  &=~	(1U<<22);
	GPIOA->AFR[0]  &=~	(1U<<23);
	//Force diconnect imput to the adc
	GPIOA->ASCR	   &=~	(1U<<5);
}
void pwmb(void){
	long lFreqClock = dFreqClock * 1000000;

	initialize_GPIOE_PA5();
	//Configure Clock 16Mhz
	//RCC->CFGR &=~ (1U<<10);

	//Enable APB2 Clock access to Timer 2
	RCC->APB1ENR1 |= TIM2EN;
	//Maintain 80Mhz of clock so prescale is 1
	TIM2->PSC	=	1-1;
	//Frequency determined by TIMx_ARR
	TIM2->ARR 	= 	(lFreqClock/dFreq50Hz);
	//TIM2->ARR 	= 	(80000000/50);
	//Timer count
	TIM2->CNT	=	0;
	//Duty cycle determined by TIMx_CCRx [
	TIM2->CCR1	= 	(dPercDutyCycle/100)*(lFreqClock/dFreq50Hz);
	//TIM2->CCR1	= 	((dFreqClock/50)*10)/100;

	//PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive
	TIM2->CCMR1	&=~	(1U<<4);
	TIM2->CCMR1	|=	(1U<<5);
	TIM2->CCMR1	|=	(1U<<6);
	TIM2->CCMR1	&=~	(1U<<16);

	//DIR -> 0: Counter used as upcounter
	TIM2->CR1	&=~ (1<<4);
	//TIMx_ARR register is not buffered
	TIM2->CR1	&=~	(1U<<7);

	//UG-> Update generation 1: Re-initialize the counter and generates an update of the registers
	TIM2->EGR	|= 	(1U<<0);

	//CC1P: Capture/Compare 1 output Polarity. 0: OC1 active high (output mode)
	TIM2->CCER	&=~	(1U<<1);
	//CC1E: Capture/Compare 1 output enable. 0: Capture mode disabled
	TIM2->CCER	|=	(1U<<0);

	//CMS[1:0]: Center-aligned mode selection. 00: Edge-aligned mode
	TIM2->CR1	&=~	(1U<<5);
	TIM2->CR1	&=~	(1U<<6);
	//Enable Timer 2
	TIM2->CR1	|=	(1U<<0);

}
void pwmr(void){
	long lFreqClock = dFreqClock * 1000000;

	initialize_GPIOE_PA5();
	//Configure Clock 16Mhz
	//RCC->CFGR &=~ (1U<<10);

	//Enable APB2 Clock access to Timer 2
	RCC->APB1ENR1 |= TIM2EN;
	//Maintain 80Mhz of clock so prescale is 1
	TIM2->PSC	=	1-1;
	//Frequency determined by TIMx_ARR
	TIM2->ARR 	= 	(lFreqClock/dFreq50Hz);
	//TIM2->ARR 	= 	(80000000/50);
	//Timer count
	TIM2->CNT	=	0;
	//Duty cycle determined by TIMx_CCRx [
	TIM2->CCR1	= 	(dPercDutyCycle/100)*(lFreqClock/dFreq50Hz);
	//TIM2->CCR1	= 	((dFreqClock/50)*10)/100;

	//PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive
	TIM2->CCMR1	&=~	(1U<<4);
	TIM2->CCMR1	|=	(1U<<5);
	TIM2->CCMR1	|=	(1U<<6);
	TIM2->CCMR1	&=~	(1U<<16);

	//DIR -> 0: Counter used as upcounter
	TIM2->CR1	&=~ (1<<4);
	//TIMx_ARR register is not buffered
	TIM2->CR1	&=~	(1U<<7);

	//UG-> Update generation 1: Re-initialize the counter and generates an update of the registers
	TIM2->EGR	|= 	(1U<<0);

	//CC1P: Capture/Compare 1 output Polarity. 0: OC1 active high (output mode)
	TIM2->CCER	&=~	(1U<<1);
	//CC1E: Capture/Compare 1 output enable. 0: Capture mode disabled
	TIM2->CCER	|=	(1U<<0);

	//CMS[1:0]: Center-aligned mode selection. 00: Edge-aligned mode
	TIM2->CR1	&=~	(1U<<5);
	TIM2->CR1	&=~	(1U<<6);
	//Enable Timer 2
	TIM2->CR1	|=	(1U<<0);

}
void pwml(void){
	long lFreqClock = dFreqClock * 1000000;

	initialize_GPIOE_PA5();
	//Configure Clock 16Mhz
	//RCC->CFGR &=~ (1U<<10);

	//Enable APB2 Clock access to Timer 2
	RCC->APB1ENR1 |= TIM2EN;
	//Maintain 80Mhz of clock so prescale is 1
	TIM2->PSC	=	1-1;
	//Frequency determined by TIMx_ARR
	TIM2->ARR 	= 	(lFreqClock/dFreq50Hz);
	//TIM2->ARR 	= 	(80000000/50);
	//Timer count
	TIM2->CNT	=	0;
	//Duty cycle determined by TIMx_CCRx [
	TIM2->CCR1	= 	(dPercDutyCycle/100)*(lFreqClock/dFreq50Hz);
	//TIM2->CCR1	= 	((dFreqClock/50)*10)/100;

	//PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive
	TIM2->CCMR1	&=~	(1U<<4);
	TIM2->CCMR1	|=	(1U<<5);
	TIM2->CCMR1	|=	(1U<<6);
	TIM2->CCMR1	&=~	(1U<<16);

	//DIR -> 0: Counter used as upcounter
	TIM2->CR1	&=~ (1<<4);
	//TIMx_ARR register is not buffered
	TIM2->CR1	&=~	(1U<<7);

	//UG-> Update generation 1: Re-initialize the counter and generates an update of the registers
	TIM2->EGR	|= 	(1U<<0);

	//CC1P: Capture/Compare 1 output Polarity. 0: OC1 active high (output mode)
	TIM2->CCER	&=~	(1U<<1);
	//CC1E: Capture/Compare 1 output enable. 0: Capture mode disabled
	TIM2->CCER	|=	(1U<<0);

	//CMS[1:0]: Center-aligned mode selection. 00: Edge-aligned mode
	TIM2->CR1	&=~	(1U<<5);
	TIM2->CR1	&=~	(1U<<6);
	//Enable Timer 2
	TIM2->CR1	|=	(1U<<0);

}
