/*
 * Buzzer.cpp
 *
 *  Created on: 13 gru 2014
 *      Author: Dominik
 */

#include "Buzzer.h"

Buzzer::Buzzer() {
	// TODO Auto-generated constructor stub

}

Buzzer::~Buzzer() {
	// TODO Auto-generated destructor stub
}

void Buzzer::init() {

	TCNT1 = 3036; // wartoœæ pocz¹tkowa
	TCCR1A = 0x00; // timer1 w trybie czasomierza
	TCCR1B = (1 << CS10); // preskaler 256
	TIMSK |= (1 << TOIE1);
	DDRD |= (1 << PD7);
}
