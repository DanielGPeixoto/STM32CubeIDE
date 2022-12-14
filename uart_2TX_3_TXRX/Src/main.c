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



/**********************************************/
/*	printf() to write through serial monitor  //
 * 	only working with UART2.				  //
 * 											  //
 */											  //
/**********************************************/

#include "stm32l4xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"

char cUART2WriteBuffer[20];
char cUART3ReadBuffer[20];
char cUARTBufferSaved[20];



int main(void){


	/*MAKE GENERIC VERSION OF THIS FUNCTION IN ORDER TO RECEIVE ANY USART*/
	uart2_tx_init();
	uart3_rx_init();
	/*Replace USART2 as USARTx, and Pass it as argument to the function*/
	while(1){


		cUART3ReadBuffer[0] = uart_read_function(USART3);
		/*if(cUART3ReadBuffer[0] != cUARTBufferSaved[0])
		{
			cUARTBufferSaved[0] = cUART3ReadBuffer[0];
			cUART2WriteBuffer[0] = cUARTBufferSaved[0];

			printf(cUART2WriteBuffer);
		}

*/
		cUART2WriteBuffer[0] = cUART3ReadBuffer[0];
		printf(cUART2WriteBuffer);


	}

}
