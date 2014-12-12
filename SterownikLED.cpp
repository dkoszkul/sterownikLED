/*
 * SterownikLED.cpp
 *
 *  Created on: 25 lis 2014
 *      Author: Dominik
 */

#include "SterownikLED.h"

SterownikLED::SterownikLED() {
	zolte=0;
	czerwone=0;
	czas_zmiany_na_biale=0;

}

SterownikLED::~SterownikLED() {
	// TODO Auto-generated destructor stub
}

void SterownikLED::ustawRejestryDDRC() {
	DDRC |= (1 << PC0);
	DDRC |= (1 << PC1);
	DDRC |= (1 << PC2);
}

void SterownikLED::setRed() {
	PORTC |= (1 << LED_R);
}

void SterownikLED::setBlue() {
	PORTC |= (1 << LED_B);
}

void SterownikLED::setGreen() {
	PORTC |= (1 << LED_G);
}

void SterownikLED::resetRed() {
	PORTC &= (0 << LED_R);
}

void SterownikLED::resetBlue() {
	PORTC &= (0 << LED_B);
}

void SterownikLED::resetGreen() {
	PORTC &= (0 << LED_G);
}

void SterownikLED::ustawRejestryTimer0() {
	TCCR0 |= (1 << CS00); // Ÿród³em CLK, preskaler 1
	TIMSK |= (1 << TOIE0);          //Przerwanie overflow (przepe³nienie timera)
}

void SterownikLED::pokazRGB(volatile uint8_t & R,volatile uint8_t & G,volatile uint8_t & B) {
	uint8_t i=0;
	R=0;
	G=0;
	B=0;
	for (i = 0; i < MAX; i++) {
		R = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		R = i;
		_delay_ms(5);
	}
	for (i = 0; i < MAX; i++) {
		G = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		G = i;
		_delay_ms(5);
	}
	for (i = 0; i < MAX; i++) {
		B = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		B = i;
		_delay_ms(5);
	}

	for (i = 0; i < MAX; i++) {
		B = i;
		R = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		B = i;
		R = i;
		_delay_ms(5);
	}
	for (i = 0; i < MAX; i++) {
		B = i;
		G = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		B = i;
		G = i;
		_delay_ms(5);
	}

	for (i = 0; i < MAX; i++) {
		R = i;
		G = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		R = i;
		G = i;
		_delay_ms(5);
	}


	for (i = 0; i < MAX; i++) {
		R = i;
		G = i;
		B = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		R = i;
		G = i;
		B = i;
		_delay_ms(5);
	}

	for (i = 0; i < MAX; i++) {
		R = i;
		G = i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		R = i;
		_delay_ms(5);
	}

	for (i = 0; i < MAX; i++) {
		R = i;
		G = 100-i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		B=100-i;
		_delay_ms(5);
	}

}

uint16_t SterownikLED::getCzasZmianyNaBiale() const {
	return czas_zmiany_na_biale;
}

void SterownikLED::setCzasZmianyNaBiale(uint16_t czasZmianyNaBiale) {
	this->czas_zmiany_na_biale = czasZmianyNaBiale;
}

uint16_t SterownikLED::getCzerwone() const {
	return czerwone;
}

void SterownikLED::setCzerwone(uint16_t czerwone) {
	this->czerwone = czerwone;
}

uint16_t SterownikLED::getZolte() const {
	return zolte;
}

void SterownikLED::setZolte(uint16_t zolte) {
	this->zolte = zolte;
}
