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
public:
	Buzzer();
	~Buzzer();

	void init();
};

#endif /* BUZZER_H_ */
