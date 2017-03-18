#ifndef UKHASNET_H
#define UKHASNET_H

#include <stdbool.h>
#include <stdint.h>

/* Setup the RFM69 for UKHASnet operation */
void ukhasnet_radio_init(void);

/* Generate a ukhasnet packet in buf, with maximum length buf_len.
 * Return the length of the packet generated */
uint8_t makepacket(uint8_t *buf, uint8_t buf_len,
                   char *seq, char *label, /* Seq count, node label */
                   uint8_t hops,
                   bool has_battery, uint16_t voltage,   /* battery voltage */
                   bool has_temp, int16_t temp,         /* temperature, C*10 */
                   bool has_hum, uint8_t hum,           /* rel humidity, % */
                   bool has_press, uint32_t press,       /* Pressure, pascal */
                   bool has_light, uint8_t light,       /* Light sensor */
                   char *comment);

/* Add a hop to the hops field of a packet.
 * packet_len is the old length of the packet, including the terminating ']'
 * We return the new length of the packet, including the terminating ']'.
 * If the extended packet won't fit in the buffer length, buf_len, we panic
 * node_name should be a null-terminated string. */
uint8_t ukhasnet_addhop(uint8_t *buf, uint8_t packet_len, char *node_name,
                        uint8_t buf_len);

#endif
