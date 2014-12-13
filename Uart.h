/*
 * Uart.h
 *
 *  Created on: 13 gru 2014
 *      Author: Dominik
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

class Uart {
public:
	Uart();
	~Uart();

	static void uart_9600() {
	#define BAUD 9600
	#include <util/setbaud.h>
		UBRRH = UBRRH_VALUE;
		UBRRL = UBRRL_VALUE;
	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif
	}

	static void init() {
		uart_9600();
		UCSRC = _BV(URSEL) | (1 << UCSZ0) | (1 << UCSZ1) | _BV(USBS); //2 bity stopu ; 8 bitów informacji
		UCSRB = _BV(TXEN) | _BV(RXEN) | _BV(RXCIE); // uruchomienie TX,RX i przerwania w RX
	}
	uint8_t rec_uart();
	void send_uart(char byte);
	void send_uart_text(char str[]);

};

#endif /* UART_H_ */
