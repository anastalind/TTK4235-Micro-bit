#include "gpiote.h"

void GPIOTE_config() {
	GPIOTE->CONFIG[0] = (3 | (13 << 8) | (3 << 16) | (1 << 20));
	GPIOTE->CONFIG[1] = (3 | (14 << 8) | (3 << 16) | (1 << 20));
	GPIOTE->CONFIG[2] = (3 | (15 << 8) | (3 << 16) | (1 << 20));
	GPIOTE->CONFIG[3] = (1 | (17 << 8) | (2 << 16) | (1 << 20));
}



