#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char centenas=0;
unsigned char decenas=0;
unsigned char unidades=0;
unsigned char contador=0;
unsigned int numero=0;

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
  UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);
  UBRR0=103;
}