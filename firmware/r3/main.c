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
#include <string.h>
#endif

/*
 * Blue LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg)
{
    (void)arg;
    chRegSetThreadName("blinker1");
    while (true)
    {
        palClearPad(GPIOA, GPIOA_LED_GREEN);
        chThdSleepMilliseconds(500);
        palSetPad(GPIOA, GPIOA_LED_GREEN);
        chThdSleepMilliseconds(500);
    }
}

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg)
{
    (void)arg;
    chRegSetThreadName("blinker2");
    while (true)
    {
        palClearPad(GPIOB, GPIOB_LED_YELLOW);
        chThdSleepMilliseconds(250);
        palSetPad(GPIOB, GPIOB_LED_YELLOW);
        chThdSleepMilliseconds(250);
    }
}

static const I2CConfig i2cconfig = {
    1<<31 | 1<<30 | 1<<29 | 1<<28, // TIMINGR
    0,      // CR1
    0,      // CR2
};

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

    i2cStart(&I2CD1, &i2cconfig);
    ukhasnet_radio_init();

    uint16_t pixels[64];

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
    puts("Hello, world.");
#endif

    while (true)
    {
        chThdSleepMilliseconds(1000);
    }
}
