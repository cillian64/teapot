#include <stdint.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"

#include "util.h"
#include "grid-eye.h"

/* Retrieve the state of the grid-eye array, writing it to the "pixels" array.
 * Pixels is a 64-element 8-by-8 matrix of uint16_t values. */
void grideye_get(uint16_t *pixels)
{
    uint8_t tx_buf[1], rx_buf[128];
    msg_t result;

    // Transmit address to read from:
    tx_buf[0] = 0x80; /* Lower level of pixel 1 */

    /* We dump 128-bytes read from the grid-eye to rx_buf.  Then we must
     * combine the 8-bit values to the 16-bit array in pixels */

    result = i2cMasterTransmitTimeout(&I2CD1,
                                      0b1101000,        // address
                                      tx_buf, 1,        // tx buffer and length
                                      rx_buf, 128,      // rx buffer and length
                                      TIME_INFINITE);   // No timeout
    if(result != MSG_OK)
        panic();

    for(uint8_t i=0; i<64; i++)
        pixels[i] = rx_buf[2*i] | ((uint16_t)rx_buf[2*i + 1] << 8);
}

