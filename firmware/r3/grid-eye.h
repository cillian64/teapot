#ifndef GRID_EYE_H
#define GRID_EYE_H

/* Retrieve the state of the grid-eye array, writing it to the "pixels" array.
 * Pixels is a 64-element 8-by-8 matrix of uint16_t values. */
void grideye_get(uint16_t *pixels);

#endif // GRID_EYE_H
