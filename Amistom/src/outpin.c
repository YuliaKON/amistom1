#include "outpin.h"

GPIO_InitTypeDef OutBit_InitStruct;

void init_outpin(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		//A

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_0;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_UP;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &OutBit_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);		//B

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_8;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &OutBit_InitStruct);

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_1|GPIO_Pin_4;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_UP;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &OutBit_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);		//C

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_6;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &OutBit_InitStruct);

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_UP;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &OutBit_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		//D

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &OutBit_InitStruct);

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_UP;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &OutBit_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);		//E

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &OutBit_InitStruct);

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_7;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_IN;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_UP;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &OutBit_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);		//H

	OutBit_InitStruct.GPIO_Pin = 			GPIO_Pin_0|GPIO_Pin_1;
	OutBit_InitStruct.GPIO_Mode =			GPIO_Mode_OUT;
	OutBit_InitStruct.GPIO_OType = 			GPIO_OType_PP;
	OutBit_InitStruct.GPIO_PuPd = 			GPIO_PuPd_DOWN;
	OutBit_InitStruct.GPIO_Speed = 			GPIO_Speed_50MHz;
	GPIO_Init(GPIOH, &OutBit_InitStruct);

}

unsigned char Get_Debounced_0(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	signed char counter = 10;
	while (--counter > 0)
	{
		if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)) return 1;
		delay_ms(2);
	}
	return 0;
}

unsigned char Get_Debounced_1(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	signed char counter = 10;
	while (--counter > 0)
	{
		if (!GPIO_ReadInputDataBit(GPIOx, GPIO_Pin)) return 0;
		delay_ms(2);
	}
	return 1;
}

void displayDigit(uint8_t pos, uint8_t chr)
{
	/*
	  A
	 ----
   F| G  |B
     ----
   E|    |C
     ----  *
      D     H(d. dot)

	*/
	switch (pos)
	{
	case 1:
	{
		GPIO_ResetBits(GPIOH, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
	break;
	case 2:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_1);
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
	break;
	case 3:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_1);
		GPIO_SetBits(GPIOC, GPIO_Pin_15);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	break;
	}

	switch(chr)
	{
	case 0:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_SetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 1:
	{
		GPIO_ResetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_ResetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_ResetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 2:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_ResetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_SetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_ResetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 3:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_ResetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 4:
	{
		GPIO_ResetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_ResetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 5:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_ResetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 6:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_ResetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_SetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 7:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_ResetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_ResetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 8:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_SetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 9:
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_SetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_SetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case 'e':
	{
		GPIO_SetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_ResetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_ResetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_SetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_SetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_SetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_SetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_ResetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;
	case '.':
	{
		GPIO_ResetBits(GPIOH, GPIO_Pin_0); //A
		GPIO_ResetBits(GPIOC, GPIO_Pin_14); //B
		GPIO_ResetBits(GPIOE, GPIO_Pin_6); //C
		GPIO_ResetBits(GPIOE, GPIO_Pin_4); //D
		GPIO_ResetBits(GPIOE, GPIO_Pin_2); //E
		GPIO_ResetBits(GPIOE, GPIO_Pin_0); //F
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //G
		GPIO_SetBits(GPIOB, GPIO_Pin_6); //H
	}
	break;

	}

}//displaydigit()

