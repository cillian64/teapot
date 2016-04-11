#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "teapot_pins.h"
#include "rfm69.h"
#include "util.h"
#include "ukhasnet.h"
#include "analog.h"
#include "i2c.h"

/* #define SEMIHOSTING */
#ifdef SEMIHOSTING
#include <stdio.h>
void initialise_monitor_handles(void);
#endif

static void radio_init(void);

/* Initialise RFM69 and setup for ukhasnet layer 1+2 */
static void radio_init(void)
{
    rfm69_init();

    /* Set frequency:
     * Fstep = Fxosc / 2^19 = 32e6 / 2^19
     * FRF = freq / (32e6 / 2^19 )
     *     = 869.5 / 32 * 2^19 = 14245888 */
    rfm69_setfreq(14245888);

    /* Set output power in dBm */
    rfm69_setpower(2);

    /* Shift: 24kHz: fdev=24e3/fstep = 24e3/61 = 393
     * 2000-baud: bitrate = fxosc / 2000 = 32e6/2000 = 16000
     */
    rfm69_physetup(393, 16000);

    /* 3-byte preamble of 0xAA, 0xAA, 0xAA
     * 2-byte sync of 0x2D, 0xAA
     * preamble, sync, length, data, CRC16 */
    uint8_t syncvalue[2] = {0x2d, 0xaa};
    rfm69_packetsetup(true, 3, 2, syncvalue, false, false, true);


}

int main(void)
{
    char sequence = 'a';
    char buf[64];
    uint8_t packet_len;

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, gdb!");
#endif

    gpio_set(LED_ERR_PORT, LED_ERR);
    teapot_pins_init();
    radio_init();
    analog_init();
    gpio_clear(LED_ERR_PORT, LED_ERR);

    while(true)
    {
        gpio_set(LED_ACT_PORT, LED_ACT); /* begin actions */
        gpio_set(LIGHT_EN_PORT, LIGHT_EN);
        delay_ms(1);
        uint8_t light = get_light();
        gpio_clear(LIGHT_EN_PORT, LIGHT_EN);

        packet_len = makepacket(buf, 64, sequence, "TEA1",
                                true, get_batt(), /* batt */
                                false, -456, /* temp */
                                false, 42, /* hum */
                                false, 123456, /* press */
                                true, light); /* light */
        if(sequence++ == 'z')
            sequence = 'b';
        rfm69_transmit((uint8_t*)buf, packet_len);
        gpio_clear(LED_ACT_PORT, LED_ACT); /* end of action */

        delay_ms(3000);
    }

    return 0;
}

