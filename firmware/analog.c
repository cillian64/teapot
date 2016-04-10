#include <stdint.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>

#include "analog.h"
#include "util.h"

void analog_init(void)
{
    rcc_periph_clock_enable(RCC_ADC1);
    /* Check ADC is asleep and start its clock */
    adc_power_off(ADC1);
    adc_set_clk_source(ADC1, ADC_CLKSOURCE_PCLK_DIV2);

    /* Initiate calibration and block til completion */
    adc_calibrate_start(ADC1);
    adc_calibrate_wait_finish(ADC1);

    /* Settings */
    adc_set_operation_mode(ADC1, ADC_MODE_SEQUENTIAL);
    adc_set_right_aligned(ADC1);
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPTIME_239DOT5);

    /* Default to 12-bit ADC */

    /* Bring up the ADC and wait for it to settle */
    adc_power_on(ADC1);
    while(!(ADC_ISR(ADC1) & ADC_ISR_ADRDY));
}

uint8_t get_light(void)
{
    uint8_t channel=3;
    uint16_t raw;
    /* Choose a channel */
    adc_set_regular_sequence(ADC1, 1, &channel);
    
    /* Start conversion and block */
    adc_start_conversion_regular(ADC1);
    while(!adc_eoc(ADC1));

    raw = adc_read_regular(ADC1);
    /* Convert 12-bit to 8-bit: */
    raw = raw >> 4;

    return raw;
}

uint8_t get_batt(void)
{
    uint8_t channel=2;
    volatile uint32_t working = 0;
    volatile uint16_t raw = 0;

    adc_set_regular_sequence(ADC1, 1, &channel);
    adc_start_conversion_regular(ADC1);
    while(!adc_eoc(ADC1));
    raw = adc_read_regular(ADC1);

    working = raw & 0x0fff;
    working *= 330;
    working /= 0x1000;

    if(working > 255) /* Can't handle voltages higher than 2.55V */
        panic();
    return (uint8_t)working;
}
