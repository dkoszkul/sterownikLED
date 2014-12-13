/*
 * SterownikLED.cpp
 *
 *  Created on: 25 lis 2014
 *      Author: Dominik
 */

#include "SterownikLED.h"

SterownikLED::SterownikLED() {
	poprzednia_wartosc = -1;
	ilosc_niezmiennych_wartosci = 0;

}

SterownikLED::~SterownikLED() {
	// TODO Auto-generated destructor stub
}

void SterownikLED::ustawRejestryDDRC() {
	DDRC |= (1 << PC0);
	DDRC |= (1 << PC1);
	DDRC |= (1 << PC2);
}


void SterownikLED::ustawRejestryTimer0() {
	TCCR0 |= (1 << CS00); // Ÿród³em CLK, preskaler 1
	TIMSK |= (1 << TOIE0);          //Przerwanie overflow (przepe³nienie timera)
}

void SterownikLED::setReferences(volatile uint8_t & R,volatile uint8_t & G,volatile uint8_t & B){
reference_R = &R;
reference_G = &G;
reference_B = &B;

}

void SterownikLED::ustawRGB(volatile uint8_t red,volatile uint8_t green, volatile uint8_t blue){
	*reference_R=red;
	*reference_G=green;
	*reference_B=blue;
}

void SterownikLED::pokaz_swiatel_RGB(volatile uint8_t & R, volatile uint8_t & G,
		volatile uint8_t & B) {
	uint8_t i = 0;
	R = 0;
	G = 0;
	B = 0;
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
		G = 100 - i;
		_delay_ms(5);
	}
	for (i = MAX; i > 0; i--) {
		B = 100 - i;
		_delay_ms(5);
	}

}

int SterownikLED::ustawSwiatlo(volatile uint8_t odleglosc) {
	int pochodna;
	if (poprzednia_wartosc == -1)
		poprzednia_wartosc = odleglosc; /* pierwszy przebieg */
	else {

		pochodna = poprzednia_wartosc - odleglosc; /* je¿eli >0 obiekt zbli¿a siê do czujnika */

		if (odleglosc > granica_zielone && pochodna > 0) { /* Warunki w przypadku zbli¿ania siê do œciany  */
			ustawRGB(0,0,0);
		} else if (odleglosc <= granica_zielone && odleglosc > granica_zolte
				&& pochodna > 1) {
			ustawRGB(0,MAX,0);
		} else if (odleglosc <= granica_zolte && odleglosc > granica_czerwone
				&& pochodna > 1) {
			ustawRGB(MAX,MAX,0);
		} else if (odleglosc <= granica_czerwone && pochodna > 1) {
			ustawRGB(MAX,0,0);
		}
		else if (pochodna < -1 && odleglosc <= (granica_czerwone + histereza)) {
			ustawRGB(MAX,0,0);
		}
		else if(pochodna < -1 && odleglosc > (granica_czerwone + histereza) && odleglosc <= (granica_zolte + histereza)){
			ustawRGB(MAX,MAX,0);
		}
		else if(pochodna < -1 && odleglosc > (granica_zolte + histereza) && odleglosc <= (granica_zielone + histereza)){
			ustawRGB(0,MAX,0);
		}
		else if (pochodna < -1 && odleglosc > (granica_zielone + histereza) ){
			ustawRGB(0,0,0);
		}
		else if(pochodna >= -1 && pochodna <=1 && ilosc_niezmiennych_wartosci<22 && odleglosc<= granica_czerwone){
			ilosc_niezmiennych_wartosci++;
		}
	}

	if(pochodna < -1 && pochodna >1 ){
		ilosc_niezmiennych_wartosci=0;
	}
	if(ilosc_niezmiennych_wartosci>20){
		ustawRGB(MAX,MAX,MAX);
	}
	poprzednia_wartosc=odleglosc;
return pochodna;
}



