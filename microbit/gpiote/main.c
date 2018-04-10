#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	GPIOTE_config();
	PPI_connect();

	PPI->CHENSET = (1 << 0) | (1 << 1) | (1 << 2);
	
	while (1) {}

	return 0;
}