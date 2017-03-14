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
#include "hal_serial.h"

#include "rfm69.h"
#include "ukhasnet.h"
#include "usbcfg.h"


int main(void) {
  halInit();
  chSysInit();

  /* Clear LEDs */
  palClearLine(LINE_LED_YELLOW);
  palClearLine(LINE_LED_GREEN);

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

  uint8_t rx_buf[64];
  uint8_t packet_len;

  while (true) {
    packet_len = rfm69_receive(rx_buf, 64);

    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(50);

    // Gateway:
    streamWrite(&SDU1, rx_buf, packet_len);
    streamPut(&SDU1, '\n');

    // Repeater:
//    packet_len = ukhasnet_addhop(rx_buf, packet_len, "TEA0", 64);
//    ukhasnet_transmit(rx_buf, packet_len);

    palClearLine(LINE_LED_GREEN);
  }
}
