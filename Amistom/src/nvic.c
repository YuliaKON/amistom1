#include "nvic.h"

//void NVIC_conf(void){

		/*NVIC_SetPriorityGrouping(4);								//8 приоритетов и 2 подприоритета


// EXTI PE0 1 2 3
// BUTTOn

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1 | EXTI_PinSource0 | EXTI_PinSource2 | EXTI_PinSource3 );// прерывание на изменение состояние PEx

		EXTI_InitTypeDef extiPE0, extiPE1, extiPE2, extiPE3;
		NVIC_InitTypeDef nvicPE0, nvicPE1, nvicPE2, nvicPE3;

		extiPE0.EXTI_Line = 							EXTI_Line0;
		extiPE0.EXTI_Mode = 							EXTI_Mode_Interrupt;//прерывание, а не событие
		extiPE0.EXTI_Trigger = 							EXTI_Trigger_Falling;//по  фронту
		extiPE0.EXTI_LineCmd = 							ENABLE;
	    EXTI_Init(&extiPE0);

	    nvicPE0.NVIC_IRQChannel = 						EXTI0_IRQn;
	    nvicPE0.NVIC_IRQChannelPreemptionPriority = 	3;
	    nvicPE0.NVIC_IRQChannelSubPriority = 			1;
	    nvicPE0.NVIC_IRQChannelCmd = 					ENABLE;
	    NVIC_Init(&nvicPE0);

	    extiPE1.EXTI_Line = 							EXTI_Line1;
	    extiPE1.EXTI_Mode = 							EXTI_Mode_Interrupt;//прерывание, а не событие
	    extiPE1.EXTI_Trigger = 							EXTI_Trigger_Falling;//по  фронту
	    extiPE1.EXTI_LineCmd = 							ENABLE;
	    EXTI_Init(&extiPE1);

	    nvicPE1.NVIC_IRQChannel = 						EXTI1_IRQn;
	    nvicPE1.NVIC_IRQChannelPreemptionPriority = 	2;
	    nvicPE1.NVIC_IRQChannelSubPriority = 			0;
	    nvicPE1.NVIC_IRQChannelCmd = 					ENABLE;
	    NVIC_Init(&nvicPE1);

		extiPE2.EXTI_Line = 							EXTI_Line2;
		extiPE2.EXTI_Mode = 							EXTI_Mode_Interrupt;//прерывание, а не событие
		extiPE2.EXTI_Trigger = 							EXTI_Trigger_Falling;//по  фронту
		extiPE2.EXTI_LineCmd = 							ENABLE;
	    EXTI_Init(&extiPE2);

	    nvicPE2.NVIC_IRQChannel = 						EXTI2_IRQn;
	    nvicPE2.NVIC_IRQChannelPreemptionPriority = 	3;
	    nvicPE2.NVIC_IRQChannelSubPriority = 			0;
	    nvicPE2.NVIC_IRQChannelCmd = 					ENABLE;
	    NVIC_Init(&nvicPE2);

	    nvicPE3.NVIC_IRQChannel = 						EXTI3_IRQn;
	    nvicPE3.NVIC_IRQChannelPreemptionPriority = 	2;
	    nvicPE3.NVIC_IRQChannelSubPriority = 			1;
	    nvicPE3.NVIC_IRQChannelCmd = 					ENABLE;
	    NVIC_Init(&nvicPE3);

	    extiPE3.EXTI_Line = 							EXTI_Line3;
	    extiPE3.EXTI_Mode = 							EXTI_Mode_Interrupt;//прерывание, а не событие
	    extiPE3.EXTI_Trigger = 							EXTI_Trigger_Falling;//по  фронту
	    extiPE3.EXTI_LineCmd = 							ENABLE;
	    EXTI_Init(&extiPE3);
	    state_err=6*/;


//}
