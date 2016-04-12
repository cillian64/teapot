#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stdbool.h>

void pressure_init(void);
uint32_t get_pressure(void);

#endif
