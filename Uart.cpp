/*
 * Uart.cpp
 *
 *  Created on: 13 gru 2014
 *      Author: Dominik
 */

#include "Uart.h"

Uart::Uart() {
	// TODO Auto-generated constructor stub

}

Uart::~Uart() {
	// TODO Auto-generated destructor stub
}



uint8_t Uart::rec_uart(void) {
	while (!(UCSRA & _BV(RXC)));
	return UDR;
}

void Uart::send_uart(char byte) {
	while (!(UCSRA & _BV(UDRE)));
	UDR = byte;
}

void Uart::send_uart_text(char str[]) {
	unsigned char i = 0;
	for (i = 0; str[i] != '\0'; i++)
		send_uart(str[i]);
}
