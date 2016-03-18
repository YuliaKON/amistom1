#include "io.h"

void AdcInit(void)
//PC5
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//настройка DMA
	//Ацп работает без прерываний.
	//После завершения преобразования каждого канала ДМА помещает результат в кольцевой буфер

	DMA_DeInit(DMA2_Stream0 );
	DMA_InitStructure.DMA_Channel = 				DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = 		(uint32_t) 0x4001204C;
	DMA_InitStructure.DMA_Memory0BaseAddr = 		(uint32_t) &ADC_SampleValue;
	DMA_InitStructure.DMA_DIR = 					DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 				ADC_BUFFER_SIZE;//16
	DMA_InitStructure.DMA_PeripheralInc = 			DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc =				DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize =		DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = 			DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = 					DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = 				DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = 				DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = 			DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = 			DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = 		DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

    DMA_ITConfig(DMA2_Stream0, DMA_IT_HT | DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA2_Stream0, ENABLE);
//------------------------------------------------------------------------------------------
	// пины АЦП
	//PC5(chan15)
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_Init(GPIOC,
			&(GPIO_InitTypeDef ) { .GPIO_Pin = GPIO_Pin_5,
								   .GPIO_Mode = GPIO_Mode_AIN,
								   .GPIO_OType = GPIO_OType_PP, .GPIO_PuPd = GPIO_PuPd_NOPULL,
								   .GPIO_Speed = GPIO_Speed_50MHz, });


	//Настройка АЦП
	//Минимальное количество циклов для преобразования считается как разрешение + 3, для 12 bits: 3 + 12 = 15 ADCCLK cycles
	ADC_CommonInitStructure.ADC_Mode = 				ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = 		ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = 	ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = 	ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = 				ADC_Resolution_8b;

	ADC_InitStructure.ADC_ScanConvMode = 			ENABLE;//многократное преобразование
	ADC_InitStructure.ADC_ContinuousConvMode = 		ENABLE;//DISABLE;//преобразование не начинается после окончания предыдущего
	//ADC_InitStructure.ADC_ExternalTrigConvEdge =	ADC_ExternalTrigConvEdge_None;//начинать преобразование программно//ADC_ExternalTrigConvEdge_Falling;//использовать триггер
	ADC_InitStructure.ADC_ExternalTrigConv = 		ADC_ExternalTrigConvEdge_None;//ADC_ExternalTrigConv_T5_CC1;
	ADC_InitStructure.ADC_DataAlign = 				ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 		ADC_BUFFER_SIZE;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);

	ADC_DMACmd(ADC1, ENABLE);

//регулярные каналы для сканирования PC5
	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 	1,	 ADC_SampleTime_56Cycles );

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
}


//---------------------------------------------------------------------------------------------------

inline uint16_t read_abs(void)
{
	delay(1000);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//End of conversion flag
	return ADC_SampleValue[0];
}

uint16_t readADC1(void)//pc5
{
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_3Cycles);
  ADC_SoftwareStartConv(ADC1);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  return ADC_GetConversionValue(ADC1);
}

uint16_t InOut_adcStart (void)
{
	double d[ADC_BUFFER_SIZE];
	uint8_t i;
	ADC_SoftwareStartConv(ADC1);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//End Of Conversion
    for(i = 0; i <= ADC_BUFFER_SIZE; i++){
    d[i] = (double)ADC_SampleValue[i]/4096*3.3;// mV
    }
    return ADC_GetConversionValue(ADC1);
}
