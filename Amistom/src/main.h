
#ifndef INC_MAIN_H
#define INC_MAIN_H

//---------------------------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include "stdbool.h"
#include "stm32f4xx_usart.h"
//---------------------------------------------------------------------------------------------------
#include "io.h"
#include "globalTimer.h"
#include "outpin.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "button.h"
#include "uart.h"
#include "display.h"
#include "mode.h"
#include "meandr.h"
//---------------------------------------------------------------------------------------------------

enum MODE_EMIT
{
	loading,
	idle,
	starting,
	emit
};


//---------------------------------------------------------------------------------------------------
//void NVIC_conf(void);
void Initialization_All(void);

uint8_t state_err[10]; //error code
uint8_t imp_len; //ms
uint8_t mode_emit;

uint16_t cntr1;
uint16_t cntr_laser;
uint16_t cntr_imp;
uint16_t cntr_emit_wd;
uint16_t cntr_diaph;

_Bool bExp;
_Bool bPlus;
_Bool bMinus;
_Bool bFilm;
_Bool bSafe;
_Bool bPat;
_Bool bUin;
_Bool bUpm;
_Bool bUmo;
_Bool bDin;
_Bool bDpm;
_Bool bDmo;
_Bool beep;



#endif /* INC_MAIN_H */
