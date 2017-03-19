/* Analog side of matters: read battery voltage and light level
 * Based on Matt Coates' example code */

#include "ch.h"
#include "hal.h"

const ADCConversionGroup adcgrpcfg1 = {
// Converting 2 channels: Battery (PA0/IN0) and light (PA3/IN3)
    false,              // Non-circular buffer
    2,                  // Number of channels
    NULL,               // No callback
    NULL,               // No error callback
    0,                  // cfgr1
    0,                  // TR
    ADC_SMPR_SMP_71P5,  // SMPR
    (1<<0) | (1<<3)     // CHSELR
};


static uint8_t convert_battery(adcsample_t batt_raw)
{
    // Full scale 2**12 == 3.3V
    // Return battery voltage in 0.01V increments
    return (uint32_t)batt_raw * 330 / 4095;
}

static uint16_t convert_light(adcsample_t light_raw)
{
    // TEPT4400 provides ~2uA/lx
    // With a 10k sense resistor this is 0.02V/lx
    // So full scale 3.3V is equivalent to 165lx
    return (uint32_t)light_raw * 165 / 4095;
}


void analog_read(uint8_t *battery, uint16_t *light)
{
    adcsample_t samples[2];

    palSetLine(LINE_LIGHT_EN);
    chThdSleepMilliseconds(10);
    adcStart(&ADCD1, NULL);
    adcConvert(&ADCD1, &adcgrpcfg1, samples, 1);
    adcStop(&ADCD1);
    palClearLine(LINE_LIGHT_EN);
    *battery = convert_battery(samples[0]);
    *light = convert_light(samples[1]);
}

void analog_init(void)
{
    // Enable VBAT channel.  Need ADC to be stopped.
    adcStop(&ADCD1);
    adcSTM32SetCCR(0);
}
