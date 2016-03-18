#ifndef TEAPOT_PINS_H
#define TEAPOT_PINS_H

#include <libopencm3/stm32/gpio.h>

void teapot_pins_init(void);

/* Clock GPIOs, set pin modes */

/* LEDs */
#define LED_ACT           GPIO1
#define LED_ACT_PORT      GPIOA
#define LED_ERR          GPIO0
#define LED_ERR_PORT     GPIOA

/* Analog inputs, plus LIGHT_EN */
#define BATT_MON            GPIO2
#define BATT_MON_PORT       GPIOA
#define LIGHT_SENSE         GPIO3
#define LIGHT_SENSE_PORT    GPIOA
#define LIGHT_EN            GPIO4
#define LIGHT_EN_PORT       GPIOA

/* Radio */
#define RFM_RESET           GPIO10
#define RFM_RESET_PORT      GPIOA
#define RFM_NSS             GPIO15
#define RFM_NSS_PORT        GPIOA
#define RFM_SCK             GPIO3
#define RFM_SCK_PORT        GPIOB
#define RFM_MISO            GPIO4
#define RFM_MISO_PORT       GPIOB
#define RFM_MOSI            GPIO5
#define RFM_MOSI_PORT       GPIOB
#define RFM_DIO0            GPIO8
#define RFM_DIO0_PORT       GPIOA
#define RFM_DIO4            GPIO9
#define RFM_DIO4_PORT       GPIOA

/* I2C */
#define I2C_SCL             GPIO6
#define I2C_SCL_PORT        GPIOB
#define I2C_SDA             GPIO7
#define I2C_SDA_PORT        GPIOB


#endif
