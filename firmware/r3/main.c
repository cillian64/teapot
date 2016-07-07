/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <string.h>

#include "ch.h"
#include "hal.h"
#include "ch_test.h"

#include "analog.h"
#include "rfm69.h"
#include "ukhasnet.h"
#include "grid-eye.h"
#include "sensors.h"

#ifdef SEMIHOSTING
#include <stdio.h>
#endif

static const I2CConfig i2cconfig = {
    1<<31 | 1<<30 | 1<<29 | 1<<28, // TIMINGR
    0,      // CR1
    0,      // CR2
};

/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 64);
static THD_FUNCTION(Thread1, arg)
{
    (void)arg;
    chRegSetThreadName("runthread");

}


#ifdef SEMIHOSTING
void initialise_monitor_handles(void);

/* Puts with no newline */
void puts_non(char *str);
void puts_non(char *str)
{
    for(uint32_t i=0; i<strlen(str); i++)
        putchar(str[i]);
}
#endif

int main(void)
{
    halInit();
    chSysInit();

    palClearLine(LINE_LED_YELLOW);
    palClearLine(LINE_LED_GREEN);

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, world.");
#endif

    uint16_t *pixels = chHeapAlloc(NULL, 64*sizeof(uint16_t));
    uint8_t *packet_buf = chHeapAlloc(NULL, 48*sizeof(uint8_t));

    packet_buf[0] = 'G';
    packet_buf[1] = 'R';
    packet_buf[2] = 'I';
    packet_buf[3] = 'D';

    while(true)
    {

        palSetLine(LINE_LED_GREEN);
        spiStop(&SPID1);
        i2cStart(&I2CD1, &i2cconfig);
        grideye_get(pixels);
        i2cStop(&I2CD1);

        ukhasnet_radio_init();
        packet_buf[4] = '1';
        memcpy(packet_buf+6, (uint8_t*)pixels, 43);
        rfm69_transmit(packet_buf, 48);

        packet_buf[4] = '2';
        memcpy(packet_buf+6, (uint8_t*)pixels + 43, 43);
        rfm69_transmit(packet_buf, 48);

        packet_buf[4] = '3';
        memcpy(packet_buf+6, (uint8_t*)pixels + 86, 42);
        rfm69_transmit(packet_buf, 47);

        palClearLine(LINE_LED_GREEN);
    }
}
