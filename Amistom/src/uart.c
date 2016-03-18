 #include "uart.h"
 #include "stm32f4xx_usart.h"

//---------------------------------------------------------------------------------------------------
char StringLoop[3], chr;
uint8_t bytesToSend = 8, sendDataCounter = 0;
unsigned int data;
uint8_t tempByte = 0;
uint8_t hbyte = 0;
uint8_t lbyte = 0;
//extern uint16_t period;


_Bool recData = 0;
_Bool recFilL = 0;
_Bool recFilH = 0;
_Bool recImpL = 0;
_Bool recImpH = 0;

//---------------------------------------------------------------------------------------------------
void Init_Uart3(void)
{
	GPIO_InitTypeDef 		GPIO_InitStructure_usart3;
	USART_InitTypeDef 		USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 				UART_BAUDRATE;
	USART_InitStructure.USART_WordLength = 				USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = 				USART_StopBits_1;
	USART_InitStructure.USART_Parity = 					USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = 	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = 					USART_Mode_Rx | USART_Mode_Tx;

	//configure clock for USART
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	//configure clock for GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//configure AF
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3);

  //configure ports, &GPIO_InitStructure);
	GPIO_InitStructure_usart3.GPIO_OType = 		GPIO_OType_PP;
	GPIO_InitStructure_usart3.GPIO_PuPd = 		GPIO_PuPd_UP;
	GPIO_InitStructure_usart3.GPIO_Mode = 		GPIO_Mode_AF;

	GPIO_InitStructure_usart3.GPIO_Pin = 		GPIO_Pin_8;
	GPIO_InitStructure_usart3.GPIO_Speed = 		GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure_usart3);

	GPIO_InitStructure_usart3.GPIO_Mode =		GPIO_Mode_AF;
	GPIO_InitStructure_usart3.GPIO_Pin = 		GPIO_Pin_9;
	GPIO_Init(GPIOD, &GPIO_InitStructure_usart3);

	USART_Init(USART3, &USART_InitStructure);

	// Enable USART
	NVIC_EnableIRQ(USART3_IRQn);
	USART_Cmd(USART3, ENABLE);
}

//---------------------------------------------------------------------------------------------------

void USART3_IRQHandler(void)
{
	static int tx_index = 0;
	static int rx_index = 0;
	static int a = 0;
	extern uint16_t period;


	if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
	{
		USART_SendData(USART3, StringLoop[tx_index++]);
		if (tx_index >= (sizeof(StringLoop) - 1))
			tx_index = 0;
	}



	if(USART3->SR & USART_SR_RXNE)
	{
		chr = USART3->DR;
		switch(chr){
 case 'V':
			{
				send_int_Usart( meandr_capture()+2);
			}
			break;
 default: {send_int_Usart('a');}
 break;
}
}
//------------------------------------------------------------------------------------------------------


	if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
	{
		sendDataCounter++;
		if  (sendDataCounter == bytesToSend)
		{
			sendDataCounter = 0;
		}
	}
}


//---------------------------------------------------------------------------------------------------


void send_Uart(USART_TypeDef* USARTx, unsigned char c)

{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)== RESET){}
	USART_SendData(USARTx, c);
}



void Usart3_Send_String(char* str)
{
	for(uint8_t i = 0; str[i]; i++)
	{
		while(!USART_GetFlagStatus(USART3,USART_FLAG_TC));
		USART_SendData(USART3,str[i]);
	}
}


//---------------------------------------------------------------------------------------------------

//	Р В Р вЂ Р РЋРІР‚в„–Р В Р вЂ Р В РЎвЂўР В РўвЂ�Р В РЎвЂ�Р В РЎпїЅ Р РЋРІР‚РЋР В РЎвЂ�Р РЋР С“Р В Р’В»Р В РЎвЂў Р В Р вЂ  UART

void send_int_Usart(long c)
{
	unsigned long d=10000;
	char temp,flag=0;
	do
	{
		c=c%d;
		d=d/10;
		temp=c/d;
		if(temp!=0)
			flag=1;
		if(flag==1)
			send_Uart(USART3,temp+'0');
	}
	while(d>1);
}

//---------------------------------------------------------------------------------------------------
unsigned char getch_Uart(USART_TypeDef* USARTx)
{
	while (USART_GetFlagStatus(USARTx,USART_FLAG_RXNE) == RESET){}
	return USART_ReceiveData(USARTx);
}

//---------------------------------------------------------------------------------------------------

//	Р В Р’В§Р В РЎвЂ�Р РЋРІР‚С™Р В Р’В°Р В Р’ВµР В РЎпїЅ Р РЋРІР‚РЋР В РЎвЂ�Р РЋР С“Р В Р’В»Р В РЎвЂў (Р В Р вЂ  ASCII) Р РЋР С“ UART. Р В РЎС™Р В Р’В°Р В РЎвЂќР РЋР С“Р В РЎвЂ�Р В РЎпїЅР В Р’В°Р В Р’В»Р РЋР Р‰Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В Р вЂ  8 Р В Р’В·Р В Р вЂ¦Р В Р’В°Р В РЎвЂќР В РЎвЂўР В Р вЂ .
//	Р В РІР‚вЂќР В Р’В°Р В Р вЂ Р В Р’ВµР РЋР вЂљР РЋРІвЂљВ¬Р В Р’ВµР В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ Р В Р вЂ Р В Р вЂ Р В РЎвЂўР В РўвЂ�Р В Р’В° Р В РЎвЂ”Р В РЎвЂў Р В Р вЂ Р В Р вЂ Р В РЎвЂўР В РўвЂ�Р РЋРЎвЂњ Р В Р’В»Р РЋР вЂ№Р В Р’В±Р В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р вЂ¦Р В Р’Вµ Р РЋРІР‚В Р В РЎвЂ�Р РЋРІР‚С›Р РЋР вЂљР В РЎвЂўР В Р вЂ Р В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р РЋР С“Р В РЎвЂ�Р В РЎпїЅР В Р вЂ Р В РЎвЂўР В Р’В»Р В Р’В°

long USART_Read_int(void)
{
	unsigned char temp = 0, index = 0, flag = 0;
	long value=0;

	temp=getch_Uart(USART3);

	if(temp == '-')
	{
		flag=1;
		temp=getch_Uart(USART3);
		index++;
	}
	do
	{
		index++;
		if((47 < temp)&&(temp < 58))
		{
			value=value*10+temp-48;
		}
		else
		{
			index=255;
		}
		if(index < 3)
		{
			temp=getch_Uart(USART3);
		}
	}while(index<7);

	if(flag==1)
	{
		value=-value;
	}

	return value;
}
