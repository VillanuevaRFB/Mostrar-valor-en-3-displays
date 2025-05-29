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

ISR(USART_RX_vect){
  unsigned char dato=UDR0;
  if(dato>='0'&&dato<='9'){
    numero=numero*10+(dato-'0');
    contador++;

    if(contador==3){
      centenas=numero/100;
      decenas=(numero/10)%10;
      unidades=numero%10;
      contador=0;
      numero=0;
    }
  }
  else{
    contador=0;
    numero=0;
  }
}

void mostrar_display(unsigned char valor, unsigned char digito){
  PORTB|=0x07;
  PORTD=(PORTD&0x0F)|(valor<<4);
  PORTB&=~(1<<digito);
  _delay_ms(5);
  PORTB|=0x07;
}

int main(void){
  DDRD|=0xF0;
  DDRB|=0x07;
  config_USART();
  sei();
  while(1){
    mostrar_display(unidades,0);
    mostrar_display(decenas,1);
    mostrar_display(centenas,2);
  }
}