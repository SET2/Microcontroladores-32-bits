#include "MKL25Z4.h" 
#include "adc.h"
#include "pit.h"
#include "dma.h"

uint16_t  value[8];
extern char ready;

int main(void)
{
	int i, avg;
	avg = 0;
	ready = 0;

	dma_init();
	adc_init();
	pit_init();

	for(;;)
	{
		if(ready > ADC_READS)
		{
			for(i = 0; i < ADC_READS; i++)
				avg += value[i];
			avg /= ADC_READS;

			ready = 0;
		}
	}

	return 0;
}
