#ifndef LOWPOWER_H
#define LOWPOWER_H

#include <stdint.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"

#include "lowpower.h"

static RTCAlarm rtc_alarm_cfg;
static RTCDateTime rtc_time;

/* Set up RTC wakeup timer in seconds */
void lowpower_set_wakeup_timer(uint32_t interval)
{
    uint8_t hours, minutes, seconds;
    uint8_t hours_tens, hours_units;
    uint8_t minutes_tens, minutes_units;
    uint8_t seconds_tens, seconds_units;

    // We only use time, not days, so only need to zero millis
    rtc_time.millisecond = 0;
    rtcSetTime(&RTCD1, &rtc_time);

    // Ignore date and day-of-week, just set time.
    rtc_alarm_cfg.alrmr = RTC_ALRMAR_MSK4 | RTC_ALRMAR_WDSEL;
    hours = interval / 3600;
    hours_tens = hours / 10;
    hours_units = hours % 10;
    minutes = (interval % 3600) / 60;
    minutes_tens = minutes / 10;
    minutes_units = minutes % 10;
    seconds = (interval % 60);
    seconds_tens = seconds / 10;
    seconds_units = seconds % 10;
    rtc_alarm_cfg.alrmr |= hours_tens << 20;
    rtc_alarm_cfg.alrmr |= hours_units << 16;
    rtc_alarm_cfg.alrmr |= minutes_tens << 12;
    rtc_alarm_cfg.alrmr |= minutes_units << 8;
    rtc_alarm_cfg.alrmr |= seconds_tens << 4;
    rtc_alarm_cfg.alrmr |= seconds_units << 0;

    rtcSetAlarm(&RTCD1, (rtcalarm_t)0, &rtc_alarm_cfg);
}

/* Go into standby */
void lowpower_do_standby(void)
{
    // Enable deep sleep and stand-by mode, disable STOP
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    PWR->CR |= PWR_CR_PDDS;
    PWR->CR &= ~PWR_CR_LPDS;

    // Clear WUF wakeup flag
    PWR->CR |= PWR_CR_CWUF;

    // Clear RTC interrupts
    RTC->ISR = 0;

    __SEV();
    while(1)
        __WFE();
}

/* Are we booting from standby, as opposed to from cold? */
bool lowpower_woken_from_standby(void)
{
    if(PWR->CSR & PWR_CSR_SBF)
    {
        PWR->CR |= PWR_CR_CSBF;
        return true;
    }
    else
        return false;
}

/* Store sequence character in backup register*/
void lowpower_set_sequence(char seq)
{
    RTC->BKP0R = (uint32_t)seq;
}

/* Retrieve sequence character from backup register */
char lowpower_get_sequence(void)
{
    return (char)RTC->BKP0R;
}

#endif
