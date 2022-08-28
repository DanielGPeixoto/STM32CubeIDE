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

char buffer1[1000];
char buffer2[1000];
int count1 = 0;
int count2 = 0;

int main(void){

	uart3_rx_init();
	uart2_tx_init();
	printf("ola");
	while(1){
		while(uart_read(USART3) != ','){
			buffer1[count1] = uart_read(USART3);
			count1 ++;
		}break;


/*
		while(uart2_read(USART2) != '!'){
					buffer2[count2] = uart2_read(USART2);
					count2 ++;
		}break;
		*/

		for(int i=0; i<= count1; i++)
		{
			printf("%s", buffer1);
		}


	}
}

