#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "teapot_pins.h"
#include "rfm69.h"
#include "util.h"

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

    /* Set max output power 13dBm */
    rfm69_setpower(13);

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
#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, gdb!");
#endif

    teapot_pins_init();
    radio_init();
    gpio_clear(LED_ERR_PORT, LED_ERR);

    char* buf = "3a:hello[TEA1]";
    uint8_t buflen = 14;

    while(true) /* main loop */
    {
        gpio_set(LED_ACT_PORT, LED_ACT);
        rfm69_transmit((uint8_t*)buf, buflen);
        delay_ms(10);
        gpio_clear(LED_ACT_PORT, LED_ACT);

        delay_ms(1000);
    }

    return 0;
}

