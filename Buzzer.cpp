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

	TCNT1 = 10; // wartoœæ pocz¹tkowa
	TCCR1A = 0x00; // timer1 w trybie czasomierza
	TCCR1B = (1 << CS11); //no preskaler
	TIMSK |= (1 << TOIE1);
	DDRD |= (1 << PD7);
}

void Buzzer::setReferences(volatile uint8_t& buzzer_value, volatile uint8_t & odl,volatile bool & buzzerON) {
	this->buzzer_value=&buzzer_value;
	this->reference_odl=&odl;
	this->buzzerON=&buzzerON;
}

void Buzzer::ustawBuzzer(uint8_t ilosc_niezmiennych_wartosci) {
	if(*reference_odl>40 && *reference_odl<200){
		*buzzerON=true;
		*buzzer_value=16;
	}
	else if (*reference_odl>20 && *reference_odl<=40){
		*buzzerON=true;
		*buzzer_value=8;
	}
	else if (*reference_odl>10 && *reference_odl<=20){
		*buzzerON=true;
		*buzzer_value=4;
	}
	else if (*reference_odl<=10){
		*buzzerON=true;
		*buzzer_value=2;
	}
	if(ilosc_niezmiennych_wartosci>20){
		*buzzerON=false;
	}
}
