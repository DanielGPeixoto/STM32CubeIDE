#include "stm32l4xx.h"
#include "ledfreq1hz.h"

#define TIM5EN              (1U<<3)

/*LED 1HZ*/
#define AF2_TIM             (1U<<5)
/*---------------------------------*/
#define GPIOAEN             (1U<<0)     //shifts 1 to position 0

void initialize_GPIOE_PA5(void){
	/*LED 1 Hz PA1*/
	    //RCC->AHB2ENR |= GPIOAEN;
	    GPIOA->MODER |= (1U<<3);
	    GPIOA->MODER &=~ (1U<<2);
	    GPIOA->AFR[0] |= AF2_TIM;
	/*---------------------*/
}
void ledfreq1hz(void){
		initialize_GPIOE_PA5();
	    //Enable APB2 Clock access to Timer 1
	    RCC->APB1ENR1 |= TIM5EN;
	    //Load the Timer 1 Pre-scaler with 400
	    TIM5->PSC = 400-1;
	    //Load the Auto Reload with 10000
	    TIM5->ARR = 10000-1;
	    /*Set CH 2 Output Compare Toggle Mode*/
	    TIM5->CCMR1 |= (1U<<12);
	    TIM5->CCMR1 |= (1U<<13);
	    /*Set Match value to 0*/
	    TIM5->CCR2 = 0;
	    /*Enable the CH 2 compare mode*/
	    TIM5->CCER |= (1U<<4);
	    //Counter register starts with 0
	    TIM5->CNT = 0;
	    //Enable Timer 2
	    TIM5 ->CR1 = (1U<<0);
}
