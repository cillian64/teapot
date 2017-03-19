#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "analog.h"
#include "rfm69.h"
#include "ukhasnet.h"
#include "grid-eye.h"
#include "sensors.h"
#include "base64.h"

#ifdef SEMIHOSTING
#include <stdio.h>
#include <string.h>
#endif

//#define GRIDEYE

static const I2CConfig i2cconfig = {
//    0xffff,
    1<<31 | 1<<30 | 1<<29 | 1<<28, // TIMINGR
    0,      // CR1
    0,      // CR2
};

#ifdef SEMIHOSTING
void initialise_monitor_handles(void);

/* Puts with no newline */
void puts_non(char *str);
void puts_non(char *str)
{
    for(uint32_t i=0; i<strlen(str); i++)
        putchar(str[i]);
}
#endif

int main(void)
{
    halInit();
    chSysInit();

    // Wait for things to warm up??
    // Get weird i2c errors if not for this.
    chThdSleepMilliseconds(1000);

    palClearLine(LINE_LED_YELLOW);
    palClearLine(LINE_LED_GREEN);

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, world.");
#endif

    spiStop(&SPID1);
    i2cStart(&I2CD1, &i2cconfig);
    pressure_init();
    i2cStop(&I2CD1);
    ukhasnet_radio_init();

    // Buffers
    uint8_t *packetbuf = chHeapAlloc(NULL, 64*sizeof(uint8_t));
#ifdef GRIDEYE
    uint16_t *pixels = chHeapAlloc(NULL, 64*sizeof(uint16_t));
    uint8_t *packed_pixels = chHeapAlloc(NULL, 36*sizeof(uint8_t));
    char *b64_pixels = chHeapAlloc(NULL, 49*sizeof(char));
#endif

    const char *nodename = "TEA9";
    char seq = 'a';
    uint8_t packet_len;
    uint32_t pressure;

    while(true)
    {
        // Begin activity
        palSetLine(LINE_LED_GREEN);

        // Read sensors. Swap from SPI to I2C
        spiStop(&SPID1);
        i2cStart(&I2CD1, &i2cconfig);
        volatile uint16_t temperature_raw = get_temperature();
        volatile int16_t temperature = convert_temperature(temperature_raw);
        volatile uint16_t humidity_raw = get_humidity();
        volatile uint8_t humidity = convert_humidity(humidity_raw);
//        pressure = get_pressure();
#ifdef GRIDEYE
        grideye_get(pixels);
#endif
        i2cStop(&I2CD1);
        ukhasnet_radio_init();

       // Send sensor packet:
#ifndef GRIDEYE
       packet_len = makepacket(packetbuf, 64, &seq, (char*)nodename, 0,
                               false, 0, // battery
                               true, temperature,
                               true, humidity,
                               false, pressure,
                               false, 0, // light
                               "");
       rfm69_transmit(packetbuf, packet_len);
#endif

        // For Grid-eye send another packet with pixels:
#ifdef GRIDEYE
        uint16_t average = grideye_pack(pixels, packed_pixels);
        packed_pixels[32] = average >> 8;
        packed_pixels[33] = average & 0xff;
        packed_pixels[34] = pixels[32] >> 8;
        packed_pixels[35] = pixels[32] & 0xff;
        b64encode(packed_pixels, 36, b64_pixels);
        b64_pixels[48] = '\0';

        packet_len = makepacket(packetbuf, 64, &seq, (char*)nodename, 1,
                                false, 0, false, 0, false, 0,
                                false, 0, false, 0,
                                b64_pixels);
        rfm69_transmit(packetbuf, packet_len);
#endif

        // End activity
        palClearLine(LINE_LED_GREEN);

        chThdSleepMilliseconds(60000);
    }
}
