#include "utility.h"
#include "accel.h"
#include "ubit_led_matrix.h"
#include "twi.h"
#include "uart.h"
#include <stdio.h>



int main(){


	twi_init();

	uint8_t * data_buffer_0;
	data_buffer_0 = (uint8_t *)malloc(8 * sizeof(uint8_t));

	uint8_t accel_address = 0x01d;
	uint8_t WHO_AM_I = 0x0d;

	int registers_to_read = 8;

	uart_init(); 
	twi_multi_read(accel_address, WHO_AM_I, registers_to_read, data_buffer_0);
	utility_print( &uart_send, "%d", data_buffer_0[0] );
	//printf("\n");
	free(data_buffer_0);
	accel_init();

	ubit_led_matrix_init();
	int data_buffer[3];
	int x_acc;
	int y_acc;
	int z_acc;

	int x_dot;
	int y_dot;

	int sleep;
	while (1) {
		accel_read_x_y_z(data_buffer);
		x_acc = data_buffer[0];
		y_acc = data_buffer[1];
		z_acc = data_buffer[2];
		utility_print(&uart_send, "X: %6d Y: %6d Z: %6d\n\r", x_acc, y_acc, z_acc);
		x_dot = x_acc / 50;
		y_dot = - y_acc / 50;

		if(x_dot>2){
			x_dot = 2;
		}
		else if (x_dot <-2){
			x_dot = -2;
		}

		if(y_dot>2){
			y_dot = 2;
		}
		else if (y_dot <-2){
			y_dot = -2;
		}
	
		ubit_led_matrix_light_only_at(x_dot, y_dot);
		sleep = 100000;
		while(--sleep);
	} 

	return 0;

}