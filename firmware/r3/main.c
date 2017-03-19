#include <string.h>

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "analog.h"
#include "rfm69.h"
#include "ukhasnet.h"
#include "grid-eye.h"
#include "sensors.h"
#include "base64.h"
#include "flash.h"

#ifdef SEMIHOSTING
#include <stdio.h>
#endif

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

    flash_config_t *config = chHeapAlloc(NULL, sizeof(flash_config_t));
    // Uncomment below to write config to flash memory.
    // strcpy(config->nodeid, "TEA8");
    // config->ttl = 3;
    // config->interval = 60;
    // config->has_battery = true;
    // config->has_temperature = true;
    // config->has_humidity = true;
    // config->has_pressure = true;
    // config->has_light = false;
    // config->has_grideye = false;
    // flash_write_config(config);
    flash_read_config(config);

    analog_init();
    ukhasnet_radio_init();

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

    // Buffers
    uint8_t *packetbuf = chHeapAlloc(NULL, 64*sizeof(uint8_t));

    // GRIDEYE stuff.  Allocate whether or not we actually have a grideye
    uint16_t *pixels = chHeapAlloc(NULL, 64*sizeof(uint16_t));
    uint8_t *packed_pixels = chHeapAlloc(NULL, 36*sizeof(uint8_t));
    char *b64_pixels = chHeapAlloc(NULL, 49*sizeof(char));
    uint16_t grid_average;

    char seq = 'a';
    uint8_t packet_len;
    uint32_t pressure;
    uint8_t battery;
    uint16_t light;
    uint16_t temperature;
    uint8_t humidity;

    while(true)
    {
        // Begin activity
        palSetLine(LINE_LED_GREEN);

        // Read analog sensors.
        analog_read(&battery, &light);
        // Read I2C sensors. Swap from SPI to I2C
        spiStop(&SPID1);
        i2cStart(&I2CD1, &i2cconfig);
        temperature = convert_temperature(get_temperature());
        humidity = convert_humidity(get_humidity());
        pressure = get_pressure();
        if(config->has_grideye)
            grideye_get(pixels);
        i2cStop(&I2CD1);
        ukhasnet_radio_init();

       // Send sensor packet:
       packet_len = makepacket(packetbuf, 64, &seq, config->nodeid,
                               config->ttl,
                               config->has_battery, battery,
                               config->has_temperature, temperature,
                               config->has_humidity, humidity,
                               config->has_pressure, pressure,
                               config->has_light, light,
                               "");
       rfm69_transmit(packetbuf, packet_len);

        // For Grid-eye send another packet with pixels:
        if(config->has_grideye)
        {
            grid_average = grideye_pack(pixels, packed_pixels);
            packed_pixels[32] = grid_average >> 8;
            packed_pixels[33] = grid_average & 0xff;
            packed_pixels[34] = pixels[32] >> 8;
            packed_pixels[35] = pixels[32] & 0xff;
            b64encode(packed_pixels, 36, b64_pixels);
            b64_pixels[48] = '\0';

            packet_len = makepacket(packetbuf, 64, &seq,
                                    config->nodeid,
                                    0, // Disable grideye repeating
                                    false, 0, false, 0, false, 0,
                                    false, 0, false, 0,
                                    b64_pixels);
            rfm69_transmit(packetbuf, packet_len);
        }

        // End activity and clean up for sleep
        palClearLine(LINE_LED_GREEN);
        rfm69_setmode(RFM69_OPMODE_SLEEP);
        i2cStop(&I2CD1);
        spiStop(&SPID1);
        adcStop(&ADCD1);
        chThdSleepMilliseconds(config->interval * 1000);
    }
}
