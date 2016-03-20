#ifndef LIGHT_H
#define LIGHT_H

#include <stdint.h>

/* Initialise ADC, light sensor, etc. */
void light_init(void);

/* Get amount of light, from 0-255, no particular units */
uint8_t get_light(void);

#endif

