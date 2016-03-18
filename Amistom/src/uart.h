/*
 * uart.h
 *
 *  Created on: 02.02.2015
 *      Author: Yulia
 */

#ifndef UART_H_
#define UART_H_

#define 	UART_BAUDRATE 				9600
#define 	ADC_DIAFRAGMA				Usart3_Send_String(" voltage = "); send_int_Usart((int)(voltage*1000)); Usart3_Send_String("mV \n");



#include "main.h"

long USART_Read_int(void);
void Init_Uart3(void);
void USART3_IRQHandler(void);
void send_int_Usart(long c);

#endif /* UART_H_ */
