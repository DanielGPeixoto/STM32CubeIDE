/*Hello World LED toggle, using ST Header file and BSRR register
 *
 * */

#include "stm32l4xx.h"


#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5

#define PIN_13				(1U<<13)
#define	BTN_PIN				PIN_13


#define GPIOAEN				(1U<<0)										//Enable IO port A clock enable - shifts 1 to position 0
#define GPIOCEN				(1U<<2)										//Enable IO port A clock enable - shifts 1 to position 2

int main(void){

	/*
	//Enable clock accesses to GPIOA
	RCC_AHB2EN_R |= GPIOAEN;
	GPIOA_MODE_R |= (1U<<10);
	GPIOA_MODE_R &=~ (1U<<11);											//set's only 11th bit to 0
	 */
	RCC->AHB2ENR |= GPIOAEN;											//Enable IO PORTA Clock
	RCC->AHB2ENR |= GPIOCEN;											//Enable IO PORTC Clock
	/*sets PIN5 PORTA as general mode output. Bit 10 and 11 of MODE REGISTER as 01 */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	/*sets P13 PORTC as input mode. Bit 26 and 27 of MODE REGISTER as 00*/
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	//Enabling clock accesses to GIPOA using structures method


	while(1){

		/*check if button is pressed  -> & - and operation against value 1 at the 13th bit in the Input Data Register*/
		if(GPIOC->IDR & BTN_PIN){
			GPIOA->BSRR |= (1U<<5);												//Sets PIN 5 from PORTA
		}else{
			GPIOA->BSRR |= (1U<<21);											//Resets PIN 5 from PORTA

		}
	}
}

