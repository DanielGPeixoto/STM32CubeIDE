/*
 * uart.h
 *
 *  Created on: 17/08/2022
 *      Author: daniel
 */

#ifndef UART_H_
#define UART_H_
#include "stm32l4xx.h"

void uart2_tx_init(void);
char uart2_read(USART_TypeDef *USARTx);
void uart2_rxtx_init(void);

#endif /* UART_H_ */
