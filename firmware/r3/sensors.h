#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>
#include <stdbool.h>

/* Convert raw temperature from HTU21D to signed integer milli-celcius */
int32_t convert_temperature(uint16_t raw);

/* Convert raw humidity from HTU21D to unsigned integer RH percent */
uint8_t convert_humidity(uint16_t raw);

/* Get temperature from HTU21D */
uint16_t get_temperature(void);

/* Get humidity from HTU21D */
uint16_t get_humidity(void);

/* Initialise MS5637 pressure sensor */
void pressure_init(void);

/* Get pressure from MS5637 */
uint32_t get_pressure(void);

#endif
