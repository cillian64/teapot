#ifndef GRID_EYE_H
#define GRID_EYE_H

/* Retrieve the state of the grid-eye array, writing it to the "pixels" array.
 * Pixels is a 64-element 8-by-8 matrix of uint16_t values. */
void grideye_get(uint16_t *pixels);

/* Pack 64 uint16_t values into 32 uint8_t values, 4 bits per pixel.
 * Returns the average value, which is subtracted from the pixels.
 * Having subtracted the average a non-linear quantization is applied. */
uint16_t grideye_pack(uint16_t *raw, uint8_t *done);

#endif // GRID_EYE_H
