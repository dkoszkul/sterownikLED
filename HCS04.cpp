/*
 * HCS04.cpp
 *
 *  Created on: 3 gru 2014
 *      Author: Dominik
 */

#include "HCS04.h"

HCS04::HCS04() {
	nrPortu = -1;
}

HCS04::~HCS04() {
	// TODO Auto-generated destructor stub
}

int HCS04::pomiarOdleglosci() {
	int zmierzonaOdleglosc = 0;

	return zmierzonaOdleglosc;
}

void HCS04::InitInterrupt() {
//PRZERWANIA ZEWNÊTRZNE

	DDRB |= (1 << PB0); //PB0 -Trig wyjscie ; PD3- echo wejscie
	DDRD |= ~(1 << PD3);

	MCUCR = (1 << ISC11) | (1 << ISC10); //The rising edge of INT0 generates an interrupt request

//TIMER2
	TCNT2 = 0x00;          //Zerowanie rejestru TCNT2 (Rejestr jednostki zegara)

	TCCR2 = (1 << WGM21) | (1 << CS20); //Ustawia timer2 w tryb CTC bez preskalera
										//Czestotliwoœæ 16Mhz/1=8MHz

	OCR2 = 0x10;                            //Górna wartoœæ licznika wynosi 16
											//Przerwania bêd¹ nastêpowaæ co 1us
}

void HCS04::pomiar() {
	GICR |= (1 << INT1);

	SetBit(PORTB, 0);
	_delay_us(15);
	ClrBit(PORTB, 0);

	_delay_ms(20);

	GICR &= ~(1 << INT1);
}




