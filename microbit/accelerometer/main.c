#include "utility.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include "twi.h"

int main(){

	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	uint8_t * data_buffer;
	data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));

	uint8_t accel_address = 0x01d;
	uint8_t WHO_AM_I = 0x0d;

	int registers_to_read = 8;

	twi_multi_read(accel_address, WHO_AM_I, registers_to_read, data_buffer);

	int fabric_id[8] = {0, 1, 0, 1, 1, 0, 1, 0};
	int is_identical = 1;

	for (int i = 0; i < registers_to_read; i++){
		if (data_buffer[i] != fabric_id[i]){
			is_identical = 0;
		}
	}

	if (is_identical = 1){
		GPIO->OUTSET = (1 << 13);
		GPIO->OUTSET = (1 << 14);
		GPIO->OUTSET = (1 << 15);
	}

	free(data_buffer);


}