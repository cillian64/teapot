#ifndef ANALOG_H
#define ANALOG_H

void analog_init(void);
void analog_read(uint8_t *battery, uint16_t *light);

#endif /* ANALOG_H */
