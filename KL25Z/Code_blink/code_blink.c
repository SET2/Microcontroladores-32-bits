// LED Vermelho com catodo ligado em PTB18
unsigned int *simscg5 = (unsigned int*)0x40048038; //Ativação de perifericos GPIO (Reg. SIM_SCGC5)
unsigned int *pbpcr18 = (unsigned int*)0x4004A048; // MUX de PTB18 (Reg. PORTB_PCR18)
unsigned int *pbddr = (unsigned int*)0x400FF054; // Data direction do PORTB (Reg. GPIOB_PDDR)
unsigned int *pbtor = (unsigned int*)0x400FF04C; // Toggle register do PORTB (Reg. GPIOB_PTOR)

void pisca(void) {
	*pbtor = 0x00040000; // toggle no bit 18 do PORTB
}

void delay(unsigned int tempo) {
	for(; tempo !=0; --tempo);
}

int main(void)
{
	*simscg5 = *simscg5 | 0x00000400; // Ativa GPIO do PORTB
	*pbpcr18 = *pbpcr18 & 0xFFFFF8FF; // Zera bits de MUX de PTB18
	*pbpcr18 = *pbpcr18 | 0x00000100; // Seta bit 0 do MUX de PTB18, assim os bits de MUX serão ?001?
	*pbddr = *pbddr | 0x00040000; // Seta pino 18 do PORTB como saída

	for(;;) {
	   	pisca(); // Inverte estado do LED vermelho em PTB18
	   	delay(500000); // Espera um tempo
	}

}
