/*
 * uart.c
 *
 *  Created on: 17/08/2022
 *      Author: daniel
 */


#include <stdint.h>
#include "uart.h"

#define USART2EN			(1U<<17)															//Enable USART2 Clock - shifts 1 to position 17
#define USART2EN			(1U<<18)															//Enable USART3 Clock - shifts 1 to position 17
#define GPIOAEN				(1U<<0)																//Enable GPIOA Clock
#define SYS_FREQ			4000000																//System clock frequency - Default frequency is 4MHz
#define APB1_CLK			SYS_FREQ															//Peripheral clock 1 equals the system clock


#define CR1_TE				(1U<<3)																//Enables Transmitter
#define CR1_RE				(1U<<2)																//Enables Receiver

#define	CR1_UE				(1U<<0)																//Enable UART module
#define ISR_TXE				(1U<<7)																//Transmitter data register
#define ISR_RXNE			(1U<<5)																//Transmitter data register




static uint16_t compute_uart_div(uint32_t PreiphClk, uint32_t BaudRate); 						//Function prototype for computing the Baudrate value
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PreiphClk, uint32_t BaudRate);	//Prototype function for the BaudRate Register configuration
static void uart2_write(USART_TypeDef *USARTx,uint8_t ch);										//Prototype for the Transmit data function

int __io_putchar(int ch)
{
	uart2_write(USART2, ch);
	return ch;
	}

/*MAKE GENERIC VERSION OF THIS FUNCTION IN ORDER TO RECEIVE ANY USART*/

/*Replace USART2 as USARTx, and Pass it as argument to the function*/
void uart2_rxtx_init(void)
{
	/***********************Configure UART pin***************************/
	/*	Enable clock access to GPIOA for PA2 and PA3 as TX and RX line	*/
	RCC->AHB2ENR|= GPIOAEN;
	/*	Set PA2 Mode as alternate function mode							*/
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);
	/*	Set PA3 Mode as alternate function mode							*/
	GPIOA->MODER &=~ (1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*	Set the alternate function typed to UART						*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*	Set the alternate function typed to UART						*/
	GPIOA->AFR[0] |=(1U<<12);
	GPIOA->AFR[0] |=(1U<<13);
	GPIOA->AFR[0] |=(1U<<14);
	GPIOA->AFR[0] &=~(1U<<15);
	/********************************************************************/

	/********************Configure the UART module***********************/
	/*	Enable clock access to UART2									*/
	RCC->APB1ENR1	|= USART2EN;
	/*	Configure baudrate												*/
	uart_set_baudrate(USART2, APB1_CLK, 115200);
	/*	Configure transfer direction									*/
	USART2->CR1 = (CR1_TE | CR1_RE);									//enable TX and RX
																		//
	/*	Enable UART module												*/
	USART2->CR1	|= CR1_UE;												//Enables the UART module
	/********************************************************************/


}



/*MAKE GENERIC VERSION OF THIS FUNCTION IN ORDER TO RECEIVE ANY USART*/

/*Replace USART2 as USARTx, and Pass it as argument to the function*/
char uartx_tx_init(USART_TypeDef *USARTx)
{
	/***********************Configure UART pin***************************/
	/*	Enable clock access to GPIOA for PA2 as TX line					*/
	RCC->AHB2ENR|= GPIOAEN;
	RCC->AHB2ENR|= GPIOCEN;
	/*	Set PA2 Mode as alternate function mode							*/
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*PC4*/
	GPIOC->MODER |= (1U<<9);
	GPIOC->MODER &=~ (1U<<8);
	/*PC5*/
	GPIOC->MODER |= (1U<<11);
	GPIOC->MODER &=~ (1U<<10);


	/*	Set the alternate function typed to UART						*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*	Set the alternate function typed to UART						*/
	GPIOC->AFR[0] |=(1U<<16);
	GPIOC->AFR[0] |=(1U<<17);
	GPIOC->AFR[0] |=(1U<<18);
	GPIOC->AFR[0] &=~(1U<<19);

	/*	Set the alternate function typed to UART						*/
	GPIOC->AFR[0] |=(1U<<20);
	GPIOC->AFR[0] |=(1U<<21);
	GPIOC->AFR[0] |=(1U<<22);
	GPIOC->AFR[0] &=~(1U<<19);
	/********************************************************************/

	/********************Configure the UART module***********************/
	/*	Enable clock access to UART2									*/
	RCC->APB1ENR1	|= USART2EN;
	/*	Configure baudrate												*/
	uart_set_baudrate(USARTx, APB1_CLK, 115200);
	/*	Configure transfer direction									*/
	USARTx->CR1 = CR1_TE;												//Important to use '=' instead of '|=' operator, in order to clean everything
																		//and set the othes configs of to it's default values
	/*	Enable UART module												*/
	USARTx->CR1	|= CR1_UE;												//Enables the UART module
	/********************************************************************/


}



{

	/*Wait for receive data register not empty flag*/
	while(!(USARTx->ISR & ISR_RXNE))																//Wait for transmit data register to be empty
	{
		//wait, nothing to read.
	}
	/*Read content of receive data register*/
	return USARTx->RDR;
	}

static void uart2_write(USART_TypeDef *USARTx,uint8_t ch)
{
	/*Reading a register - Perform a 'and' operation against the register and the bit we want to read*/
	while(!(USARTx->ISR & ISR_TXE))																//Wait for transmit data register to be empty
	{
		//wait
	}
	/*TDR - Transmitter Data Register it's equal to the character we want to send*/
	USARTx->TDR = (ch & 0xFF);											// & 0xFF makes sure that 8 bits are transmitted
	}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PreiphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div(PreiphClk, BaudRate);
	}

static uint16_t compute_uart_div(uint32_t PreiphClk, uint32_t BaudRate)
{
	return ((PreiphClk + (BaudRate/2))/BaudRate);
	}

