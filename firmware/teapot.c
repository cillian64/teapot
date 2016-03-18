#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "teapot_pins.h"
#include "rfm69.h"
#include "util.h"


int main(void)
{
    teapot_pins_init();

    while(true)
    {
        gpio_set(LED_ACT_PORT, LED_ACT);
        gpio_clear(LED_ERR_PORT, LED_ERR);
        delay_ms(500);
        gpio_set(LED_ERR_PORT, LED_ERR);
        gpio_clear(LED_ACT_PORT, LED_ACT);
        delay_ms(500);
    }

    return 0;
}

