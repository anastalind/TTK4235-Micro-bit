#include <stdint.h>
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;

	volatile uint32_t RESERVED0[3];
	volatile uint32_t SUSPEND;

	volatile uint32_t RESERVED1[56];

	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;

	volatile uint32_t RESERVED2[4];

	volatile uint32_t TXDRDY;

	volatile uint32_t RESERVED3[1];

	volatile uint32_t ERROR;

	volatile uint32_t RESERVED4[7];

	volatile uint32_t RXTO;

	volatile uint32_t RESERVED5[110];

	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;

	volatile uint32_t RESERVED6[93];

	volatile uint32_t ERRORSRC;

	volatile uint32_t RESERVED7[31];

	volatile uint32_t ENABLE;

	volatile uint32_t RESERVED8[1];

	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;

	volatile uint32_t RESERVED9[1];

	volatile uint32_t BAUDRATE;

	volatile uint32_t RESERVED10[17];

	volatile uint32_t CONFIG;

} NRF_UART_REG;


void uart_init() {
	// Configurates GPIO pins
	GPIO->PIN_CNF[24] = 1;
	GPIO->PIN_CNF[25] = 0;

	// Ready for use by the UART module
	UART->PSELTXD = 24;
	UART->PSELRXD = 25;

	// Disconnects the CTS and RTS lines
	UART->PSELRTS = 0xFFFFFFFF;
	UART->PSELCTS = 0xFFFFFFFF;

	// Sets baudrate to 9600
	UART->BAUDRATE = 0x00275000;

	// Turns on the UART module
	UART->ENABLE = 4;

	// Ready to receive messages
	UART->STARTRX = 1;
}


void uart_send(char letter) {

	UART->STARTTX = 1;
	UART->TXD = letter;

	while (UART->TXDRDY != 1);

	UART->STOPTX = 1;
	UART->TXDRDY = 0;
	
}


char uart_read() {
	char character = '\0';

	if (UART->RXDRDY == 0) {
		return character;
	}

	else {
		UART->RXDRDY = 0;
		character = UART->RXD;
		return character;
	}
}


void uart_send_letter() {
	if ((GPIO->IN & 131072) != 131072) {
		uart_send('A');
	}


	else if ((GPIO->IN & 67108864) != 67108864) {
		uart_send('B');
	}
}


void uart_read_letter(int is_on) {

	if (uart_read() == '\0') {
		return;
	}

	else {
		if (is_on == 1) {
			GPIO->OUTCLR = (1 << 13);
			GPIO->OUTCLR = (1 << 14);
			GPIO->OUTCLR = (1 << 15);
			is_on = 0;
		}


		else {
			GPIO->OUTSET = (1 << 13);
			GPIO->OUTSET = (1 << 14);
			GPIO->OUTSET = (1 << 15);
			is_on = 1;
		}
	}
}

