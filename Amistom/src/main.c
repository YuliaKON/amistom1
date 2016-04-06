#include "main.h"

double adc_value[ADC_BUFFER_SIZE];
uint16_t ADC_SampleValue[ADC_BUFFER_SIZE];
uint16_t voltage = 		0;
uint8_t mode_emit =		loading;
uint8_t imp_len = 		10; // *20 ms
uint8_t patSize =		1;
uint8_t filmType = 		1;
uint8_t pat_count = 	0;
uint8_t film_count = 	0;
char tooth_ch = 		0;
extern volatile uint16_t systick_ms;



_Bool b_Exp = 		0;
_Bool b_Plus = 		0;
_Bool b_Minus = 	0;
_Bool b_Film = 		0;
_Bool b_Safe = 		0;
_Bool b_Pat = 		0;
_Bool b_Uin = 		0;
_Bool b_Upm = 		0;
_Bool b_Umo = 		0;
_Bool b_Din = 		0;
_Bool b_Dpm = 		0;
_Bool b_Dmo = 		0;
_Bool beep = 		0;
_Bool mode_auto = 	0;


DI_TypeDef 			display;
MODE_TypeDef		mode_struct, struct_sample;

//----------------------------------------------------------------------------------------------------

inline void Initialization_All(void)
{
	init_outpin();
	AdcInit();
	GlobalTimerInit();
	Button_Init();
	init_meandr__gpio();
	init_meandr_timer();
	Init_Uart3();
	//TIM3_IRQHandler();

	NVIC_InitTypeDef NVIC_InitStructure_usart3;
			NVIC_InitStructure_usart3.NVIC_IRQChannel                   = USART3_IRQn;
			NVIC_InitStructure_usart3.NVIC_IRQChannelSubPriority        = 1;
			NVIC_InitStructure_usart3.NVIC_IRQChannelPreemptionPriority = 1;
			NVIC_InitStructure_usart3.NVIC_IRQChannelCmd                = ENABLE;
			NVIC_Init (&NVIC_InitStructure_usart3);

			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			//state_err=2;
			//USART_ITConfig(USART3, USART_IT_ERR,  ENABLE);
			USART_ITConfig(USART3, USART_IT_TC,   DISABLE);
//	NVIC_conf();
		 display.a.port =	 	  GPIOH;
		 display.b.port =	 	  GPIOC;
		 display.c.port =	 	  GPIOE;
		 display.d.port = 		  GPIOE;
		 display.e.port = 		  GPIOE;
		 display.f.port =	 	  GPIOE;
		 display.g.port = 		  GPIOB;
		 display.common[0].port = GPIOC;
		 display.common[1].port = GPIOC;
		 display.common[2].port = GPIOH;
		 display.dot.port = 	  GPIOB;

		 display.a.pin = 		GPIO_Pin_0;
		 display.b.pin = 		GPIO_Pin_14;
		 display.c.pin = 		GPIO_Pin_6;
		 display.d.pin = 		GPIO_Pin_4;
		 display.e.pin = 		GPIO_Pin_2;
		 display.f.pin = 		GPIO_Pin_0;
		 display.g.pin = 		GPIO_Pin_8;

		 display.common[0].pin = 	GPIO_Pin_13;
		 display.common[1].pin = 	GPIO_Pin_15;
		 display.common[2].pin = 	GPIO_Pin_1;
		 display.dot.pin = 			GPIO_Pin_6;

		 DI_Init(&display);
}

void SysTick_Handler (void){
	DI_TimerHandler(&display);
	++systick_ms;
}
//----------------------------------------------------------------------------------------------------
int main(void)
{
	Initialization_All();
	uint8_t pat_count, counter1, meandre_ok = 0;
	SysTick_Config(SystemCoreClock / 1000);//200000

	if (Button_test() == false) 					   state_err[4] = 0x04;		//button on test
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) state_err[6] = 0x06;		//LV1 error
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) state_err[8] = 0x08;		//LV2 error
	if (meandr_test(GPIOB, GPIO_Pin_0) == true)		   state_err[7] = 0x07;		//short-circuit K1
	if (meandr_test(GPIOB, GPIO_Pin_1) == true)		   {state_err[9] = 0x09;	//emission in process \/ monoblok isn't connected
	Emission(true); Beeper(true);}												//вкл индикатор излучение, вкл бипер

	Display(&display, struct_sample.voltage_correction*struct_sample.man_exposition*20);//длительность экспозиции мс


	//main loop
	while(1)
	{
		wait_label:

// while B_SAFE and B_FILM is ON, do get voltage and output to display
			if (Button_OnClick(B_SAFE) && Button_OnClick(B_FILM)) {
				DI_Display(&display, readADC1(), 0);
			}

		meandr_auto();

// Выбор пациента
			if(Button_OnClick(B_PAT) == 1)	++pat_count;

		    if (pat_count > 3)  pat_count = 1;
		    switch(pat_count) {
		    		    	case 1: {GPIO_SetBits(GPIOB, GPIO_Pin_3);	GPIO_ResetBits(GPIOD, GPIO_Pin_6);	GPIO_ResetBits(GPIOD, GPIO_Pin_4); \
		    		    	DI_Display(&display, 3, 0);\
		    		    	struct_sample.patient_type = PAT1;} break;
		    		    	case 2: {GPIO_ResetBits(GPIOB, GPIO_Pin_3);	GPIO_SetBits(GPIOD, GPIO_Pin_6);	GPIO_ResetBits(GPIOD, GPIO_Pin_4);\
		    		    	DI_Display(&display, 33, 0);\
		    		    	struct_sample.patient_type = PAT2;} break;
		    		    	case 3: {GPIO_ResetBits(GPIOB, GPIO_Pin_3);	GPIO_ResetBits(GPIOD, GPIO_Pin_6);	GPIO_SetBits(GPIOD, GPIO_Pin_4);\
		    		    	DI_Display(&display, 111, 0);\
		    		    	struct_sample.patient_type = PAT3;} break;
		    		    	default:{GPIO_ResetBits(GPIOB, GPIO_Pin_3);	GPIO_ResetBits(GPIOD, GPIO_Pin_6);	GPIO_ResetBits(GPIOD, GPIO_Pin_4);}	break;
		   }

//Выбор пленки
		    if(Button_OnClick(B_FILM) == 1)	++film_count;

		    if (film_count > 3)  film_count = 1;
		    switch(pat_count) {
		    		    		case 1: {GPIO_SetBits(GPIOA, GPIO_Pin_15);	GPIO_ResetBits(GPIOA, GPIO_Pin_13);	GPIO_ResetBits(GPIOA, GPIO_Pin_9);\
		    		    		struct_sample.film = FILM_1;} break;
		    		    		case 2: {GPIO_ResetBits(GPIOA, GPIO_Pin_15);GPIO_SetBits(GPIOA, GPIO_Pin_13);	GPIO_ResetBits(GPIOA, GPIO_Pin_9);\
		    		    		struct_sample.film = FILM_2;} break;
		    		    		case 3: {GPIO_ResetBits(GPIOA, GPIO_Pin_15);GPIO_ResetBits(GPIOA, GPIO_Pin_13);	GPIO_SetBits(GPIOA, GPIO_Pin_9);\
		    		    		struct_sample.film = FILM_3;} break;
		    		    		default:{GPIO_ResetBits(GPIOA, GPIO_Pin_15);GPIO_ResetBits(GPIOA, GPIO_Pin_13);	GPIO_ResetBits(GPIOA, GPIO_Pin_9);}	break;
		    }

// Кнопка безопасности
		    if(Button_OnClick(B_SAFE) == 1) {
		    		if (!b_Safe) {
		    			GPIO_SetBits(GPIOC, GPIO_Pin_9);
		    			b_Safe = 1;// safe
		    		}
		    		else if(b_Safe) {
		    		   GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		    		   b_Safe = 0;// safe
		    		}
		   	}


//buttons released
		    Button_OnClick(B_EXP)?  (b_Exp = 1):(b_Exp = 0);
		    Button_OnClick(B_PLUS)? (b_Plus = 1):(b_Plus = 0);
		    Button_OnClick(B_MINUS)?(b_Minus = 1):(b_Minus = 0);
		    Button_OnClick(B_FILM)? (b_Film = 1):(b_Film = 0);
		    Button_OnClick(B_UIN)? 	(b_Uin = 1):(b_Uin = 0);

		/*if (Button_OnClick(B_EXP) == 1)
			b_Exp = 1;
		if (Button_OnClick(B_PLUS) == 1)
			b_Plus = 1;
		if (Button_OnClick(B_MINUS) == 1)
			b_Minus = 1;
		if (Button_OnClick(B_FILM) == 1)
			b_Film = 1;
		if (Button_OnClick(B_UIN) == 1)
			b_Uin = 1;
*/
//Выбор зуба
		if (Button_OnClick(B_UPM) == 1){
			TOOTH_IND_ON('upm') ;
			struct_sample.tooth = UPM;
		}
		if (Button_OnClick( B_UMO) == 1){
			TOOTH_IND_ON('umo') ;
			struct_sample.tooth = UMO;
		}
		if (Button_OnClick(B_DIN) == 1){
			TOOTH_IND_ON('din') ;
			struct_sample.tooth = DIN;
		}
		if (Button_OnClick(B_DPM) == 1){
			TOOTH_IND_ON('dpm') ;
			struct_sample.tooth = DPM;
		}
		if (Button_OnClick(B_UIN) == 1){
			TOOTH_IND_ON('uin') ;
			struct_sample.tooth = UIN;
		}
		if (Button_OnClick(B_DMO) == 1){
			TOOTH_IND_ON('dmo') ;
			struct_sample.tooth = DMO;
		}

//====================================================================================
//		starting mode
//====================================================================================

		if (mode_emit == starting)
		{
            //ошибка при преждевременном отпускании кнопки экспозиции
			if (Button_OnClick(B_EXP) == 1){

				uint8_t i = 0;

				for(i = 0; i <= 5; i++){
					voltage += readADC1();
					delay_ms(20);
				}

				if ((voltage = voltage/i) < 2)//volt < 192V
				{state_err[1] = 0x01; mode_emit = idle; goto wait_label;}
				if ((voltage = voltage/i) > 3)//volt > 247V
				{state_err[2] = 0x02; mode_emit = idle; goto wait_label;}

				delay_ms(100);

				if (meandr_test(GPIOB, GPIO_Pin_0) == false)
				{state_err[1] = 0x01; mode_emit = idle; goto wait_label;}
				if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
				{state_err[6] = 0x06; mode_emit = idle; goto wait_label;}
				if (meandr_test(GPIOB, GPIO_Pin_1) == 1)
				{state_err[9] = 0x09; mode_emit = idle;
				Emission(true); Beeper(true);}//light ON, beeper ON

				if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 1)&(meandr_test(GPIOB, GPIO_Pin_0) == true))
				{mode_emit = emit;}

				}
			}




		//			starting mode

		if (mode_emit == emit)
		{
			Display(&display, struct_sample.voltage_correction);

				if (cntr_imp >= imp_len)
				{
				//	stopEmission();
					mode_emit = idle;
					goto wait_label;
				}


		}
	}//while(1)
}//main()

