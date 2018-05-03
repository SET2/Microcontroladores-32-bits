#define F_CPU 16000000UL	// Define a frequ�ncia do microcontrolador
#include <avr/io.h>		// Biblioteca para o uso dos IOs do MCU
#include <util/delay.h>		// Biblioteca para o uso das rotinas de delay

void ConfigMCU()
{
	DDRB = 0XFF;           //Configura todos os pinos do PORTB como sa�da 
	PORTB = 0;             //Todo o PORTB ter� n�vel l�gico zero.
}

int main(void)
{
    ConfigMCU(); 
    while (1) 
    {
		 PORTB ^= 0xFF;   //Toggle, ou seja, inverte dos os pinos do PORTB;
		 _delay_ms(50);  //Delay de 300ms  	  
    }
}



