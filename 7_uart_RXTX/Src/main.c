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

char text[4096] = "Esta e uma mensagem a ser transmitida por UART.\n";



int main(void){


	/*MAKE GENERIC VERSION OF THIS FUNCTION IN ORDER TO RECEIVE ANY USART*/
	uart2_tx_init();
	/*Replace USART2 as USARTx, and Pass it as argument to the function*/

	while(1){

		printf("%s", text);
		for(int i = 0; i<1000; i++){}
	}

}
