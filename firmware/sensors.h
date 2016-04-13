#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stdbool.h>

uint16_t get_temperature(void);
uint16_t get_humidity(void);
void pressure_init(void);
uint32_t get_pressure(void);

#endif
