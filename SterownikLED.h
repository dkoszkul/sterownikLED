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
#define WAIT_TIME 1000
#define WORK_TIME 100

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

class SterownikLED {
private:
	static const uint8_t granica_czerwone = 10;
	static const uint8_t granica_zolte = 40;
	static const uint8_t granica_zielone = 200;
	static const uint8_t czas_zmiany_na_biale = 0;
	static const uint8_t histereza = 5;

	uint8_t poprzednia_wartosc;
	uint8_t ilosc_niezmiennych_wartosci;

	volatile uint8_t *reference_R;
	volatile uint8_t *reference_G;
	volatile uint8_t *reference_B;
	volatile uint8_t *reference_odl;

	uint8_t mode; /* 0 - wait, 1 - wjazd, 2 - wyjazd  */

	uint8_t czas_pomiedzy_pomiarami;
	uint8_t odleglosc_czujnika_od_samochodu_podczas_postoju;

	void ustawRejestryDDRC();
	void ustawRejestryTimer0();


	void mode_wjazdDoGarazu();
	void mode_wyjazdZGarazu();
	void mode_postoj();

public:
	SterownikLED();
	~SterownikLED();

	void init();
	void setReferences(volatile uint8_t & R, volatile uint8_t & G, volatile uint8_t & B, volatile uint8_t & odl);

	void pokaz_swiatel_RGB(volatile uint8_t & R, volatile uint8_t & G, volatile uint8_t & B);
	void ustawSwiatlo();
	void ustawRGB(uint8_t red, uint8_t green, uint8_t blue);



	/* getters & setters */
	uint8_t getCzasPomiedzyPomiarami() const;
	void setCzasPomiedzyPomiarami(uint8_t czasPomiedzyPomiarami);

	uint8_t getIloscNiezmiennychWartosci() const {
		return ilosc_niezmiennych_wartosci;
	}
};

void _delay_ms_var(uint32_t a);

#endif /* STEROWNIKLED_H_ */
