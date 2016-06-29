/* Analog side of matters: read battery voltage and light level
 * Based on Matt Coates' example code */

#include "ch.h"
#include "hal.h"

volatile uint32_t batt_millivolts;
volatile uint32_t light_level;

static const ADCConversionGroup adcgrpcfg1 = {
// Converting 2 channels: Battery (IN0) and light (IN3)
    FALSE,              // Non-circular buffer
    2,                  // Number of channels
    NULL,               // No callback
    NULL,               // No error callback
    0,                  // CR1
    0,                  // TR
    ADC_SMPR_SMP_71P5,  // SMPR
    (1<<0) | (1<<3)     // CHSELR
};

THD_WORKING_AREA(waThreadAnalog, 128);
THD_FUNCTION(ThreadAnalog, arg) {
    adcsample_t samples[2];
    volatile uint16_t batt_raw;
    volatile uint16_t light_raw;

    palSetLine(LINE_LED_GREEN);

    (void)arg;
    chRegSetThreadName("analog");

    adcStart(&ADCD1, NULL);

    palSetLine(LINE_LED_YELLOW);

    while(true) {
        adcConvert(&ADCD1, &adcgrpcfg1, samples, 2);
        batt_raw = samples[0];
        light_raw = samples[1];
        chThdSleepMilliseconds(100);
    }
}
