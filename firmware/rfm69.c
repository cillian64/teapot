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
static void spi_send8(uint32_t spi, uint8_t data);
static uint8_t spi_read8(uint32_t spi);
/* Send and receive 8 bits, synchronously */
static uint8_t _rfm69_spi_xfer8(uint8_t data);
/* Write a byte to a register */
static void _rfm69_writereg(uint8_t address, uint8_t data);
/* Read a byte from a register */
static uint8_t _rfm69_readreg(uint8_t address);
/* Bulk write to registers from a buffer */
static void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len);
/* Bulk read from registers into a buffer */
static void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len);
/* Set op mode */
static void _rfm69_setmode(uint8_t mode);
/* Get op mode */
static uint8_t _rfm69_getmode(void);

/************* Internal function definitions ***********/
static void spi_send8(uint32_t spi, uint8_t data)
{
    SPI_DR8(spi) = data;
}

static uint8_t spi_read8(uint32_t spi)
{
    while(!(SPI_SR(spi) & SPI_SR_RXNE));
    return SPI_DR8(spi);
}

static uint8_t _rfm69_spi_xfer8(uint8_t data)
{
    spi_send8(SPI1, data);
    return spi_read8(SPI1);
}

static void _rfm69_writereg(uint8_t address, uint8_t data)
{
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address | (1<<7)); /* Set MSB to write */
    (void)_rfm69_spi_xfer8(data);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
}

static uint8_t _rfm69_readreg(uint8_t address)
{
    uint8_t data;
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address & 0b01111111); /* Clear MSB to read*/
    data = _rfm69_spi_xfer8(0x00);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
    return data;
}

static void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    gpio_clear(RFM_NSS_PORT, RFM_NSS);
    (void)_rfm69_spi_xfer8(address | 0b10000000); /* Set MSB to write */
    (void)_rfm69_spi_xfer8(len); /* Now send packet length */
    for(i=0; i<len; i++) /* Now send whole packet */
        (void)_rfm69_spi_xfer8(buffer[i]);
    gpio_set(RFM_NSS_PORT, RFM_NSS);
}

static void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len)
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

    /* Wait for RFM to warm up */
    delay_ms(10);

    /* Set the frequency:
     * Fstep = Fxosc / 2^19 = 32e6 / 2^19
     * freq = Fstep * FRF
     * FRF = freq / (32e6 / 2^19)
     *     = 869.5 / 32 * 2^19 = 14245888 */
    rfm69_setfreq(14245888);
}

/* Set frequency.  The value provided is not a frequency in Hz, it is he FRF
 * value put in the register.  See the datasheet for conversion */
void rfm69_setfreq(uint32_t frf)
{
    /* Check we're asleep */
    _rfm69_setmode(RFM69_OPMODE_SLEEP);

    /* Program 3 FRF registers */
    _rfm69_writereg(RFM69_REGFRFMSB, (frf << 16) & 0xff);
    _rfm69_writereg(RFM69_REGFRFMID, (frf << 8) & 0xff);
    _rfm69_writereg(RFM69_REGFRFLSB, frf & 0xff);
}

/* Get rfm69 mode */
static uint8_t _rfm69_getmode(void)
{
    uint8_t RegOpMode;
    RegOpMode = _rfm69_readreg(RFM69_REGOPMODE);
    return (RegOpMode & 0b00011100) >> 2;
}

/* Change rfm69 opmode. Options are found under RegOpMode in rfm69.h */
static void _rfm69_setmode(uint8_t mode)
{
    uint8_t RegOpMode;

    if(mode > RFM69_OPMODE_RX)
        panic();

    RegOpMode = _rfm69_readreg(RFM69_REGOPMODE);
    RegOpMode &= 0b11100011;
    RegOpMode |= mode << 2;
    _rfm69_writereg(RFM69_REGOPMODE, RegOpMode);

    /* Wait for new mode to take effect: */
/*    volatile uint8_t themode=0xff;
    while(themode != mode)
    {
        themode = _rfm69_getmode();
        themode = themode & 0b01111111;
    }*/
    /*while(_rfm69_getmode() != mode);*/
}

/* Transmit bytes from buffer `buf', length `len' bytes.  This function is
 * synchronous - it will not return until transmission is complete */
void rfm69_transmit(uint8_t *buf, uint8_t len)
{
    /* If we are in transmit, wait for transmit to finish */
    while(_rfm69_getmode() == RFM69_OPMODE_TX);

    /* If we are in sleep, fs or rx, bring us up to standby */
    uint8_t mode = _rfm69_getmode();
    if(mode == RFM69_OPMODE_SLEEP || mode == RFM69_OPMODE_FS ||
       mode == RFM69_OPMODE_RX)
    {
        _rfm69_setmode(RFM69_OPMODE_STDBY);
        while(_rfm69_getmode() != RFM69_OPMODE_STDBY);
    }

    /* Write the packet to the RFM69's FIFO */
    _rfm69_bulkwrite(RFM69_REGFIFO, buf, len);

    /* Initiate transmit */
    _rfm69_setmode(RFM69_OPMODE_TX);

    /* Block until transmit completes */
    while(_rfm69_getmode() == RFM69_OPMODE_TX);
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

