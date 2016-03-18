/*
 * display.h
 *
 *  Created on: 15 окт. 2015 г.
 *      Author: Yulia
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "main.h"


#define PIN_HIGH(p,b) (p->BSRRL = b)
#define PIN_LOW(p,b)  (p->BSRRH = b)
#define DI_DIGITS 3

typedef struct {
		GPIO_TypeDef*	port;
		uint16_t		pin;
} DI_Pin_TypeDef;

typedef struct {
		DI_Pin_TypeDef	a;
		DI_Pin_TypeDef	b;
		DI_Pin_TypeDef	c;
		DI_Pin_TypeDef	d;
		DI_Pin_TypeDef	e;
		DI_Pin_TypeDef	f;
		DI_Pin_TypeDef	g;
		DI_Pin_TypeDef	dot;
		DI_Pin_TypeDef	p1;
		DI_Pin_TypeDef	p2;
		DI_Pin_TypeDef	p3;
		DI_Pin_TypeDef	common[DI_DIGITS];//разрядность, у нас 3
		uint8_t			digits[DI_DIGITS];//что в каком разряде
		uint8_t			dot_flag;		  //где точка
		uint8_t			index;			  //текущий разряд
		uint8_t			show;

} DI_TypeDef;






uint16_t DI_Pow10(uint8_t deg);
DI_TypeDef* init_di_port(void);
void DI_DisplayDigit(DI_TypeDef* display, uint8_t digit, uint8_t character, uint8_t dot);
void DI_DisplayNone(DI_TypeDef* display);
void DI_TimerHandler(DI_TypeDef* display);


void DI_Init(DI_TypeDef* display);
void DI_Display(DI_TypeDef* display, uint16_t value, uint8_t DotPos);
void DI_Clear(DI_TypeDef* display);
void DI_DisplayAll(DI_TypeDef* display);
void Display(DI_TypeDef* display, uint16_t value);

#endif

