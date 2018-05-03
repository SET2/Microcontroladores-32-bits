#ifndef ADC_H_
#define ADC_H_

#include "MKL25Z4.h"

/* Prototypes */
void adc_init(void);
int adc_cal(void);
unsigned short adc_read(unsigned char ch);

#endif /* ADC_H_ */
