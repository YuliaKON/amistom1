/*
 * button.h
 *
 *  Created on: 12 окт. 2015 г.
 *      Author: mos-rk-753
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

unsigned char Get_Debounced_0(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
unsigned char Get_Debounced_1(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


//--------------------------------------------------------------
// работа с зубами
//--------------------------------------------------------------
#define TEETH_IND_ALL_OFF		GPIO_ResetBits(GPIOE, GPIO_Pin_3);\
								GPIO_ResetBits(GPIOE, GPIO_Pin_1);\
								GPIO_ResetBits(GPIOB, GPIO_Pin_9);\
								GPIO_ResetBits(GPIOD, GPIO_Pin_2);\
								GPIO_ResetBits(GPIOD, GPIO_Pin_0);\
								GPIO_ResetBits(GPIOC, GPIO_Pin_11);

#define TOOTH_IND_ON(tooth) 	TEETH_IND_ALL_OFF;\
								switch(tooth){\
								case 'din':\
								GPIO_SetBits(GPIOE, GPIO_Pin_3); b_Din = 1; tooth_ch = tooth; break;\
								case 'dpm':\
								GPIO_SetBits(GPIOE, GPIO_Pin_1); b_Dpm = 1; tooth_ch = tooth; break;\
								case 'dmo':\
								GPIO_SetBits(GPIOB, GPIO_Pin_9); b_Dmo = 1; tooth_ch = tooth; break;\
								case 'uin':\
								GPIO_SetBits(GPIOD, GPIO_Pin_2); b_Uin = 1; tooth_ch = tooth; break;\
								case 'upm':\
								GPIO_SetBits(GPIOD, GPIO_Pin_0); b_Upm = 1; tooth_ch = tooth; break;\
								case 'umo':\
								GPIO_SetBits(GPIOC, GPIO_Pin_11); b_Umo = 1; tooth_ch = tooth; break;\
								}



//--------------------------------------------------------------
// Сюда писать кнопки
//--------------------------------------------------------------
typedef enum
{
  B_TEST = 0,
  B_PAT,
  B_SAFE,
  B_PLUS,
  B_MINUS,
  B_UIN,
  B_UPM,
  B_UMO,
  B_DIN,
  B_DPM,
  B_DMO,
  B_FILM,
  B_EXP

}BUTTON_NAME_t;


//--------------------------------------------------------------
// Структура конфигурирования кнопки
//--------------------------------------------------------------
typedef struct {
  BUTTON_NAME_t 	BUTTON_NAME;
  GPIO_TypeDef* 	BUTTON_PORT;
  const uint16_t 	BUTTON_PIN;
  const uint32_t 	BUTTON_CLK;
  GPIOPuPd_TypeDef	BUTTON_R;
  uint8_t 			BUTTON_AKT;
}BUTTON_t;

#define  BUTTON_OBJ   13 // сколько штук Button_NAME_t


//--------------------------------------------------------------
// Статус кнопки
//--------------------------------------------------------------
typedef enum {
  BTN_RELEASED = 0,  // Кнопка не нажата
  BTN_PRESSED        // Кнопка нажата
}BUTTON_STATUS_t;



_Bool Button_OnClick(BUTTON_NAME_t btn_name);
_Bool Button_OnRelease(BUTTON_NAME_t btn_name);
_Bool Button_OnPressed(BUTTON_NAME_t btn_name);
_Bool Button_Read(BUTTON_NAME_t btn_name);
_Bool Button_test(void);
void Button_Init(void);

  #define   BUTTON_TIM              TIM7
  #define   BUTTON_TIM_CLK          RCC_APB1Periph_TIM7
  #define   BUTTON_TIM_PERIODE      4999
  #define   BUTTON_TIM_PRESCALE     839
  #define   BUTTON_TIM_IRQ          TIM7_IRQn
  #define   BUTTON_TIM_ISR_HANDLER  TIM7_IRQHandler



#endif /* BUTTON_H_ */
