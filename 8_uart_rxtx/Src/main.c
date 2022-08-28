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


#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5
#define GPIOAEN				(1U<<0)										//shifts 1 to position 0

char key;


int main(void){

	/*Turn LED on and off*/
	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	/************************/
	uart2_rxtx_init();

	while(1){
		key = uart2_read(USART2);


		if(key == 'Y')
		{
			uart2_write(USART2, 'A');																//Writes the letter 'Y' through the UART2
			GPIOA->BSRR |= (1U<<5);												//Sets PIN 5 from PORTA
		}else{
			uart2_write(USART2, 'B');																//Writes the letter 'Y' through the UART2
			GPIOA->BSRR |= (1U<<21);											//Resets PIN 5 from PORTA
		}
	}
}

