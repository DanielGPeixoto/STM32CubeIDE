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
#include <string.h>
#include "uart.h"


#define PIN_5				(1U<<5)
#define	LED_PIN				PIN_5
#define GPIOAEN				(1U<<0)										//shifts 1 to position 0



char key[1024];
char begin = '$';
char end = '!';
int count = 0;

int main(void){

	/*Turn LED on and off*/
	RCC->AHB2ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);
	/************************/
	uart2_rxtx_init();
	uartx_tx_init(USART3);

	while(1){


		key[count] = uart_read(USART3);

		if(key[count] == begin)
		{
			while (key[count] != '!')
			{
				key[count] = uart_read(USART3);
				count = count + 1;
				/*if(key[count] == end)
				{
					count = 0;
					memset(key, 0, 4096);
				}*/
			}break;

		}
		printf("Nothing");
		for(int i = 0; i<= count; i++)
		{

			printf("%s", key);
		}
		//for(int i = 0; i<1000; i++){}
/*
		if(key[0] == 'Y')
		{
			GPIOA->BSRR |= (1U<<5);												//Sets PIN 5 from PORTA
		}else{
			GPIOA->BSRR |= (1U<<21);											//Resets PIN 5 from PORTA
		}*/
	}
}


