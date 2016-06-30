#include <stdbool.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "rfm69.h"
#include "util.h"

/* #define SEMIHOSTING */
#ifdef SEMIHOSTING
#include <stdio.h>
#endif

/*********** Internal function declarations ************/
static uint8_t _rfm69_spi_xfer8(uint8_t data);
/* Write a byte to a register */
static void _rfm69_writereg(uint8_t address, uint8_t data);
/* Read a byte from a register */
static uint8_t _rfm69_readreg(uint8_t address);
/* Bulk write to registers from a buffer */
static void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len);
/* Bulk write to registers from a buffer with length */
static void _rfm69_bulkwritewithlen(uint8_t address, uint8_t *buffer, uint8_t len);
/* Bulk read from registers into a buffer */
static void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len);
/* Set op mode */
static void _rfm69_setmode(uint8_t mode);
/* Get op mode */
static uint8_t _rfm69_getmode(void);

/************* Internal function definitions ***********/
static uint8_t _rfm69_spi_xfer8(uint8_t data)
{
    uint8_t rx_buf = 0;
    spiExchange(&SPID1, 1, &data, &rx_buf);
    return rx_buf;
}

static void _rfm69_writereg(uint8_t address, uint8_t data)
{
    palClearLine(LINE_RFM_NSS);
    (void)_rfm69_spi_xfer8(address | (1<<7)); /* Set MSB to write */
    (void)_rfm69_spi_xfer8(data);
    palSetLine(LINE_RFM_NSS);
}

static uint8_t _rfm69_readreg(uint8_t address)
{
    uint8_t data;
    palClearLine(LINE_RFM_NSS);
    (void)_rfm69_spi_xfer8(address & 0b01111111); /* Clear MSB to read*/
    data = _rfm69_spi_xfer8(0x00);
    palSetLine(LINE_RFM_NSS);
    return data;
}

static void _rfm69_bulkwrite(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    palClearLine(LINE_RFM_NSS);
    (void)_rfm69_spi_xfer8(address | 0b10000000); /* Set MSB to write */
    for(i=0; i<len; i++) /* Now send whole packet */
        (void)_rfm69_spi_xfer8(buffer[i]);
    palSetLine(LINE_RFM_NSS);
}

static void _rfm69_bulkwritewithlen(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    palClearLine(LINE_RFM_NSS);
    (void)_rfm69_spi_xfer8(address | 0b10000000); /* Set MSB to write */
    (void)_rfm69_spi_xfer8(len); /* Now send packet length */
    for(i=0; i<len; i++) /* Now send whole packet */
        (void)_rfm69_spi_xfer8(buffer[i]);
    palSetLine(LINE_RFM_NSS);
}

static void _rfm69_bulkread(uint8_t address, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    palClearLine(LINE_RFM_NSS);
    (void)_rfm69_spi_xfer8(address & 0b01111111); /* Clear MSB to read */
    for(i=0; i<len; i++)
        buffer[i] = _rfm69_spi_xfer8(0x00);
    palSetLine(LINE_RFM_NSS);
}

static const SPIConfig spiconfig = {
    NULL,           // Finish callback
    GPIOA,          // NSS port
    GPIOA_RFM_NSS,  // NSS pad number
    0,              // CR1
    0               // CR2
};

/************* External function definitions ***********/
/* Initialise RFM */
void rfm69_init(void)
{
    spiStart(&SPID1, &spiconfig);
    palSetLine(LINE_RFM_NSS);

    /* Release RESET and wait for RFM to warm up */
    palClearLine(LINE_RFM_RESET);
    chThdSleepMilliseconds(10);

    if(_rfm69_readreg(RFM69_REGVERSION) != 0x24)
        panic();

    /* Set tx to start as soon as we start filling the FIFO */
    uint8_t RegFifoThresh = 0x00;
    RegFifoThresh |= RFM69_REGFIFOTHRESH_TXSTARTCONDITION;
    _rfm69_writereg(RFM69_REGFIFOTHRESH, RegFifoThresh);
}

/* Set frequency.  The value provided is not a frequency in Hz, it is he FRF
 * value put in the register.  See the datasheet for conversion */
void rfm69_setfreq(uint32_t frf)
{
    /* Check we're asleep */
    _rfm69_setmode(RFM69_OPMODE_SLEEP);

    /* Program 3 FRF registers */
    _rfm69_writereg(RFM69_REGFRFMSB, (frf >> 16) & 0xff);
    _rfm69_writereg(RFM69_REGFRFMID, (frf >> 8) & 0xff);
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

#ifdef SEMIHOSTING
/* Convert a number from 0-15 into a hex digit character */
char dtoh(uint8_t digit)
{
    if(digit<=9)
        return '0'+digit;
    else if(digit<=15)
        return 'a'+digit-10;
    else
        panic();
    return ' ';  /* Otherwise it appears we may not return */
}

/* Print out all the RFM69 registers from 0x00 to 0x70 using semihosting */
void dumpregisters(void)
{
    /* printf with %x and %d format specifiers is too big for our ROM.
     * So do a simple DIY */
    for(uint8_t addr=0; addr<0x71; addr++)
    {
        uint8_t data = _rfm69_readreg(addr);
        fputs("addr 0x", stdout);
        putc(dtoh(addr/16), stdout);
        putc(dtoh(addr%16), stdout);
        fputs(": ", stdout);
        for(uint8_t i=0; i<8; i++)
        {
            putc(dtoh((data>>(7-i))%2), stdout);
            if(i==3)
                putc(' ', stdout);
        }
        putc('\n', stdout);
        if(addr%16 == 15)
            putc('\n', stdout);
    }
}
#endif /* SEMIHOSTING */

/* Transmit bytes from buffer `buf', length `len' bytes.  This function is
 * synchronous - it will not return until transmission is complete */
void rfm69_transmit(uint8_t *buf, uint8_t len)
{
    /* Go into transmit mode */
    _rfm69_setmode(RFM69_OPMODE_TX);
    while(_rfm69_getmode() != RFM69_OPMODE_TX);

    /* Wait for PA ramp-up */
    while(!(_rfm69_readreg(RFM69_REGIRQFLAGS1) & RFM69_REGIRQFLAGS1_TXREADY));

    /* Write the packet to the RFM69's FIFO */
    _rfm69_bulkwritewithlen(RFM69_REGFIFO, buf, len);

    /* Wait for send to complete */
    while(!(_rfm69_readreg(RFM69_REGIRQFLAGS2) &
            RFM69_REGIRQFLAGS2_PACKETSENT));

    /* Return to standby */
    _rfm69_setmode(RFM69_OPMODE_STDBY);
    while(_rfm69_getmode() != RFM69_OPMODE_STDBY);
}

/* Receive `len' bytes into buffer `buf'.  This function
 * is synchronous - it will not return until reception is complete */
void rfm69_receive(uint8_t *buf, uint8_t len)
{
    panic();
}

/* Set the transmit power.  `power' is a power in dBm from +2dBm to +17dBm */
void rfm69_setpower(int8_t power)
{
    uint8_t RegPaLevel = 0x00;

    if((power < 2) || (power > 17))
        panic();
    
    RegPaLevel &= RFM69_PALEVEL_PA0ON;
    RegPaLevel |= RFM69_PALEVEL_PA1ON;
    RegPaLevel |= RFM69_PALEVEL_PA2ON;

    /* With this PA setup, Pout = -14dBm + OutputPower */
    uint8_t OutputPower = (uint8_t)(power + 14);
    OutputPower &= 0b00011111;
    RegPaLevel |= OutputPower;

    _rfm69_writereg(RFM69_REGPALEVEL, RegPaLevel);
}

/* Setup physical laye settings.
 * fdev is frequency deviation in dimensionless hoperf units
 * bitrate is bitrate in dimensionless hoperf units */
void rfm69_physetup(uint16_t fdev, uint16_t bitrate)
{
    /* Write deviation */
    _rfm69_writereg(RFM69_REGFDEVMSB, (fdev >> 8) & 0b00111111);
    _rfm69_writereg(RFM69_REGFDEVLSB, fdev & 0xff);

    /* Write bitrate */
    _rfm69_writereg(RFM69_REGBITRATEMSB, (bitrate >> 8) & 0xff);
    _rfm69_writereg(RFM69_REGBITRATELSB, bitrate & 0xff);
}

/* Setup packet-mode settings.
 * variablelength: Do we want to include a length with each packet?
 * preamblelength: number of preamble bytes
 * synclength: number of sync bytes, 1-8
 * syncvalue: values of sync bytes */
void rfm69_packetsetup(bool variablelength, uint16_t preamblelength,
                       uint8_t synclength, uint8_t *syncvalue,
                       bool manchester, bool whitening, bool crc)
{
    uint8_t RegPacketConfig1 = 0x00;
    uint8_t RegSyncConfig = 0x00;

    /* Validate parameters */
    if(whitening && manchester)
        panic(); /* Can't do both */
    if(synclength > 8)
        panic(); /* Can only do 8 sync bytes */


    if(variablelength)
        RegPacketConfig1 |= RFM69_REGPACKETCONFIG1_PACKETFORMAT;
    if(whitening)
        RegPacketConfig1 |= RFM69_REGPACKETCONFIG1_WHITENING;
    if(manchester)
        RegPacketConfig1 |= RFM69_REGPACKETCONFIG1_MANCHESTER;
    if(crc)
        RegPacketConfig1 |= RFM69_REGPACKETCONFIG1_CRCON;
    _rfm69_writereg(RFM69_REGPACKETCONFIG1, RegPacketConfig1);

    /* Preamble length */
    _rfm69_writereg(RFM69_REGPREAMBLEMSB, (preamblelength >> 8) & 0xff);
    _rfm69_writereg(RFM69_REGPREAMBLELSB, preamblelength & 0xff);

    if(synclength > 0)
    {
        RegSyncConfig |= RFM69_REGSYNCCONFIG_SYNCON;
        RegSyncConfig |= (synclength - 1) << 3;
        /* Sync values are sequential in memory so we can bulkwrite them all */
        _rfm69_bulkwrite(RFM69_REGSYNCVALUE1, syncvalue, synclength);
    }
    _rfm69_writereg(RFM69_REGSYNCCONFIG, RegSyncConfig);


}

