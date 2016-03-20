#include <stdint.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>

#include "light.h"

void light_init(void)
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
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPTIME_071DOT5);
    adc_set_resolution(ADC1, ADC_RESOLUTION_8BIT);

    /* Bring up the ADC and wait for it to settle */
    adc_power_on(ADC1);
    while(!(ADC_ISR(ADC1) & ADC_ISR_ADRDY));
}

uint8_t get_light(void)
{
    uint8_t channel=3;
    /* Choose a channel */
    adc_set_regular_sequence(ADC1, 1, &channel);

    /* Start conversion and block */
    adc_start_conversion_regular(ADC1);
    while(!adc_eoc(ADC1));

    return adc_read_regular(ADC1);
}

