#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "teapot_pins.h"
#include "util.h"

void teapot_pins_init(void)
{
    /* Clock all GPIOs */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    /* LEDs - default off */
    gpio_clear(LED_ACT_PORT, LED_ACT);
    gpio_clear(LED_ERR_PORT, LED_ERR);
    gpio_mode_setup(LED_ACT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    LED_ACT);
    gpio_mode_setup(LED_ERR_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    LED_ERR);

    /* LIGHT_EN */
    gpio_clear(LIGHT_EN_PORT, LIGHT_EN);
    gpio_mode_setup(LIGHT_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    LIGHT_EN);

    /* Analog inputs */
    gpio_mode_setup(BATT_MON_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, BATT_MON);
    gpio_mode_setup(LIGHT_SENSE_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE,
                    LIGHT_SENSE);

    /* Radio stuff */
    /* Bring up reset pin, hold in reset: */
    gpio_mode_setup(RFM_RESET_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
                    RFM_RESET);
    gpio_set(RFM_RESET_PORT, RFM_RESET);
    delay_ms(1); /* Check RFM gets reset on powerup */
    /* Setup SPI */
    rcc_periph_clock_enable(RCC_SPI1);
    /* Setup NSS for manual control. Check it doesn't blip low when we first
     * setup the pin. */
    gpio_set(RFM_NSS_PORT, RFM_NSS);
    gpio_mode_setup(RFM_NSS_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, RFM_NSS);
    /* Now the rest of the SPI pins */
    gpio_mode_setup(RFM_SCK_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, RFM_SCK);
    gpio_mode_setup(RFM_MISO_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, RFM_MISO);
    gpio_mode_setup(RFM_MOSI_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, RFM_MOSI);
    gpio_set_af(RFM_SCK_PORT, GPIO_AF0, RFM_SCK);
    gpio_set_af(RFM_MISO_PORT, GPIO_AF0, RFM_MISO);
    gpio_set_af(RFM_MOSI_PORT, GPIO_AF0, RFM_MOSI);

    /* I2C bus */
    /* TODO: i2c stuff... 
    rcc_periph_clock_enable(RCC_I2C1);
    rcc_set_i2c_clock_hsi(I2C1);
    i2c_reset(I2C1);
    */
}

