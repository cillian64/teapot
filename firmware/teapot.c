#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define LED_YELLOW_RCC RCC_GPIOA
#define LED_YELLOW_PORT GPIOA
#define LED_YELLOW_PIN GPIO0

#define LED_GREEN_RCC RCC_GPIOA
#define LED_GREEN_PORT GPIOA
#define LED_GREEN_PIN GPIO1

static void _delay_ms(const uint32_t delay)
{
    uint32_t i, j;

    for( i = 0; i < delay; i++ )
        for( j = 0; j < 500; j++)
            __asm__("nop");
}


int main(void)
{

    rcc_periph_clock_enable(LED_GREEN_RCC);
    gpio_mode_setup(LED_GREEN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    LED_GREEN_PIN);
    gpio_mode_setup(LED_YELLOW_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    LED_YELLOW_PIN);

    while(true)
    {
        gpio_set(LED_GREEN_PORT, LED_GREEN_PIN);
        gpio_clear(LED_YELLOW_PORT, LED_YELLOW_PIN);
        _delay_ms(500);
        gpio_set(LED_YELLOW_PORT, LED_YELLOW_PIN);
        gpio_clear(LED_GREEN_PORT, LED_GREEN_PIN);
        _delay_ms(500);
    }

    return 0;
}

