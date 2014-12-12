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
	uint16_t zolte;
	uint16_t czerwone;
	uint16_t czas_zmiany_na_biale;

public:
	SterownikLED();
	~SterownikLED();

	void ustawRejestryDDRC();
	void ustawRejestryTimer0();

	void setRed();
	void setBlue();
	void setGreen();
	void resetRed();
	void resetBlue();
	void resetGreen();

	void pokazRGB(volatile uint8_t & R,volatile uint8_t & G,volatile uint8_t & B);

	uint16_t getCzasZmianyNaBiale() const;
	void setCzasZmianyNaBiale(uint16_t czasZmianyNaBiale);
	uint16_t getCzerwone() const;
	void setCzerwone(uint16_t czerwone);
	uint16_t getZolte() const;
	void setZolte(uint16_t zolte);
};



#endif /* STEROWNIKLED_H_ */
