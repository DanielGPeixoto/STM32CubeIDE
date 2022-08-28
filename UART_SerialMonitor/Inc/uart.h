/*
 * uart.h
 *
 *  Created on: 17/08/2022
 *      Author: daniel
 */

#ifndef UART_H_
#define UART_H_
#include "stm32l4xx.h"

char uartx_tx_init(USART_TypeDef *USARTx);
char uart_read(USART_TypeDef *USARTx);
void uart2_rxtx_init(void);


#endif /* UART_H_ */
