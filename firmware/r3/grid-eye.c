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

    /* With the teapot mounted radio-side-up (silk correct orientation)
     * the grid-eye is also correctly orientated, window at the top.
     * Pixels are ordered right-to-left then bottom-to-top.
     * Ideally we want pixels in standard image/reading order,
     * left-to-right then top-to-bottom.
     * To do this we just reverse the pixel order. (Alternatively the teapot
     * could be inverted */

    for(uint8_t i=0; i<64; i++)
        pixels[i] = rx_buf[2*i] | ((uint16_t)rx_buf[2*i + 1] << 8);
}


// Celcius * 4
static uint16_t LUT[16] = {
    -48,
    -24,
    -12,
    -6,
    -4
    -3,
    -2
    -1,
    1,
    2,
    3,
    4,
    6,
    12,
    24,
    48
};


static uint8_t reverse_LUT(int8_t raw)
{
    for(uint8_t i=0; i<16; i++)
        if(raw < LUT[i])
            return i;
    return 15;
}


uint16_t grideye_pack(uint16_t *raw, uint8_t *done)
{
    int32_t average = 0;
    for(uint8_t i=0; i<64; i++)
        average += raw[i];
    average /= 64;

    for(uint8_t i=0; i<32; i++)
    {
        uint8_t high = reverse_LUT((int8_t)raw[2*i] - average);
        uint8_t low = reverse_LUT((int8_t)raw[2*i+1] - average);
        done[i] = (high << 4) | low;
    }
    return average;
}

