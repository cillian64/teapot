#include <libopencm3/stm32/gpio.h>

#include "teapot_pins.h"
#include "util.h"


/* If something goes wrong, turn on the ERR (error) LED and hang here.  In
 * debugging this makes it clear that something went wrong.  In production the
 * watchdog will catch us and reset (eventually).
 */
void panic(void)
{
    gpio_set(LED_ERR_PORT, LED_ERR);
    while(true);
}

/* Delay a number of milliseconds by hard-looping.  Not very precise or
 * calibrated. No guarantees. */
void delay_ms(const uint32_t delay)
{
    uint32_t i, j;
    for(i=0; i<delay; i++)
        for(j=0; j<3333; j++)
            __asm__("nop");
}

