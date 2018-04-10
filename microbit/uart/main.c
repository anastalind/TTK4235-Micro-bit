#include <stdint.h>
#include "uart.h"
#include "gpio.h"
#include <stdio.h>


ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
		}
	return count;
}

int main(){
	for (int i =4; i <= 15; i++){
		GPIO->DIRSET = ( 1 << i);
		GPIO->OUTCLR = ( 1 << i);
	}

	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	uart_init();

	//iprintf("Norway has %d counties.\n\r", 18);
	iprintf("hei");

	while(1){

		//iprintf("hei");
		char character = uart_read();gf
		uart_send_letter();

		if (character != '\0') {
			uart_read_letter();
		}

	}
	return 0;
}
