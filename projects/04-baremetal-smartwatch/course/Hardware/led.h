#ifndef __LED__H__
#define __LED__H__
#include <stdint.h>


void led_init();

void led_toggle();

void led_set_state(uint8_t state);

int led_get_state();

#endif