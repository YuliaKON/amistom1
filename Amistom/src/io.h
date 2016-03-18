#ifndef INC_IO_H
#define INC_IO_H

#include "main.h"
#define ADC_BUFFER_SIZE 1

uint16_t ADC_SampleValue[ADC_BUFFER_SIZE];

void AdcInit(void);
uint16_t read_abs(void);
uint16_t readADC1(void);

#endif /*INC_IO_H*/
