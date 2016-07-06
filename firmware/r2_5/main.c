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
#include "chprintf.h"

#include "rfm69.h"
#include "ukhasnet.h"
#include "usbcfg.h"

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");

  while (true) {
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(50);
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(950);
  }
}


int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /* LED heartbeat thread */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /* Clear errors */
  palClearLine(LINE_LED_YELLOW);

  ukhasnet_radio_init();

  /* Start up USB-serial driver */
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);

  /* Activate USB driver and bus pull-up on D+.  The delay means we don't have
   * to disconnect the cable after a reset. */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  uint8_t rxbuf[64];
  uint8_t packet_len;

  while (true) {
    packet_len = rfm69_receive(rxbuf, 64);

#ifndef GATEWAY
    /* Append a NULL character so we can use printf as a string */
    rx_buf[packet_len] = '\0';
    chprintf(&SDU1, "%s\n", rx_buf);
#endif

#ifdef REPEATER
    packet_len = ukhasnet_addhop(rxbuf, packet_len, "TEA0", 64);
    ukhasnet_transmit(rxbuf, packet_len);
#endif
  }
}
