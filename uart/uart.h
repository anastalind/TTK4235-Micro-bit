#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "gpio.h"

void uart_init();
void uart_send(char letter);
char uart_read();
void uart_send_letter();
void uart_read_letter(int is_on);

#endif 