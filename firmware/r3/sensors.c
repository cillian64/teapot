#include <stdint.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"

#include "sensors.h"
#include "util.h"

const uint8_t ms5637_address = 0b01110110;
uint16_t ms5637_prom[7];
const uint8_t htu21d_address = 0x40;

/* Convert raw temperature from HTU21D to signed integer 0.1C */
int32_t convert_temperature(uint16_t raw)
{
    int64_t temp = raw;
    temp *= 175720;
    temp /= (1<<16);
    temp -= 46850;
    temp /= 100;
    return temp;
}

/* Convert raw humidity from HTU21D to unsigned integer RH percent */
uint8_t convert_humidity(uint16_t raw)
{
    uint32_t hum = raw;
    hum *= 125;
    hum /= (1<<16);
    hum -= 6;
    return hum;
}

/* Get temperature from HTU21D */
uint16_t get_temperature(void)
{
    uint8_t tx_buf[1];
    uint8_t rx_buf[3] = {0, 0, 0};
    msg_t result;

    tx_buf[0] = 0xe3; /* temperature, hold master */

    /* Transmit command to begin temperature measurement */
    result = i2cMasterTransmitTimeout(&I2CD1,
                                      htu21d_address,   // address
                                      tx_buf, 1,        // tx buffer and length
                                      rx_buf, 0,        // rx buffer and length
                                      TIME_INFINITE);   // No timeout
    if(result != MSG_OK)
    {
        volatile uint8_t error = i2cGetErrors(&I2CD1);
        panic("Temperature cmd return != MSG_OK");
    }

    /* Now try to read back -- slave will hold until ready */
    result = i2cMasterReceiveTimeout(&I2CD1,
                                     htu21d_address,    // address
                                     rx_buf, 3,         // rx buffer and length
                                     TIME_INFINITE);
    if(result != MSG_OK)
    {
        volatile uint8_t error = i2cGetErrors(&I2CD1);
        panic("Temperature read return != MSG_OK");
    }

    // Sometimes MSbit of MSB sometimes gets improbably set
    rx_buf[0] &= 0x7f;

//    if(rx_buf[1] & 0x02)
//        panic("Temperature result is of type humidity!");

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)rx_buf[0] << 8) | (rx_buf[1] & 0b11111100);
}

/* Get humidity from HTU21D */
uint16_t get_humidity(void)
{
    uint8_t tx_buf[1];
    uint8_t rx_buf[3];
    msg_t result;

    tx_buf[0] = 0xe5; /* humidity, hold master */

    /* Transmit command to begin humidity measurement */
    result = i2cMasterTransmitTimeout(&I2CD1,
                                      htu21d_address,   // address
                                      tx_buf, 1,        // tx buffer and length
                                      rx_buf, 0,        // rx buffer and length
                                      TIME_INFINITE);   // No timeout
    if(result != MSG_OK)
    {
        volatile uint8_t error = i2cGetErrors(&I2CD1);
        panic("Humidity cmd return != MSG_OK");
    }

    /* Now try to read back -- slave will hold until ready */
    result = i2cMasterReceiveTimeout(&I2CD1,
                                     htu21d_address,    // address
                                     rx_buf, 3,         // rx buffer and length
                                     TIME_INFINITE);
    if(result != MSG_OK)
    {
        volatile uint8_t error = i2cGetErrors(&I2CD1);
        panic("Humidity read return != MSG_OK");
    }

//    if(!(rx_buf[0] & 0x02))
//        panic("Humidity result is of type temperature!");

    /* Retrieve 14-bit measurement, ignoring 2 LSBits */
    return ((uint16_t)rx_buf[0] << 6) | (rx_buf[1] >> 2);
}

/* Initialise MS5637 pressure sensor */
void pressure_init(void)
{
    uint8_t tx_buf[1];
    uint8_t rx_buf[2];
    msg_t result;

    tx_buf[0] = 0x1e; /* reset */
    result = i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                                      tx_buf, 1,
                                      rx_buf, 0,
                                      TIME_INFINITE);
    if(result != MSG_OK)
    {
        volatile uint8_t error = i2cGetErrors(&I2CD1);
        panic("Pressure cmd return != MSG_OK");
    }

    /* Read 6 values from PROM */
    for(uint8_t prom_addr=0; prom_addr<7; prom_addr++)
    {
        tx_buf[0] = 0xa0 | (prom_addr << 1);
        /* Do these two separately as the ms5637 datasheet seems to imply that
           we need an I2C stop between the command and actually reading */
        result = i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                                          tx_buf, 1,
                                          rx_buf, 0,
                                          TIME_INFINITE);
        result = i2cMasterReceiveTimeout(&I2CD1, ms5637_address,
                                         rx_buf, 2,
                                         TIME_INFINITE);
        ms5637_prom[prom_addr] = (uint16_t)rx_buf[0] << 8 | rx_buf[1];
    }
}

/* Get pressure from MS5637 */
uint32_t get_pressure(void)
{
    uint8_t tx_buf[1];
    uint8_t rx_buf[3];
    uint32_t d1;
    uint32_t d2;

    /* Read D1 */
    tx_buf[0] = 0x40; /* Read D1 with 256 oversampling */
    i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                             tx_buf, 1, rx_buf, 0, TIME_INFINITE);
    chThdSleepMilliseconds(1);
    tx_buf[0] = 0x00; /* Read ADC on MS5637 */
    i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                             tx_buf, 1, rx_buf, 0, TIME_INFINITE);
    i2cMasterReceiveTimeout(&I2CD1, ms5637_address,
                            rx_buf, 3, TIME_INFINITE);
    d1 = (uint32_t)rx_buf[0] << 16 | (uint32_t)rx_buf[1] << 8 | rx_buf[2];

    /* Read D2 */
    tx_buf[0] = 0x50; /* Read D2 with 256 oversampling */
    i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                             tx_buf, 1, rx_buf, 0, TIME_INFINITE);
    chThdSleepMilliseconds(1);
    tx_buf[0] = 0x00; /* Read ADC on MS5637 */
    i2cMasterTransmitTimeout(&I2CD1, ms5637_address,
                             tx_buf, 1, rx_buf, 0, TIME_INFINITE);
    i2cMasterReceiveTimeout(&I2CD1, ms5637_address,
                            rx_buf, 3, TIME_INFINITE);
    d2 = (uint32_t)rx_buf[0] << 16 | (uint32_t)rx_buf[1] << 8 | rx_buf[2];

    /* Difference between actual and reference temperature */
    int32_t dT = d2 - (int32_t)ms5637_prom[5] * 256;
    /* Actual temperature */
    int32_t temp = 2000 + dT * (int32_t)ms5637_prom[6] / 8388608;
    /* Pressure offset at actual temperature */
    int64_t off = (int64_t)ms5637_prom[2]*131072
                + ((int64_t)ms5637_prom[4]*dT) / 64;
    /* Pressure sensitivity at actual temperature */
    int64_t sens = (int64_t)ms5637_prom[1] * 65536
                 + ((int64_t)ms5637_prom[3] * dT) / 128;
    /* Temperature compensated pressure in hundredths of mbar */
    int32_t p = (d1 * sens / 2097152 - off) / 32768;

    if(p<0)
        panic("Pressure result <0");
    return (uint32_t)p;
}

