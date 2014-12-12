/*
 * main.cpp
 *
 *  Created on: 7 paü 2014
 *      Author: Dominik
 */

#include "SterownikLED.h"
#include "HCS04.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile uint8_t wypelnienie_R;
volatile uint8_t wypelnienie_G;
volatile uint8_t wypelnienie_B;

volatile uint8_t aktualna_wartosc;

volatile double licznik=0;
volatile uint8_t flaga=0;
volatile uint8_t odl0=0;

static void uart_9600(void) {
#define BAUD 9600
#include <util/setbaud.h>
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
#if USE_2X
    UCSRA |= (1 << U2X);
#else
    UCSRA &= ~(1 << U2X);
#endif
}

static void uart_init(void) {
    uart_9600();
    UCSRC = _BV(URSEL) | (1 << UCSZ0) | (1 << UCSZ1) | _BV(USBS); //2 bity stopu ; 8 bitÛw informacji
    UCSRB = _BV(TXEN) | _BV(RXEN) | _BV(RXCIE); // uruchomienie TX,RX i przerwania w RX
}

uint8_t rec_uart(void) {
    while (!(UCSRA & _BV(RXC)));
    return UDR;
}

void send_uart(char byte) {
    while (!(UCSRA & _BV(UDRE)));
    UDR = byte;
}

void send_uart_text(char str[]) {
    unsigned char i = 0;
    for (i = 0; str[i] != '\0'; i++)
        send_uart(str[i]);
}



int main(void) {
	char wynik[]="           ";//bufor tekstowy, wyczyszczenie bufora
	SterownikLED sterownikLED;
	HCS04 hcs04;
	sterownikLED.ustawRejestryDDRC();
	sterownikLED.ustawRejestryTimer0();

	hcs04.InitInterrupt();

	//uart_init();
	sei();

	while (true) {
		hcs04.pomiar();
		sterownikLED.ustawSwiatlo(odl0,wypelnienie_R,wypelnienie_G,wypelnienie_B);

		//sprintf(wynik,"%d [cm]",odl0);
		//send_uart_text(wynik);
		_delay_ms(100);

	}

	return 1;
}











ISR(TIMER0_OVF_vect) {
	aktualna_wartosc++;
	if (aktualna_wartosc > 255) {
		aktualna_wartosc = 0;
	}
	if (aktualna_wartosc < wypelnienie_B) {
		PORTC |= (1 << LED_B);
	} else if (aktualna_wartosc >= wypelnienie_B) {
		PORTC &= ~(1 << LED_B);
	}
	if (aktualna_wartosc < wypelnienie_R) {
		PORTC |= (1 << LED_R);
	} else if (aktualna_wartosc >= wypelnienie_R) {
		PORTC &= ~(1 << LED_R);
	}
	if (aktualna_wartosc < wypelnienie_G) {
		PORTC |= (1 << LED_G);
	} else if (aktualna_wartosc >= wypelnienie_G) {
		PORTC &= ~(1 << LED_G);
	}
}


//F-cja przerwania od Timera2
ISR(TIMER2_COMP_vect)
{
    licznik++;
}

//F-cja przerwania zewnÍtrznego INT0
ISR(INT1_vect)
{
    if(flaga==0)
    {
        TIMSK |= (1<<OCIE2);                //w≥πcza Timer2 w trybie dopasowania (START)

        ClrBit(GICR, INT1);

        MCUCR = 0x00;                        //The falling edge of INT0 generates an interrupt request.
        MCUCR = (1<<ISC11);

        SetBit(GICR, INT1);

        flaga=1;
    }

    else if(flaga==1)
    {
        TIMSK &=~(1<<OCIE2);                //zatrzymuje Timer2 (STOP)

        ClrBit(GICR, INT1);

        MCUCR = 0x00;                        //Przerwanie zostanie wywo≥ane zboczem rosnπcym
        MCUCR = (1<<ISC11)|(1<<ISC10);        //na wejúciu INT0

       SetBit(GICR, INT1);

        odl0=licznik;                        //Zapisuje wartoúÊ licznika do zmiennej "odl"
       /* odl0/=58;*/
 //odl0=(odl0*100/4)/25;                    //oraz skaluje go

        licznik=0;                            //Zerowanie licznika
        flaga=0;

    }
}


