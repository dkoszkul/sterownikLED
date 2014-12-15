/*
 * main.cpp
 *
 *  Created on: 7 paŸ 2014
 *      Author: Dominik
 */

#include "SterownikLED.h"
#include "HCS04.h"
#include "Uart.h"
#include "Buzzer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

volatile uint8_t wypelnienie_R;
volatile uint8_t wypelnienie_G;
volatile uint8_t wypelnienie_B;
volatile uint8_t aktualna_wartosc;
volatile uint8_t flaga = 0;
volatile uint8_t odl0 = 0;
volatile double licznik = 0;
volatile uint8_t licz = 0;
volatile uint8_t buzzer_value = 5;
volatile bool buzzerON = true;


int main(void) {

	char wynik[] = "           "; //bufor tekstowy, wyczyszczenie bufora

	SterownikLED sterownikLED;
	HCS04 hcs04;
	Uart uart;
	Buzzer buzzer;

	sterownikLED.init();
	hcs04.init();
	uart.init();
	//buzzer.init();

	sterownikLED.setReferences(wypelnienie_R, wypelnienie_G, wypelnienie_B, odl0);
	//buzzer.setReferences(buzzer_value,odl0,buzzerON);

	sei();

	while (true) {
		if(!PIN_PD3){
		hcs04.pomiar();
		sterownikLED.ustawSwiatlo();
		//buzzer.ustawBuzzer(sterownikLED.getIloscNiezmiennychWartosci());

		sprintf(wynik, " %d ", odl0);
		uart.send_uart_text(wynik);
		}
		_delay_ms_var(sterownikLED.getCzasPomiedzyPomiarami());
	}

	return 1;
}

//F-cja przerwania zewnêtrznego INT0
ISR(INT1_vect) {
	if (flaga == 0) {
		TIMSK |= (1 << OCIE2);      //w³¹cza Timer2 w trybie dopasowania (START)

		ClrBit(GICR, INT1);

		MCUCR = 0x00; //The falling edge of INT0 generates an interrupt request.
		MCUCR = (1 << ISC11);

		SetBit(GICR, INT1);

		flaga = 1;
	}

	else if (flaga == 1) {
		TIMSK &= ~(1 << OCIE2);                //zatrzymuje Timer2 (STOP)

		ClrBit(GICR, INT1);

		MCUCR = 0x00;            //Przerwanie zostanie wywo³ane zboczem rosn¹cym
		MCUCR = (1 << ISC11) | (1 << ISC10);        //na wejœciu INT0

		SetBit(GICR, INT1);

		odl0 = licznik;            //Zapisuje wartoœæ licznika do zmiennej "odl"
		/* odl0/=58;*/
		//odl0=(odl0*100/4)/25;                    //oraz skaluje go
		licznik = 0;                            //Zerowanie licznika
		flaga = 0;

	}
}

//F-cja przerwania od Timera2
ISR(TIMER2_COMP_vect) {
	licznik++;
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

ISR(TIMER1_OVF_vect) {
	TCNT1 = 100; // wartoœæ pocz¹tkowa
	licz++;
	if (licz > buzzer_value) {
		licz = 0;
	}
	if(buzzerON==true){
	if (licz <2) {
		PORTD |= (1 << PD7);
	} else if (licz >2)
		PORTD &= ~(1 << PD7);
	}
	else{
		PORTD &= ~(1 << PD7);
	}
}
