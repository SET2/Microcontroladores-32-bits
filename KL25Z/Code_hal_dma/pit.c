#include "pit.h"

void pit_init(void)
{
	// Habilita PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable Green LED clock and MUX
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB_PCR19 = PORT_PCR_MUX(1);
	GPIOB_PDDR |= (1 << LED_GREEN);
	GPIOB_PSOR |= (1 << LED_GREEN);
	
	// Turn on PIT
	PIT_MCR = 0;
	
	// Inicializa o TIMER PIT para gerar uma interrupção a cada 1 segundo
	PIT_LDVAL0 = 0x1312CFF;	// 1/20Mhz = 50ns   (1s/50ns)-1= 19,999,999 cycles or 0x1312CFF
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; // Enable interrupt and enable timer
	
	// Enable interrupt registers ISER and ICPR
	NVIC_EnableIRQ(PIT_IRQn);
}

/*	Handles PIT interrupt if enabled
 * 
 * 	Starts conversion in ADC0 with single ended channel 8 (PTB0) as input
 * 
 * */
void PIT_IRQHandler(void)
{	
	// Apaga o flag de interrupt do TIMER PIT
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	
	// Write to SC1A to start conversion with channel 8 PTB0
	ADC0_SC1A = (ADC_SC1_ADCH(ADC_CHANNEL) | 
				 (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));  
	
	// Toggle Green LED a cada 1 segundo
	GPIOB_PTOR = (1 << LED_GREEN);
}
