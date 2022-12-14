/*
 * uart.h
 *
 *  Created on: 17/08/2022
 *      Author: daniel
 */

#ifndef UART_H_
#define UART_H_

void uart2_tx_init(void);
void uart3_tx_init(void);
void uart3_rx_init(void);
void uart_write_function(USART_TypeDef *USARTx,uint8_t ch);
char uart_read_function(USART_TypeDef *USARTx);

#endif /* UART_H_ */
