/*
 * button.c
 *
 *  Created on: 12 окт. 2015 г.
 *      Author: mos-rk-753
 */
#include "button.h"
uint8_t press = 1;
char tooth;


enum  PATIENT { pat_1 = 1, pat_2, pat_3 };
void Button_InitTIM(void);
void Button_InitNVIC(void);


BUTTON_t BUTTON[] = {
  // Name    ,PORT , PIN       , CLOCK              ,Opposition      , Status
  {B_TEST 	 ,GPIOA, GPIO_Pin_0 	,RCC_AHB1Periph_GPIOA, GPIO_PuPd_UP, Bit_SET},
  {B_PAT 	 ,GPIOD, GPIO_Pin_1 	,RCC_AHB1Periph_GPIOD, GPIO_PuPd_UP, Bit_SET},
  {B_SAFE	 ,GPIOD, GPIO_Pin_3 	,RCC_AHB1Periph_GPIOD, GPIO_PuPd_UP, Bit_SET},
  {B_PLUS 	 ,GPIOB, GPIO_Pin_4 	,RCC_AHB1Periph_GPIOB, GPIO_PuPd_UP, Bit_SET},
  {B_MINUS	 ,GPIOD, GPIO_Pin_7 	,RCC_AHB1Periph_GPIOD, GPIO_PuPd_UP, Bit_SET},
  {B_UIN     ,GPIOC, GPIO_Pin_12 	,RCC_AHB1Periph_GPIOC, GPIO_PuPd_UP, Bit_SET},
  {B_UPM  	 ,GPIOC, GPIO_Pin_10 	,RCC_AHB1Periph_GPIOC, GPIO_PuPd_UP, Bit_SET},
  {B_UMO     ,GPIOA, GPIO_Pin_14	,RCC_AHB1Periph_GPIOA, GPIO_PuPd_UP, Bit_SET},
  {B_DIN     ,GPIOA, GPIO_Pin_10	,RCC_AHB1Periph_GPIOA, GPIO_PuPd_UP, Bit_SET},
  {B_DPM 	 ,GPIOA, GPIO_Pin_8	 	,RCC_AHB1Periph_GPIOA, GPIO_PuPd_UP, Bit_SET},
  {B_DMO 	 ,GPIOC, GPIO_Pin_8		,RCC_AHB1Periph_GPIOC, GPIO_PuPd_UP, Bit_SET},
  {B_FILM 	 ,GPIOD, GPIO_Pin_5	 	,RCC_AHB1Periph_GPIOD, GPIO_PuPd_UP, Bit_SET},
  {B_EXP 	 ,GPIOC, GPIO_Pin_8		,RCC_AHB1Periph_GPIOC, GPIO_PuPd_UP, Bit_SET},
};

void Button_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  BUTTON_NAME_t btn_name;

  for(btn_name = 0; btn_name < BUTTON_OBJ; btn_name++) {
    // Включение тактирования
    RCC_AHB1PeriphClockCmd(BUTTON[btn_name].BUTTON_CLK, ENABLE);

    // Конфигурация как цифровой вход
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = BUTTON[btn_name].BUTTON_R;
    GPIO_InitStructure.GPIO_Pin = BUTTON[btn_name].BUTTON_PIN;
    GPIO_Init(BUTTON[btn_name].BUTTON_PORT, &GPIO_InitStructure);
  }

  Button_InitTIM();
  Button_InitNVIC();
}

//--------------------------------------------------------------
_Bool Button_Read(BUTTON_NAME_t btn_name)
{
  if(!Get_Debounced_1(BUTTON[btn_name].BUTTON_PORT, BUTTON[btn_name].BUTTON_PIN)) {
    return(1);
  }
  else {
    return(0);
  }
}

//--------------------------------------------------------------
// Кнопка нажата (защита от дребезга контактов)
// ret_wert = True только один раз, в момент нажатия кнопки
//--------------------------------------------------------------
_Bool Button_OnClick(BUTTON_NAME_t btn_name)
{
  uint8_t			 wert,	old;
  static uint8_t 	 old_wert[BUTTON_OBJ];

  wert =	 		   BUTTON[btn_name].BUTTON_AKT;
  old = 			   old_wert[btn_name];
  old_wert[btn_name] = wert;

  if(wert == 0) {
	 if(old != 0)  return(true);
  }
  return(false);
  }

_Bool Button_test(void)
{
	uint16_t i=0;

		for(i = 1;i <= 12; i++)
		{
			if(BUTTON[i].BUTTON_AKT == 1) return (false);
		  }
return (true);
}

/*_Bool Button_OnClick(BUTTON_NAME_t btn_name)
{
  uint8_t wert,old;
  static uint8_t old_wert[BUTTON_OBJ];

  wert=BUTTON[btn_name].BUTTON_AKT;
  old=old_wert[btn_name];
  old_wert[btn_name]=wert;

  if(wert!=Bit_RESET) {
    return(false);
  }
  else if(old==Bit_RESET) {
    return(false);
  }
  else {
    return(true);
  }
}*/

//--------------------------------------------------------------
// Кнопка отпущена (защита от дребезга контактов)
// ret_wert = True только один раз, в момент отпускания кнопки
//--------------------------------------------------------------
_Bool Button_OnRelease(BUTTON_NAME_t btn_name)
{
  uint8_t wert, old;
  static uint8_t old_wert[BUTTON_OBJ];

  wert = BUTTON[btn_name].BUTTON_AKT;
  old = old_wert[btn_name];
  old_wert[btn_name] = wert;

  if(wert != 0) {
    return(false);
  }
  else if(old == Bit_RESET) {
    return(false);
  }
  else {
    return(true);
  }
}

_Bool Button_OnPressed(BUTTON_NAME_t btn_name)
{
  if(BUTTON[btn_name].BUTTON_AKT) {
    return(false);
  }
  else {
    return(true);
  }
}


//--------------------------------------------------------------
// Инициализация Timer
//--------------------------------------------------------------
void Button_InitTIM(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  RCC_APB1PeriphClockCmd(BUTTON_TIM_CLK, ENABLE);

  // Инициализация таймера
  TIM_TimeBaseStructure.TIM_Period =  BUTTON_TIM_PERIODE;
  TIM_TimeBaseStructure.TIM_Prescaler = BUTTON_TIM_PRESCALE;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(BUTTON_TIM, &TIM_TimeBaseStructure);


  TIM_ARRPreloadConfig(BUTTON_TIM, ENABLE);
  TIM_Cmd(BUTTON_TIM, ENABLE);
}

//--------------------------------------------------------------
// Инициализация NVIC
//--------------------------------------------------------------
void Button_InitNVIC(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  //---------------------------------------------
  // Инициализация прерывания от таймера
  //---------------------------------------------
  TIM_ITConfig(BUTTON_TIM,TIM_IT_Update,ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = BUTTON_TIM_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//--------------------------------------------------------------
// Прерывание от таймера
//--------------------------------------------------------------
void BUTTON_TIM_ISR_HANDLER(void)
{
  BUTTON_NAME_t btn_name;
  uint8_t wert;

  TIM_ClearITPendingBit(BUTTON_TIM, TIM_IT_Update);

  // сканируем кнопки
  for(btn_name = 0; btn_name < BUTTON_OBJ; btn_name++) {
    wert = GPIO_ReadInputDataBit(BUTTON[btn_name].BUTTON_PORT, BUTTON[btn_name].BUTTON_PIN);
    BUTTON[btn_name].BUTTON_AKT = wert;
  }
}


/*//exposition for different teeth, *20 ms
uint8_t UINC_TIME_S = 13;
uint8_t UINC_TIME_M = 16;
uint8_t UINC_TIME_L = 25;
uint8_t UPMO_TIME_S = 16;
uint8_t UPMO_TIME_M = 25;
uint8_t UPMO_TIME_L = 35;
uint8_t UMOL_TIME_S = 18;
uint8_t UMOL_TIME_M = 33;
uint8_t UMOL_TIME_L = 40;
uint8_t DINC_TIME_S = 12;
uint8_t DINC_TIME_M = 15;
uint8_t DINC_TIME_L = 24;
uint8_t DPMO_TIME_S = 15;
uint8_t DPMO_TIME_M = 20;
uint8_t DPMO_TIME_L = 30;
uint8_t DMOL_TIME_S = 18;
uint8_t DMOL_TIME_M = 25;
uint8_t DMOL_TIME_L = 35;*/

/*//film sensitivity factor(divide by 10)
uint8_t FILM_1 = 10;
uint8_t FILM_2 = 7;
uint8_t FILM_3 = 2;

//voltage correction (divide by 100)
uint8_t VOLT192 = 220;
uint8_t VOLT195 = 200;
uint8_t VOLT200 = 180;
uint8_t VOLT205 = 150;
uint8_t VOLT210 = 130;
uint8_t VOLT215 = 100;
uint8_t VOLT225 = 85;
uint8_t VOLT230 = 72;
uint8_t VOLT235 = 60;
uint8_t VOLT240 = 54;*/

//PREHEAT TIMES, ms
/*uint8_t PREHEAT192 = 145;
uint8_t PREHEAT200 = 125;
uint8_t PREHEAT210 = 105;
uint8_t PREHEAT230 = 85;
uint8_t PREHEAT240 = 65;*/
