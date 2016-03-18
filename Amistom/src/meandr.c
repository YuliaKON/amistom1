/*
 * meandr.c
 *
 *  Created on: 20 Ğ¾ĞºÑ‚. 2015 Ğ³.
 *      Author: Yulia
 */

#include "meandr.h"


volatile uint16_t 		systick_ms;
uint16_t 				capture1, 	capture2;
volatile uint16_t 	 	capture_is_first = 1, capture1_is_first = 1, capture2_is_first = 1, capture_is_ready = 0, capture1_is_ready = 0, capture2_is_ready = 0;
uint16_t 	    		_period, _periodB0, _periodB1;
extern MODE_TypeDef		struct_sample;//
		// uint16_t period;


void meandr_auto(void){

	/* Êàæäûå 10 ìèëëèñåêóíäû ìåíÿåì óğîâåíü íà íîæêå íà ïğîòèâîïîëîæíûé,
	       òàê ÷òî ïåğèîä èìïóëüñîâ áóäåò ğàâåí 20 ìñ. */
    static uint32_t toggle_ms = 0;
    if (uint16_time_diff(systick_ms, toggle_ms) >= 10)
    {
      toggle_ms = systick_ms;
      GPIO_Write(GPIOB, GPIO_ReadOutputData(GPIOB) ^ GPIO_Pin_7);
    }
}

uint16_t meandrB0_capture(void){

	static uint16_t _periodB0;
    if (capture1_is_ready)
    {
      NVIC_DisableIRQ(TIM3_IRQn);
      capture1_is_ready = 0;

      /* Îáğàáàòûâàåì çàõâà÷åííûé ïåğèîä, êîòîğûé äîëæåí áûòü ğàâåí 20ìñ */
   // const uint16_t  period = uint16_time_diff(capture2, capture1);
      _periodB0 = uint16_time_diff(capture2, capture1);
    // PERIOD;
      // ...

      NVIC_EnableIRQ(TIM3_IRQn);
    }
    return(_periodB0);
}

uint16_t meandrB1_capture(void){

	static uint16_t _periodB1;
    if (capture2_is_ready)
    {
      NVIC_DisableIRQ(TIM3_IRQn);
      capture2_is_ready = 0;

      /* Îáğàáàòûâàåì çàõâà÷åííûé ïåğèîä, êîòîğûé äîëæåí áûòü ğàâåí 146 */
    const uint16_t  period = uint16_time_diff(capture2, capture1);
    _periodB1 = period;
      // ...

      NVIC_EnableIRQ(TIM3_IRQn);
    }
    return(_periodB1);
}


uint16_t meandr_capture(void){
	uint16_t period = 0;
	//period = uint16_time_diff(1000, 700);
    if (capture_is_ready)
    {
      NVIC_DisableIRQ(TIM3_IRQn);
      capture_is_ready = 0;

      /* ĞĞ±Ñ€Ğ°Ğ±Ğ°Ñ‚Ñ‹Ğ²Ğ°ĞµĞ¼ Ğ·Ğ°Ñ…Ğ²Ğ°Ñ‡ĞµĞ½Ğ½Ñ‹Ğ¹ Ğ¿ĞµÑ€Ğ¸Ğ¾Ğ´, ĞºĞ¾Ñ‚Ğ¾Ñ€Ñ‹Ğ¹ Ğ´Ğ¾Ğ»Ğ¶ĞµĞ½ Ğ±Ñ‹Ñ‚ÑŒ Ñ€Ğ°Ğ²ĞµĞ½ 146 */
     period = uint16_time_diff(capture1, capture2);
    _period = period;
      // ...

      NVIC_EnableIRQ(TIM3_IRQn);
    }
    return(period);
}

void init_meandr__gpio(void)
{
  GPIO_InitTypeDef OutBit_InitStruct ;

  /* Ğ’Ñ‹Ğ²Ğ¾Ğ´ Ñ‚ĞµÑÑ‚Ğ¾Ğ²Ğ¾Ğ³Ğ¾ ÑĞ¸Ğ³Ğ½Ğ°Ğ»Ğ° Ğ½Ğ° PB7 */

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		//B

  	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_7;
  	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
  	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
  	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
  	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &OutBit_InitStruct);

  /* Ğ¢Ğ°Ğ¹Ğ¼ĞµÑ€ TIM3, ĞºĞ°Ğ½Ğ°Ğ» 1 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_1|GPIO_Pin_0;
  OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
  OutBit_InitStruct.GPIO_OType = 		GPIO_OType_PP;
  OutBit_InitStruct.GPIO_PuPd = 		GPIO_PuPd_NOPULL;
  OutBit_InitStruct.GPIO_Speed = 		GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &OutBit_InitStruct);
}

void init_meandr_timer(void)
{
  /* ĞŸĞ¾Ğ´Ğ°Ñ‘Ğ¼ Ñ‚Ğ°ĞºÑ‚Ñ‹ Ğ½Ğ° TIM3 */
  RCC_AHB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* ĞĞ°ÑÑ‚Ñ€Ğ°Ğ¸Ğ²Ğ°ĞµĞ¼ Ğ¿Ñ€ĞµĞ´Ğ´ĞµĞ»Ğ¸Ñ‚ĞµĞ»ÑŒ Ñ‚Ğ°Ğº, Ñ‡Ñ‚Ğ¾Ğ±Ñ‹ Ñ‚Ğ°Ğ¹Ğ¼ĞµÑ€ ÑÑ‡Ğ¸Ñ‚Ğ°Ğ» Ğ¼Ğ¸Ğ»Ğ»Ğ¸ÑĞµĞºÑƒĞ½Ğ´Ñ‹ */
  TIM_TimeBaseInitTypeDef timer_base;
  TIM_TimeBaseStructInit(&timer_base);
  timer_base.TIM_Prescaler = 24000 - 1;
  //timer_base.TIM_Period = 10;
  TIM_TimeBaseInit(TIM3, &timer_base);

  TIM_ICInitTypeDef 			timer_ic;
  timer_ic.TIM_Channel = 		TIM_Channel_3;
  timer_ic.TIM_ICPolarity = 	TIM_ICPolarity_Falling;
  timer_ic.TIM_ICSelection =	TIM_ICSelection_DirectTI;
  timer_ic.TIM_ICPrescaler = 	TIM_ICPSC_DIV1;
  timer_ic.TIM_ICFilter = 		0;
  TIM_ICInit(TIM3, &timer_ic);

  /* Ğ Ğ°Ğ·Ñ€ĞµÑˆĞ°ĞµĞ¼ Ñ‚Ğ°Ğ¹Ğ¼ĞµÑ€Ñƒ Ğ³ĞµĞ½ĞµÑ€Ğ¸Ñ€Ğ¾Ğ²Ğ°Ñ‚ÑŒ Ğ¿Ñ€ĞµÑ€Ñ‹Ğ²Ğ°Ğ½Ğ¸Ğµ Ğ¿Ğ¾ Ğ·Ğ°Ñ…Ğ²Ğ°Ñ‚Ñƒ */
  TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);
  NVIC_SetPriority(TIM3_IRQn, 1);
  /* Ğ’ĞºĞ»ÑÑ‡Ğ°ĞµĞ¼ Ñ‚Ğ°Ğ¹Ğ¼ĞµÑ€ */
  TIM_Cmd(TIM3, ENABLE);
  /* Ğ Ğ°Ğ·Ñ€ĞµÑˆĞ°ĞµĞ¼ Ğ¿Ñ€ĞµÑ€Ñ‹Ğ²Ğ°Ğ½Ğ¸Ñ Ñ‚Ğ°Ğ¹Ğ¼ĞµÑ€Ğ° TIM3 */
  NVIC_EnableIRQ(TIM3_IRQn);
}

bool meandr_test(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if (average_period(GPIOB, GPIO_Pin) == 20) return(true);
	return(false);
}

/*void TIM3_IRQHandler(void)
{
if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)
{
 Äà¸ì çíàòü, ÷òî îáğàáîòàëè ïğåğûâàíèå
TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
N5=TIM_GetCapture3(TIM5);
nimp++;
if(nimp==1)
Nfirst = N5;
//Nlast= TIM_GetCapture3(TIM5);
 Òóò êàê-íèáóäü îáğàáàòûâàåì ñîáûòèå over-capture, åñëè ïğîâîğîíèì

}
}*/


void TIM3_IRQHandler(void)
{

extern uint16_t capture1, capture2;

  if (1/*TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET*/)
  {

    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);


    capture1 = capture2;
    capture2 = 1000;//TIM_GetCapture3(TIM3);


    if (!capture_is_first)
      capture_is_ready = 1;

    capture_is_first = 0;


    if (TIM_GetFlagStatus(TIM3, TIM_FLAG_CC3OF) != RESET)
    {
      TIM_ClearFlag(TIM3, TIM_FLAG_CC3OF);
      // ...
    }
  }

}


/* Ğ’Ñ‹Ñ‡Ğ¸ÑĞ»ÑĞµÑ‚ Ñ€Ğ°Ğ·Ğ½Ğ¾ÑÑ‚ÑŒ Ğ²Ğ¾ Ğ²Ñ€ĞµĞ¼ĞµĞ½Ğ¸ Ñ ÑƒÑ‡Ñ‘Ñ‚Ğ¾Ğ¼ Ğ¿ĞµÑ€ĞµĞ¿Ğ¾Ğ»Ğ½ĞµĞ½Ğ¸Ñ ÑÑ‡Ñ‘Ñ‚Ñ‡Ğ¸ĞºĞ° Ñ‚Ğ°Ğ¹Ğ¼ĞµÑ€Ğ° */
uint16_t uint16_time_diff(uint16_t now, uint16_t before)
{
  return (now >= before) ? (now - before) : (UINT16_MAX - before + now);
}


uint16_t average_period(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint16_t Period = 0;
	signed char counter = 5;
	while (--counter > 0)
	{
		if (GPIO_Pin == GPIO_Pin_0) Period += meandrB0_capture();
		if (GPIO_Pin == GPIO_Pin_1) Period += meandrB1_capture();
	}

	return(Period/5);
}


//Ïîïğàâî÷íûå êîıôôèöèåíòû äëÿ íàïğÿæåíèÿ ïèòàíèÿ//
VOLT_t exposition_count(void)
{
	signed char counter = 0;
	VOLT_t voltage_correction = 0;
	uint16_t current_voltage = readADC1();
	if(current_voltage > 512) // (3,3/4096)*512 = 0,4125V;
	for(counter = 0; counter >= 55; counter++){

		if ((current_voltage >= counter+192)&(current_voltage < counter+195)) voltage_correction = volt192_195;
		if ((current_voltage >= counter+195)&(current_voltage < counter+200)) voltage_correction = volt195_200;
		if ((current_voltage >= counter+200)&(current_voltage < counter+205)) voltage_correction = volt200_205;
		if ((current_voltage >= counter+205)&(current_voltage < counter+210)) voltage_correction = volt205_210;
		if ((current_voltage >= counter+210)&(current_voltage < counter+215)) voltage_correction = volt210_215;
		if ((current_voltage >= counter+215)&(current_voltage < counter+225)) voltage_correction = volt215_225;
		if ((current_voltage >= counter+225)&(current_voltage < counter+230)) voltage_correction = volt225_230;
		if ((current_voltage >= counter+230)&(current_voltage < counter+235)) voltage_correction = volt230_235;
		if ((current_voltage >= counter+235)&(current_voltage < counter+240)) voltage_correction = volt235_240;
		if ((current_voltage >= counter+240)&(current_voltage < counter+247)) voltage_correction = volt240_247;
	}
	return (voltage_correction);
	}
