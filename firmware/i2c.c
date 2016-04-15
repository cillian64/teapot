#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "i2c.h"
#include "util.h"
#include "teapot_pins.h"

uint8_t i2c_rx(void);
void i2c_tx(uint8_t data);

void i2c_init(void)
{
    /* Configure i2c clock: */
    RCC_CCIPR &= ~(RCC_CCIPR_I2C1SEL_MASK << RCC_CCIPR_I2C1SEL_SHIFT);
    RCC_CCIPR |= RCC_CCIPR_I2C1SEL_HSI16 << RCC_CCIPR_I2C1SEL_SHIFT;
    rcc_periph_clock_enable(RCC_I2C1);

    /* Ensure peripheral is off before we configure it */
    I2C1_CR1 &= ~I2C_CR1_PE;
    while(I2C1_CR1 & I2C_CR1_PE);

    /* Configure analog filters */
    /* Configure timing parameters */
    /* Configure clock stretching (if slave) */

    /* Assume we're using HSI16 as f_i2cclk = 16MHz */
    /* From l0 ref manual p674, for 100kHz standard i2c:
     * PRESC=3, SCLL=0x13, SCLH=0xf, SDADEL=0x2, SCLDEL=0x4 */
    I2C1_TIMINGR = 0x00000000;
    I2C1_TIMINGR |= 0x03 << 28; /* PRESC */
    I2C1_TIMINGR |= 0x04 << 20; /* SCLDEL */
    I2C1_TIMINGR |= 0x02 << 16; /* SDADEL */
    I2C1_TIMINGR |= 0x0f << 8;  /* SCLH */
    I2C1_TIMINGR |= 0x13 << 0;  /* SCLL */

    /* Turn peripheral back on */
    I2C1_CR1 |= I2C_CR1_PE;
    while(!(I2C1_CR1 & I2C_CR1_PE));

    /* Do not auto-end - we need repeated starts */
    I2C1_CR2 &= ~I2C_CR2_AUTOEND;

    /* Automagical ACK control */
    I2C1_CR2 &= ~I2C_CR2_RELOAD;
}

uint8_t i2c_rx(void)
{
    while(!(I2C1_ISR & I2C_ISR_RXNE));
    return I2C1_RXDR;
}

void i2c_tx(uint8_t data)
{
    while(!(I2C1_ISR & I2C_ISR_TXE));
    I2C1_TXDR = data;
}

void i2c_transfer(uint8_t addr, bool transmit, uint8_t nbytes,
                  uint8_t *buffer, bool stop)
{
/*    if(I2C1_CR2 & I2C_CR2_START)
        panic();*/

    /* Assume 7-bit addressing */
    I2C1_CR2 &= ~I2C_CR2_ADD10;
    I2C1_CR2 &= ~0xfe; /* Clear bits 1-7 */
    I2C1_CR2 |= (addr & 0x7f) << 1; /* Insert 7-bit addr at 1-7 */

    if(transmit)
        I2C1_CR2 &= ~I2C_CR2_RD_WRN;
    else
        I2C1_CR2 |= I2C_CR2_RD_WRN;
    
    I2C1_CR2 |= I2C_CR2_START;
    while(I2C1_CR2 & I2C_CR2_START); /* START cleared after slave addr sent
                                        regardless of ACK and also if
                                        arbitration lost */

    /* Check if NACK received: */
//    if(I2C1_ISR | I2C_ISR_NACKF)
//    {
//        panic();
//    }

    I2C1_CR2 &= ~(0xff << 16);
    I2C1_CR2 |= (uint32_t)nbytes << 16;

    for(uint8_t i=0; i<nbytes; i++)
        if(transmit)
            i2c_tx(buffer[i]);
        else
            buffer[i] = i2c_rx();

    if(stop)
        I2C1_CR2 |= I2C_CR2_STOP;
}

