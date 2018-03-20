#include <stdint.h>
#include "uart.h"

int main(){
	int sleep = 0;
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	uart_init();
	int is_on = 0;

	while(1){
		uart_send_letter();
		uart_read_letter(is_on);
		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
