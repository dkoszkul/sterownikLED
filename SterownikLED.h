/*
 * SterownikLED.h
 *
 *  Created on: 25 lis 2014
 *      Author: Dominik
 */

#ifndef STEROWNIKLED_H_
#define STEROWNIKLED_H_

#define LED_R PC1
#define LED_G PC2
#define LED_B PC0
#define MAX 255

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


class SterownikLED {
private:
	static const uint8_t granica_czerwone=10;
	static const uint8_t granica_zolte=40;
	static const uint8_t granica_zielone=200;
	static const uint8_t czas_zmiany_na_biale=0;
	static const uint8_t histereza=5;

	uint8_t poprzednia_wartosc;
	uint8_t ilosc_niezmiennych_wartosci;

	volatile uint8_t *reference_R;
	volatile uint8_t *reference_G;
	volatile uint8_t *reference_B;
	volatile uint8_t *reference_odl;



public:
	SterownikLED();
	~SterownikLED();

	void ustawRejestryDDRC();
	void ustawRejestryTimer0();

	void setReferences(volatile uint8_t & R,volatile uint8_t & G,volatile uint8_t & B,volatile uint8_t & odl);

	void pokaz_swiatel_RGB(volatile uint8_t & R,volatile uint8_t & G,volatile uint8_t & B);
	int ustawSwiatlo();

	void ustawRGB(uint8_t red, uint8_t green, uint8_t blue);
};






#endif /* STEROWNIKLED_H_ */
