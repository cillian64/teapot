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
    0,      // TIMINGR
    0,      // CR1
    0,      // CR2
};

void initialise_monitor_handles(void);

/* Puts with no newline */
void puts_non(char *str);
void puts_non(char *str)
{
    for(uint32_t i=0; i<strlen(str); i++)
        putchar(str[i]);
}

int main(void)
{
    halInit();
    chSysInit();

    palClearLine(LINE_LED_YELLOW);
    palClearLine(LINE_LED_GREEN);

    i2cStart(&I2CD1, &i2cconfig);

    uint16_t pixels[64];

#ifdef SEMIHOSTING
    initialise_monitor_handles();
    setbuf(stdout, NULL);
#endif

    while (true)
    {
        char str[32];
        chThdSleepMilliseconds(1000);
        grideye_get(pixels);

#ifdef SEMIHOSTING
        puts_non("\033[2J");
        for(uint8_t row=0; row<8; row++)
        {
            for(uint8_t col=0; col<8; col++)
            {
                uint8_t i = row*8 + col;
                str[0] = '0';
                if(pixels[i] < 100)
                    itoa(pixels[i], str+1, 10);
                else
                    itoa(pixels[i], str, 10);
                    
                puts_non(str);
                putchar(' ');

            }
            putchar('\n');
        }
#endif
    }
}
