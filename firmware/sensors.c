#include <stdint.h>
#include <stdbool.h>

#include "i2c.h"
#include "sensors.h"
#include "util.h"

uint16_t get_temperature(void)
{
    uint8_t buffer[2];

    buffer[0] = 0xe3; /* temperature, hold master */

    i2c_transfer(false, 0x40, true, 1, buffer);
    i2c_transfer(false, 0x40, false, 2, buffer);

    if(!(buffer[0] & 0x02))
        panic(); /* measurement type is incorrect */

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)buffer[1] << 6) | (buffer[0] >> 2);
}

uint16_t get_humidity(void)
{
    uint8_t buffer[2];

    buffer[0] = 0xe5; /* humidity, hold master */

    i2c_transfer(false, 0x40, true, 1, buffer);
    i2c_transfer(false, 0x40, false, 2, buffer);

    if(buffer[0] & 0x02)
        panic(); /* measurement type is incorrect */

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)buffer[1] << 6) | (buffer[0] >> 2);
}


