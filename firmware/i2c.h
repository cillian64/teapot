#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

#define MMIO32(addr) (*(volatile uint32_t *)(addr))

/* Valid for stm32l0x2 */
#define I2C1_OFFSET (0x40005400)

#define I2C1_CR1 MMIO32(I2C1_OFFSET+0x00)
#define I2C1_CR2 MMIO32(I2C1_OFFSET+0x04)
#define I2C1_TIMINGR MMIO32(I2C1_OFFSET+0x10)
#define I2C1_ISR MMIO32(I2C1_OFFSET+0x18)
#define I2C1_RXDR MMIO32(I2C1_OFFSET+0x24)
#define I2C1_TXDR MMIO32(I2C1_OFFSET+0x28)

#define I2C_CR1_PE (1<<0)
#define I2C_CR1_TXIE (1<<1)
#define I2C_CR1_RXIE (1<<2)
#define I2C_CR1_ADDRIE (1<<3)
#define I2C_CR1_NACKIE (1<<4)
#define I2C_CR1_STOPIE (1<<5)
#define I2C_CR1_TCIE (1<<6)
#define I2C_CR1_ERRIE (1<<7)
#define I2C_CR1_ANFOFF (1<<12)
#define I2C_CR1_TXDMAEN (1<<14)
#define I2C_CR1_RXDMAEN (1<<15)
#define I2C_CR1_SBC (1<<16)
#define I2C_CR1_NOSTRETCH (1<<17)
#define I2C_CR1_WUPEN (1<<18)
#define I2C_CR1_GCEN (1<<19)
#define I2C_CR1_SMBHEN (1<<20)
#define I2C_CR1_SMBDEN (1<<21)
#define I2C_CR1_ALERTEN (1<<22)
#define I2C_CR1_PECEN (1<<23)

#define I2C_CR2_RD_WRN (1<<10)
#define I2C_CR2_ADD10 (1<<11)
#define I2C_CR2_HEAD10R (1<<12)
#define I2C_CR2_START (1<<13)
#define I2C_CR2_STOP (1<<14)
#define I2C_CR2_NACK (1<<15)
#define I2C_CR2_RELOAD (1<<24)
#define I2C_CR2_AUTOEND (1<<25)
#define I2C_CR2_PECBYTE (1<<26)

#define I2C_ISR_TXE (1<<0)
#define I2C_ISR_TXIS (1<<1)
#define I2C_ISR_RXNE (1<<2)
#define I2C_ISR_ADDR (1<<3)
#define I2C_ISR_NACKF (1<<4)
#define I2C_ISR_STOPF (1<<5)
#define I2C_ISR_TC (1<<6)
#define I2C_ISR_TCR (1<<7)
#define I2C_ISR_BERR (1<<8)
#define I2C_ISR_ARLO (1<<9)
#define I2C_ISR_OVR (1<<10)
#define I2C_ISR_PECERR (1<<11)
#define I2C_ISR_TIMEOUT (1<<12)
#define I2C_ISR_ALERT (1<<13)
#define I2C_ISR_BUSY (1<<15)
#define I2C_ISR_DIR (1<<16)


void i2c_init(void);
void i2c_transfer(bool addr10bit, uint16_t addr, bool transmit,
                  uint8_t nbytes, uint8_t *buffer);

#endif
