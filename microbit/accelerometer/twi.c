#include <twi.h>

void twi_init(){
	TWIO->PSELSCL = 0;
	TWIO->PSELSDA = 30;
	GPIO->PIN_CNF[0] = (1<<2)|(1<<3)|(1<<9)|(1<<10);
	GPIO->PIN_CNF[30] = (1<<2)|(1<<3)|(1<<9)|(1<<10);
	TWIO->ENABLE = 5;
	TWIO->FREQUENCY = 0x01980000;
	TWIO->RXDREADY = 0;
	TWIO->TXDSENT = 0;
}


void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
){
	TWIO->ADDRESS = slave_address;
	TWIO->STARTTX = 1;

	TWIO->TXD = start_register;
	
	while(!TWIO->TXDSENT);

	TWIO->STARTRX = 1;

	for(int i = 0; i < registers_to_read-1; i++){
		while(!TWIO->RXDREADY);
		TWIO->RXDREADY = 0;
		data_buffer[i] = TWIO->RXD;
	}
	TWIO->STOP = 1;
	data_buffer[registers_to_read-1]= TWIO->RXD;
	TWIO->RXDREADY = 0;
}