#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "analog.h"
#include "rfm69.h"
#include "ukhasnet.h"
#include "grid-eye.h"
#include "sensors.h"

#ifdef SEMIHOSTING
#include <stdio.h>
#include <string.h>
#endif

static const I2CConfig i2cconfig = {
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

    palClearLine(LINE_LED_YELLOW);
    palClearLine(LINE_LED_GREEN);

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, world.");
#endif

    pressure_init();

    // Buffers
    uint8_t *packetbuf = chHeapAlloc(NULL, 64*sizeof(uint8_t));
#ifdef GRIDEYE
    uint16_t *pixels = chHeapAlloc(NULL, 64*sizeof(uint16_t));
#endif

    const char nodename = "TEAx";
    char seq = 'a';
    uint8_t packet_len;
    int32_t temperature;
    uint8_t humidity;
    uint32_t pressure;

    while(true)
    {
        // Begin activity
        palSetLine(LINE_LED_GREEN);

        // Read sensors. Swap from SPI to I2C
        spiStop(&SPID1);
        i2cStart(&I2CD1, &i2cconfig);
        temperature = convert_temperature(get_temperature());
        humidity = convert_humidity(get_humidity());
        pressure = get_pressure();
#ifdef GRIDEYE
        grideye_get(pixels);
#endif
        i2cStop(&I2CD1);
        ukhasnet_radio_init();

        // Send sensor packet:
        packet_len = makepacket(packetbuf, 64, &seq, nodename,
                                false, 0, // battery
                                true, temperature,
                                true, humidity,
                                true, pressure,
                                false, 0 // light
                                );
        rfm69_transmit(packetbuf, packet_len);

        // For Grid-eye send another two packets with pixels:
#ifdef GRIDEYE
        packet_len = makepacket(packetbuf, 64, &seq, nodename,
                                false, 0, false, 0, false, 0,
                                false, 0, false, 0,
                                "fakegrideyedatay0l0");
        rfm69_transmit(packetbuf, packet_len);
        packet_len = makepacket(packetbuf, 64, &seq, nodename,
                                false, 0, false, 0, false, 0,
                                false, 0, false, 0,
                                "2grideye4mel0l");
        rfm69_transmit(packetbuf, packet_len);
#endif


        palClearLine(LINE_LED_GREEN);
    }
}
