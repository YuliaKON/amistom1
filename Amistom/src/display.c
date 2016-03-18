/*
 * display.c
 *
 *  Created on: 15 окт. 2015 г.
 *      Author: Yulia
 */
#include "main.h"

#define DI_DIGITS 3

#define A_OFF 	PIN_LOW(display->a.port, display->a.pin)
#define A_ON 	PIN_HIGH(display->a.port, display->a.pin)
#define B_OFF 	PIN_LOW(display->b.port, display->b.pin)
#define B_ON 	PIN_HIGH(display->b.port, display->b.pin)
#define C_OFF 	PIN_LOW(display->c.port, display->c.pin)
#define C_ON 	PIN_HIGH(display->c.port, display->c.pin)
#define D_OFF 	PIN_LOW(display->d.port, display->d.pin)
#define D_ON 	PIN_HIGH(display->d.port, display->d.pin)
#define E_OFF 	PIN_LOW(display->e.port, display->e.pin)
#define E_ON 	PIN_HIGH(display->e.port, display->e.pin)
#define F_OFF 	PIN_LOW(display->f.port, display->f.pin)
#define F_ON 	PIN_HIGH(display->f.port, display->f.pin)
#define G_OFF 	PIN_LOW(display->g.port, display->g.pin)
#define G_ON 	PIN_HIGH(display->g.port, display->g.pin)
#define DOT_ON  PIN_HIGHT(display->dot.port, display->dot.pin);

#define DOT1_ON 	 PIN_LOW(display->p1.port, display->p1.pin)
#define DOT1_OFF 	 PIN_HIGH(display->p1.port, display->p1.pin)
#define DOT2_ON 	 PIN_LOW(display->p2.port, display->p2.pin)
#define DOT2_OFF	 PIN_HIGH(display->p2.port, display->p2.pin)
#define DOT3_ON 	 PIN_LOW(display->p3.port, display->p3.pin)
#define DOT3_OFF	 PIN_HIGH(display->p3.port, display->p3.pin)

/*	Hardware Functions	*/

uint16_t DI_Pow10(uint8_t deg){
	uint8_t i;
	uint16_t result = 1;
	for(i = 0; i < deg; i++){
		result *= 10;
	}
	return result;
}

void DI_DisplayDigit(DI_TypeDef* display, uint8_t digit, uint8_t character, uint8_t dot_flag){
	DI_DisplayNone(display);

	switch (digit){
		case 1:
			B_ON;
			C_ON;
			A_ON;

						D_OFF;
						E_OFF;
						F_OFF;
						G_OFF;
			break;
		case 2:
			A_ON;
			B_ON;
			C_OFF;
			F_OFF;
			G_ON;
			E_ON;
			D_ON;
			break;
		case 3:
			A_ON;
			B_ON;
			C_ON;
			D_ON;
			E_OFF;
			F_OFF;
			G_ON;
			break;
		case 4:
			A_OFF;
			D_OFF;
			E_OFF;
			F_ON;
			G_ON;
			B_ON;
			C_ON;
			break;
		case 5:
			A_ON;
			F_ON;
			G_ON;
			C_ON;
			D_ON;
			break;
		case 6:
			A_ON;
			C_ON;
			D_ON;
			E_ON;
			F_ON;
			G_ON;
			break;
		case 7:
			A_ON;
			B_ON;
			C_ON;
			break;
		case 8:
			A_ON;
			B_ON;
			C_ON;
			D_ON;
			E_ON;
			F_ON;
			G_ON;
			break;
		case 9:
			A_ON;
			B_ON;
			C_ON;
			D_ON;
			F_ON;
			G_ON;
			break;
		case 0:
			A_ON;
			B_ON;
			C_ON;
			D_ON;
			E_ON;
			F_ON;
			break;
	}

	//if (dot_flag == 1) DOT_ON;
	//if (dot_flag == 2) DOT2_ON;
	//if (dot_flag == 3) DOT3_ON;
	PIN_LOW(display->common[character].port, display->common[character].pin);

}

void DI_DisplayNone(DI_TypeDef* display){
	uint8_t i;

	A_OFF;
	B_OFF;
	C_OFF;
	D_OFF;
	E_OFF;
	F_OFF;
	G_OFF;


	for(i = 0; i < DI_DIGITS; i++){
		PIN_HIGH(display->common[i].port, display->common[i].pin);
	}
}

void DI_DisplayAll(DI_TypeDef* display){
	uint8_t i;

	A_ON;
	B_ON;
	C_ON;
	D_ON;
	E_ON;
	F_ON;
	G_ON;
//	DOT1_ON;
//	DOT2_ON;
//	DOT3_ON;

	for(i = 0; i < DI_DIGITS; i++){
		PIN_HIGH(display->common[i].port, display->common[i].pin);
	}
}

void DI_TimerHandler(DI_TypeDef* display){
	if (display->show == 1){
		DI_DisplayDigit(display, display->digits[display->index], display->index, (display->dot_flag == display->index) ? 1 : 0);
		display->index++;
		if (display->index == DI_DIGITS){
			display->index = 0;
		}
	}
}

DI_TypeDef* init_di_port(void){

DI_TypeDef display;

display.a.port = GPIOH;
display.b.port = GPIOC;
display.c.port = GPIOE;
display.d.port = GPIOE;
display.e.port = GPIOE;
display.f.port = GPIOE;
display.g.port = GPIOB;
display.p1.port = GPIOH;
display.p2.port = GPIOC;
display.p3.port = GPIOC;

display.a.pin = GPIO_Pin_0;
display.b.pin = GPIO_Pin_14;
display.c.pin = GPIO_Pin_6;
display.d.pin = GPIO_Pin_4;
display.e.pin = GPIO_Pin_2;
display.f.pin = GPIO_Pin_0;
display.g.pin = GPIO_Pin_8;
display.p1.pin = GPIO_Pin_1;
display.p2.pin = GPIO_Pin_15;
display.p3.pin = GPIO_Pin_13;

return &display; //&display
}

void DI_Init(DI_TypeDef* display){
	uint8_t i;
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;

	gpio.GPIO_Pin = display->a.pin;
	GPIO_Init(display->a.port, &gpio);
	gpio.GPIO_Pin = display->b.pin;
	GPIO_Init(display->b.port, &gpio);
	gpio.GPIO_Pin = display->c.pin;
	GPIO_Init(display->c.port, &gpio);
	gpio.GPIO_Pin = display->d.pin;
	GPIO_Init(display->d.port, &gpio);
	gpio.GPIO_Pin = display->e.pin;
	GPIO_Init(display->e.port, &gpio);
	gpio.GPIO_Pin = display->f.pin;
	GPIO_Init(display->f.port, &gpio);
	gpio.GPIO_Pin = display->g.pin;
	GPIO_Init(display->g.port, &gpio);
	gpio.GPIO_Pin = display->common[0].pin;
	GPIO_Init(display->common[0].port, &gpio);
	gpio.GPIO_Pin = display->common[1].pin;
	GPIO_Init(display->common[1].port, &gpio);
	gpio.GPIO_Pin = display->common[2].pin;
	GPIO_Init(display->common[2].port, &gpio);

	}


void DI_Display(DI_TypeDef* display, uint16_t value, uint8_t DotPos){
	uint8_t number, digit;

	number = value;
	for (digit = (DI_DIGITS-1); digit > 0 ; digit--){
		number %= DI_Pow10(digit+1);
		display->digits[digit] = (number / DI_Pow10(digit));
	}
	display->digits[0] = (number % 10);
	display->dot_flag = DotPos;
	display->index = 0;
	display->show = 1;
}

void Display(DI_TypeDef* display, uint16_t value){
	uint8_t number, digit;

	number = value;
	display->digits[0] = (number);
	display->index = 0;
	display->show = 1;
}

void DI_Clear(DI_TypeDef* display){
	display->show = 0;
	DI_DisplayNone(display);
}

