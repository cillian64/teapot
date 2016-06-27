#ifndef LIGHT_H
#define LIGHT_H

#include <stdint.h>

/* Initialise ADC, light sensor, etc. */
void analog_init(void);

/* Get amount of light, from 0-255, no particular units */
uint8_t get_light(void);

/* Get battery voltage in hundredths of a volt */
uint8_t get_batt(void);

#endif

