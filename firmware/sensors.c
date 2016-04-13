#include <stdint.h>
#include <stdbool.h>

#include "i2c.h"
#include "sensors.h"
#include "util.h"

const uint8_t ms5637_address = 0b01110110;
uint16_t ms5637_prom[7];

uint16_t get_temperature(void)
{
    uint8_t buffer[2];

    buffer[0] = 0xe3; /* temperature, hold master */

    i2c_transfer(0x40, true, 1, buffer);
    i2c_transfer(0x40, false, 2, buffer);

    if(!(buffer[0] & 0x02))
        panic(); /* measurement type is incorrect */

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)buffer[1] << 6) | (buffer[0] >> 2);
}

uint16_t get_humidity(void)
{
    uint8_t buffer[2];

    buffer[0] = 0xe5; /* humidity, hold master */

    i2c_transfer(0x40, true, 1, buffer);
    i2c_transfer(0x40, false, 2, buffer);

    if(buffer[0] & 0x02)
        panic(); /* measurement type is incorrect */

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)buffer[1] << 6) | (buffer[0] >> 2);
}

void pressure_init(void)
{
    uint8_t command;
    uint8_t buffer[2];

    command = 0x1e; /* reset */
    i2c_transfer(ms5637_address, true, 1, &command);

    /* Read 7 calibration values from PROM */
    for(uint8_t prom_addr=0; prom_addr<7; prom_addr++)
    {
        command = 0xa0 | prom_addr;
        i2c_transfer(ms5637_address, true, 1, &command);
        i2c_transfer(ms5637_address, false, 2, buffer);
        ms5637_prom[prom_addr] = (uint16_t)buffer[1] << 8 | buffer[0];
    }
}

uint32_t get_pressure(void)
{
    uint8_t command;
    uint8_t buffer[3];
    uint32_t d1;
    uint32_t d2;

    /* Read D1 */
    command = 0x40; /* Read D1 with 256 oversampling */
    i2c_transfer(ms5637_address, true, 1, &command);
    delay_ms(1);
    command = 0x00; /* Read ADC */
    i2c_transfer(ms5637_address, true, 1, &command);
    i2c_transfer(ms5637_address, false, 3, buffer);
    d1 = (uint32_t)buffer[2] << 16 | (uint32_t)buffer[1] << 8 | buffer[0];

    /* Read D2 */
    buffer[0] = 0x50; /* Read D2 with 256 oversampling */
    i2c_transfer(ms5637_address, true, 1, &command);
    delay_ms(1);
    command = 0x00; /* Read ADC */
    i2c_transfer(ms5637_address, true, 1, &command);
    i2c_transfer(ms5637_address, false, 3, buffer);
    d2 = (uint32_t)buffer[2] << 16 | (uint32_t)buffer[1] << 8 | buffer[0];

    /* Difference between actual and reference temperature */
    int32_t dT = d2 - ms5637_prom[5] * 256;
    /* Actual temperature */
    /* int32_t temp = 2000 + dT * ms5637_prom[6] / 8388608; */
    /* Pressure offset at actual temperature */
    int64_t off = ms5637_prom[2] * 131072 + (ms5637_prom[4] * dT) / 64;
    /* Pressure sensitivity at actual temperature */
    int64_t sens = ms5637_prom[1] * 65536 + (ms5637_prom[3] * dT) / 128;
    /* Temperature compensated pressure in hundredths of mbar */
    int32_t p = (d1 * sens / 2097152 - off) / 32768;

    if(p<0)
        panic();
    return (uint32_t)p;
}

