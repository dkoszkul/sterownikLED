/*
 * Buzzer.h
 *
 *  Created on: 13 gru 2014
 *      Author: Dominik
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

class Buzzer {
private:
	volatile uint8_t *buzzer_value;
	volatile uint8_t *reference_odl;
	volatile bool *buzzerON;

public:
	Buzzer();
	~Buzzer();

	void init();
	void setReferences(volatile uint8_t &buzzer_value, volatile uint8_t & odl,volatile bool & buzzerON);
	void ustawBuzzer(uint8_t ilosc_niezmiennych_wartosci);
};

#endif /* BUZZER_H_ */
