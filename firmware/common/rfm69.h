#ifndef RFM69_H
#define RFM69_H

#include <stdint.h>
#include <stdbool.h>

/* Register locations: */
#define RFM69_REGFIFO           0x00
#define RFM69_REGOPMODE         0x01
#define RFM69_REGDATAMODUL      0x02
#define RFM69_REGBITRATEMSB     0x03
#define RFM69_REGBITRATELSB     0x04
#define RFM69_REGFDEVMSB        0x05
#define RFM69_REGFDEVLSB        0x06
#define RFM69_REGFRFMSB         0x07
#define RFM69_REGFRFMID         0x08
#define RFM69_REGFRFLSB         0x09
#define RFM69_REGVERSION        0x10
#define RFM69_REGRXBW           0x19
#define RFM69_REGOSC1           0x0A
#define RFM69_REGLISTEN1        0x0D
#define RFM69_REGLISTEN2        0x0E
#define RFM69_REGLISTEN3        0x0F
#define RFM69_REGPALEVEL        0x11
#define RFM69_REGDIOMAPPING1    0x25
#define RFM69_REGDIOMAPPING2    0x26
#define RFM69_REGIRQFLAGS1      0x27
#define RFM69_REGIRQFLAGS2      0x28
#define RFM69_REGRXTIMEOUT1     0x2A
#define RFM69_REGRXTIMEOUT2     0x2B
#define RFM69_REGPREAMBLEMSB    0x2C
#define RFM69_REGPREAMBLELSB    0x2D
#define RFM69_REGSYNCCONFIG     0x2E
#define RFM69_REGSYNCVALUE1     0x2F
#define RFM69_REGPACKETCONFIG1  0x37
#define RFM69_REGPAYLOADLENGTH  0x38
#define RFM69_REGFIFOTHRESH     0x3C
#define RFM69_REGPACKETCONFIG2  0x3D
#define RFM69_REGTESTPA1        0x5A
#define RFM69_REGTESTPA2        0x5C

/* RegOpMode */
#define RFM69_OPMODE_SLEEP      0x00
#define RFM69_OPMODE_STDBY      0x01
#define RFM69_OPMODE_FS         0x02
#define RFM69_OPMODE_TX         0x03
#define RFM69_OPMODE_RX         0x04

/* RegPaLevel */
#define RFM69_PALEVEL_PA0ON     (1<<7)
#define RFM69_PALEVEL_PA1ON     (1<<6)
#define RFM69_PALEVEL_PA2ON     (1<<5)

/* RegPacketConfig1 */
#define RFM69_REGPACKETCONFIG1_PACKETFORMAT (1<<7)
#define RFM69_REGPACKETCONFIG1_WHITENING    (1<<6)
#define RFM69_REGPACKETCONFIG1_MANCHESTER   (1<<5)
#define RFM69_REGPACKETCONFIG1_CRCON        (1<<4)

/* RegSyncConfig */
#define RFM69_REGSYNCCONFIG_SYNCON (1<<7)

/* RegIrqFlags1 */
#define RFM69_REGIRQFLAGS1_MODEREADY    (1<<7)
#define RFM69_REGIRQFLAGS1_RXREADY      (1<<6)
#define RFM69_REGIRQFLAGS1_TXREADY      (1<<5)
#define RFM69_REGIRQFLAGS1_PLLLOCK      (1<<4)
#define RFM69_REGIRQFLAGS1_RSSI         (1<<3)
#define RFM69_REGIRQFLAGS1_TIMEOUT      (1<<2)
#define RFM69_REGIRQFLAGS1_AUTOMODE     (1<<1)
#define RFM69_REGIRQFLAGS1_SYNCADDRESSMATCH (1<<0)

/* RegIrqFlags2 */
#define RFM69_REGIRQFLAGS2_FIFOFULL     (1<<7)
#define RFM69_REGIRQFLAGS2_FIFONOTEMPTY (1<<6)
#define RFM69_REGIRQFLAGS2_FIFOLEVEL    (1<<5)
#define RFM69_REGIRQFLAGS2_FIFOOVERRUN  (1<<4)
#define RFM69_REGIRQFLAGS2_PACKETSENT   (1<<3)
#define RFM69_REGIRQFLAGS2_PAYLOADREADY (1<<2)
#define RFM69_REGIRQFLAGS2_CRCOK        (1<<1)

/* RegFifoThresh */
#define RFM69_REGFIFOTHRESH_TXSTARTCONDITION    (1<<7)


void rfm69_init(void);
void rfm69_setfreq(uint32_t frf);
void rfm69_transmit(uint8_t *buf, uint8_t len);
uint8_t rfm69_receive(uint8_t *buf, uint8_t max_len);
void rfm69_setpower(int8_t power);
void rfm69_physetup(uint16_t fdev, uint16_t bitrate);
void rfm69_packetsetup(bool variablelength, uint16_t preamblelength,
                       uint8_t synclength, uint8_t *syncvalue,
                       bool manchester, bool whitening, bool crc);
void rfm69_spistart(void);

#endif
