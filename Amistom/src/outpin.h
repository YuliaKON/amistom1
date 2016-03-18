#ifndef OUTPIN_H_
#define OUTPIN_H_

#include "main.h"

void init_outpin(void);
void stop_diaph(void);
void open_iris(void);
void close_iris(void);
void right_shutter(void);
void left_shutter(void);
void open_shutter(void);
void close_shutter(void);
unsigned char Get_Debounced_0(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
unsigned char Get_Debounced_1(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif /* OUTPIN_H_ */
