/*
 * meandr.h
 *
 *  Created on: 20 окт. 2015 г.
 *      Author: Yulia
 */

#ifndef MEANDR_H_
#define MEANDR_H_

#include "main.h"

uint16_t uint16_time_diff(uint16_t now, uint16_t before);
void init_meandr_timer(void);
void init_meandr__gpio(void);
void meandr_auto(void);
void TIM3_IRQHandler(void);

//==========================================================================
uint16_t meandr_capture(void);
uint16_t average_period(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
_Bool meandr_test(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif /* MEANDR_H_ */
