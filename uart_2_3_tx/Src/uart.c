/*
 * uart.c
 *
 *  Created on: 17/08/2022
 *      Author: daniel
 */

#include "stm32l4xx.h"
#include <stdint.h>


#define USART2EN			(1U<<17)															//Enable USART2 Clock - shifts 1 to position 17
#define USART3EN			(1U<<18)															//Enable USART2 Clock - shifts 1 to position 17
#define GPIOAEN				(1U<<0)																//Enable GPIOA Clock
#define GPIOCEN				(1U<<2)																//Enable GPIOC Clock
#define SYS_FREQ			4000000																//System clock frequency - Default frequency is 4MHz
#define APB1_CLK			SYS_FREQ															//Peripheral clock 1 equals the system clock


#define CR1_TE				(1U<<3)																//Enables Transmitter
#define	CR1_UE				(1U<<0)																//Enable UART module
#define ISR_TXE				(1U<<7)																//Transmitter data register



static uint16_t compute_uart_div(uint32_t PreiphClk, uint32_t BaudRate); 						//Function prototype for computing the Baudrate value
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PreiphClk, uint32_t BaudRate);	//Prototype function for the BaudRate Register configuration
void uart_write_function(USART_TypeDef *USARTx,uint8_t ch);										//Prototype for the Transmit data function


/*Tenho de passar por argumento, a USART a Utilizar!!*/
/*
int __io_putchar(USART_TypeDef *USARTx, int ch)
{
	uart_write(USARTx, ch);
	return ch;
	}
*/

/*MAKE GENERIC VERSION OF THIS FUNCTION IN ORDER TO RECEIVE ANY USART*/

/*Replace USART2 as USARTx, and Pass it as argument to the function*/
void uart2_tx_init(void)
{
	/***********************Configure UART pin***************************/
	/*	Enable clock access to GPIOA for PA2 as TX line					*/
	RCC->AHB2ENR|= GPIOAEN;
	/*	Set PA2 Mode as alternate function mode							*/
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*	Set the alternate function typed to UART						*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*Set PIN Pull-Down */
	GPIOA->PUPDR &=~ (1U<<4);
	GPIOA->PUPDR |= (1U<<5);
	/********************************************************************/

	/********************Configure the UART module***********************/
	/*	Enable clock access to UART2									*/
	RCC->APB1ENR1	|= USART2EN;
	/*	Configure baudrate												*/
	uart_set_baudrate(USART2, APB1_CLK, 115200);
	/*	Configure transfer direction									*/
	USART2->CR1 = CR1_TE;												//Important to use '=' instead of '|=' operator, in order to clean everything
																		//and set the othes configs of to it's default values
	/*	Enable UART module												*/
	USART2->CR1	|= CR1_UE;												//Enables the UART module
	/********************************************************************/


}

void uart3_tx_init(void)
{
	/***********************Configure UART pin***************************/
	/*	Enable clock access to GPIOA for PC4 as TX line					*/
	RCC->AHB2ENR|= GPIOCEN;
	/*	Set PA2 Mode as alternate function mode							*/
	GPIOC->MODER &=~ (1U<<8);											//Sets 8th bit to zero
	GPIOC->MODER |= (1U<<9);											//Sets 9th bit to 1

	/*	Set the alternate function of PC4 to UART	AF7					*/
	GPIOC->AFR[0] |=(1U<<16);
	GPIOC->AFR[0] |=(1U<<17);
	GPIOC->AFR[0] |=(1U<<18);
	GPIOC->AFR[0] &=~(1U<<19);

	/*Set PIN Pull-Down */
	GPIOC->PUPDR &=~ (1U<<8);
	GPIOC->PUPDR |= (1U<<9);
	/********************************************************************/

	/********************Configure the UART module***********************/
	/*	Enable clock access to UART3									*/
	RCC->APB1ENR1	|= USART3EN;
	/*	Configure baudrate												*/
	uart_set_baudrate(USART3, APB1_CLK, 115200);
	/*	Configure transfer direction									*/
	USART3->CR1 = CR1_TE;												//Important to use '=' instead of '|=' operator, in order to clean everything
																		//and set the othes configs of to it's default values
	/*	Enable UART module												*/
	USART3->CR1	|= CR1_UE;												//Enables the UART module
	/********************************************************************/


}

void uart_write_function(USART_TypeDef *USARTx,uint8_t ch)
{
	/*Reading a register - Perform a 'and' operation against the register and the bit we want to read*/
	while(!(USARTx->ISR & ISR_TXE))																//Wait for transmit data register to be empty
	{

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

