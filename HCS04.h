/*
 * HCS04.h
 *
 *  Created on: 3 gru 2014
 *      Author: Dominik
 */

#ifndef HCS04_H_
#define HCS04_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#define SetBit(reg, bit) ((reg) |= (0x01 << (bit)))            // Ustawienie danego bitu w rejestrze
#define ClrBit(reg, bit) ((reg) &= ~(0x01 << (bit)))        // Wyzerowanie danego bitu w rejestrze

class HCS04 {
private:
	int nrPortu;
public:
	HCS04();
    ~HCS04();

	void setNrPortu(int nr) {
		nrPortu = nr;
	}
	int getNrPortu() {
		return nrPortu;
	}
	int pomiarOdleglosci();
	void InitInterrupt();
	void pomiar();
};

#endif /* HCS04_H_ */
