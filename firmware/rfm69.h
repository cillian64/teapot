#ifndef RFM69_H
#define RFM69_H

#include <stdint.h>

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
#define RFM69_REGPACKETCONFIG1  0x37
#define RFM69_REGPAYLOADLENGTH  0x38
#define RFM69_REGPACKETCONFIG2  0x3D
#define RFM69_REGTESTPA1        0x5A
#define RFM69_REGTESTPA2        0x5C

/* RegOpMode */
#define RFM69_OPMODE_SLEEP      0x00
#define RFM69_OPMODE_STDBY      0x01
#define RFM69_OPMODE_FS         0x02
#define RFM69_OPMODE_TX         0x03
#define RFM69_OPMODE_RX         0x04

void rfm69_init(void);
void rfm69_setfreq(uint32_t frf);
void rfm69_opmode(uint8_t opmode);
void rfm69_transmit(uint8_t *buf, uint8_t len);
void rfm69_receive(uint8_t *buf, uint8_t len);
void rfm69_setpower(uint8_t power);

#endif
