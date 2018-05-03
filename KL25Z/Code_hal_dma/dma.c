#include "dma.h"

extern char ready;

void dma_init(void)
{
	ready = 0;	
	// Habilita o clocks do DMA
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	
	// Desabilita primeiro todos os DMA Mux channel
	DMAMUX0_CHCFG0 = 0x00;
	
	// Configure DMA
	DMA_SAR0 = (uint32_t)&ADC0_RA;      // Carrega o endereço (SOURCE) do buffer do conversor ADC no DMA
	DMA_DAR0 = (uint32_t)&value;        // Carrega o endereço (Destino) da variável Buffer;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(2);  // Informa quantos bytes será transferido por vez. 
										// Neste caso, 2 bytes (16 bits) por vez.
	DMA_DCR0 |= (DMA_DCR_EINT_MASK|		// Habilita a interrupt do DMA (acionada a cada transferencia realizada)
				 DMA_DCR_ERQ_MASK |		// Habilita peripheral request, ou seja, quem vai disparar a transferencia
										// será um periférico. Podemo também usar o bit de START.
				 DMA_DCR_CS_MASK  |     // Forces a single read/write transfer per request. 
				 DMA_DCR_SSIZE(2) |		// Set source size to 16 bits
				 DMA_DCR_DINC_MASK|		// Set increments to destination address
				 DMA_DCR_DMOD(1)  |     // Destination address modulo of 16 bytes
				 DMA_DCR_DSIZE(2));		// Set destination size of 16 bits 
				 
	
	// Enable DMA channel and source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(40); // Enable DMA channel and set ADC0 as source	
	// Habilita a Interrupção do DMA
	NVIC_EnableIRQ(DMA0_IRQn);
}

/*
 * Handles DMA0 interrupt
 * Resets the BCR register and clears the DONE flag
 * */
void DMA0_IRQHandler(void)
{
	/* Enable DMA0*/ 
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(2);		// Set byte count register
	ready += 1;
}
