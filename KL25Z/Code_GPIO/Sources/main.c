/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "stdint.h"

/*
void Delay(int time)
{
	for(int i = 0; i < time; i++){};
}*/

volatile uint32_t ticks;

void SysTick_Handler (void)
{
	ticks++;
}

void _delay_ms(unsigned int TicksIn_mS)
{
	unsigned int DelayTimerTick = ticks;

	while((ticks - DelayTimerTick) < TicksIn_mS);
}


int main(void)
{
    /* Write your code here */
	static unsigned char step;

	SystemInit();

	/* Generate interrupt each 1 ms */
	SysTick_Config(SystemCoreClock/1000);

	// Habilita o clock do port B
	SIM_SCGC5 |=	SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	PORTB_PCR18 = 	PORT_PCR_MUX(1) 	| // GPIO digital
					PORT_PCR_DSE_MASK 	| // Config. de corrente
					PORT_PCR_PE_MASK 	| // Habilita o circuito de Pull
					PORT_PCR_PS_MASK	; // Pull-up

	PORTB_PCR19 = 	PORT_PCR_MUX(1) 	| // GPIO digital
					PORT_PCR_DSE_MASK 	| // Config. de corrente
					PORT_PCR_PE_MASK 	| // Habilita o circuito de Pull
					PORT_PCR_PS_MASK	; // Pull-up

	PORTD_PCR1 = 	PORT_PCR_MUX(1) 	| // GPIO digital
					PORT_PCR_DSE_MASK 	| // Config. de corrente
					PORT_PCR_PE_MASK 	| // Habilita o circuito de Pull
					PORT_PCR_PS_MASK	; // Pull-up

	//Configura como saída.
	GPIOB_PDDR |= (1 << 18);
	GPIOB_PDDR |= (1 << 19);
	GPIOD_PDDR |= (1 << 1);

	//Seta o pino;
	//GPIOB_PSOR |= (1<<18);
	step = 0;

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for(;;)
    {
    	switch(step)
    	{
			case 0:	GPIOB_PSOR |= (1 << 18);
					GPIOB_PSOR |= (1 << 19);
					GPIOD_PSOR |= (1 << 1);

					step++;
					break;

			case 1: GPIOB_PSOR |= (1 << 18);
					GPIOB_PSOR |= (1 << 19);
					GPIOD_PSOR |= (1 << 1);

					GPIOB_PCOR |= (1 << 18);
					step++;
					break;

			case 2: GPIOB_PSOR |= (1 << 18);
					GPIOB_PSOR |= (1 << 19);
					GPIOD_PSOR |= (1 << 1);

					GPIOB_PCOR |= (1 << 19);
					step++;
					break;

			case 3:	GPIOB_PSOR |= (1 << 18);
					GPIOB_PSOR |= (1 << 19);
					GPIOD_PSOR |= (1 << 1);

					GPIOD_PCOR |= (1 << 1);
					step = 0;
					break;

			default: break;
    	}

    	_delay_ms(1000);
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
