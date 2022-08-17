/*Hello World LED toggle, using ST Header file and BSRR register
 *
 * */

#include "stm32l4xx.h"


#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5


#define GPIOAEN				(1U<<0)										//shifts 1 to position 0

int main(void){

	/*
	//Enable clock accesses to GPIOA
	RCC_AHB2EN_R |= GPIOAEN;
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);											//set's only 11th bit to 0
	 */
	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);

	//Enabling clock accesses to GIPOA using structures method


	while(1){

		GPIOA->BSRR |= (1U<<5);												//Sets PIN 5 from PORTA
		for(int i = 0; i<500000; i++){}
		GPIOA->BSRR |= (1U<<21);											//Resets PIN 5 from PORTA
		for(int i = 0; i<500000; i++){}
	}
}
