#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>

typedef struct flash_config_t {
    char nodeid[16];
    uint8_t ttl;
    uint32_t interval;
    bool has_battery;
    bool has_temperature;
    bool has_humidity;
    bool has_pressure;
    bool has_light;
    bool has_grideye;
} flash_config_t;

void flash_write_config(flash_config_t *config);
void flash_read_config(flash_config_t *config);

#endif
