#include <stdbool.h>
#include <stdint.h>

#include <libopencm3/stm32/gpio.h>

/* This is a bit naughty.  Officially libopencm3 doesn't include support for
 * the stm32l0 SPI peripheral.  However, it appears identical to the stm32l1
 * SPI peripheral.  Instead of patching libopencm3 we can directly include the
 * latter driver */
#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/memorymap.h>
#include <libopencm3/stm32/l1/spi.h>

#include "teapot_pins.h"
#include "rfm69.h"
#include "util.h"

/*********** Internal function declarations ************/
/* For some weird reason libopencm3 only provides spi_read8/send8 for f03
 * devices, not for l0. So we recreate them here */
#define SPI_DR8(spi_base) MMIO8((spi_base)+0x0c)
void spi_send8(uint32_t spi, uint8_t data);
uint8_t spi_read8(uint32_t spi);

/* Send and receive 8 bits, synchronously */
uint8_t _rfm69_spi_xfer8(uint8_t data);

/* Write a byte to a register */
void _rfm69_writereg(uint8_t address, uint8_t data);

/* Read a byte from a register */
uint8_t _rfm69_readreg(uint8_t address);

/* Bulk write to registers from a buffer */
void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len);

/* Bulk read from registers into a buffer */
void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len);

/************* Internal function definitions ***********/
void spi_send8(uint32_t spi, uint8_t data)
{
    SPI_DR8(spi) = data;
}
uint8_t spi_read8(uint32_t spi)
{
    while(!(SPI_SR(spi) & SPI_SR_RXNE));
    return SPI_DR8(spi);
}

uint8_t _rfm69_spi_xfer8(uint8_t data)
{
    spi_send8(SPI1, data);
    return spi_read8(SPI1);
}

void _rfm69_writereg(uint8_t address, uint8_t data)
{
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address | (1<<7)); /* Set MSB to write */
    (void)_rfm69_spi_xfer8(data);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
}

uint8_t _rfm69_readreg(uint8_t address)
{
    uint8_t data;
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address & 0b01111111); /* Clear MSB to read*/
    data = _rfm69_spi_xfer8(0x00);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
    return data;
}

void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address | 0b10000000); /* Set MSB to write */
    for(i=0; i<len; i++)
        (void)_rfm69_spi_xfer8(buffer[i]);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
}

void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address & 0b01111111); /* Clear MSB to read */
    for(i=0; i<len; i++)
        buffer[i] = _rfm69_spi_xfer8(0x00);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
}


/************* External function definitions ***********/
/* Initialise RFM */
void rfm69_init(void)
{
    /* Initialise SPI peripheral */
    spi_reset(SPI1);
    spi_disable_crc(SPI1);
    spi_init_master(SPI1,
                    SPI_CR1_BAUDRATE_FPCLK_DIV_64, /* 500kHz ? */
                    SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
                    SPI_CR1_CPHA_CLK_TRANSITION_1,
                    SPI_CR1_DFF_8BIT,
                    SPI_CR1_MSBFIRST);

    /* Manual NSS */
    spi_enable_software_slave_management(SPI1);
    spi_set_nss_high(SPI1);
    gpio_set(RFM_NSS_PORT, RFM_NSS);

    spi_enable(SPI1);

    /* Wait for RFM to warm up, then check we're in sleep mode */
    delay_ms(10);
    rfm69_opmode(RFM69_OPMODE_SLEEP);
}

/* Set frequency.  The value provided is not a frequency in Hz, it is he FRF
 * value put in the register.  See the datasheet for conversion */
void rfm69_setfreq(uint32_t frf)
{
    panic();
}

/* Change rfm69 opmode. Options are found under RegOpMode in rfm69.h */
void rfm69_opmode(uint8_t opmode)
{
    if(opmode > RFM69_OPMODE_RX)
        panic();

    panic();
}

/* Transmit bytes from buffer `buf', length `len' bytes.  This function is
 * synchronous - it will not return until transmission is complete */
void rfm69_transmit(uint8_t *buf, uint8_t len)
{
    panic();
}

/* Receive `len' bytes into buffer `buf'.  This function
 * is synchronous - it will not return until reception is complete */
void rfm69_receive(uint8_t *buf, uint8_t len)
{
    panic();
}

/* Set the transmit power.  `power' is a power in dBm */
void rfm69_setpower(uint8_t power)
{
    panic();
}

