#include <stdbool.h>
#include <stdint.h>

#include "ukhasnet.h"
#include "util.h"

const uint8_t number_hops = 3;

/* Generate a ukhasnet packet in buf, with maximum length buf_len.
 * Return the length of the packet generated */
uint8_t makepacket(char *buf, uint8_t buf_len,
                   char seq, char* label, /* Seq count, node label */
                   bool has_battery, uint16_t voltage,  /* voltage V*100 */
                   bool has_temp, int16_t temp,         /* temperature, C*10 */
                   bool has_hum, uint8_t hum,           /* rel humidity, % */
                   bool has_press, uint32_t press,      /* Pressure, pascal */
                   bool has_light, uint8_t light)       /* Light sensor */
{
    uint8_t length = 0;

    /* TODO: Check premptively if buf_len is long enough */

    /* Number of hops */
    if(number_hops > 9)
        panic(); /* Must be single digit number */
    buf[length++] = '0' + number_hops;

    /* Sequence counter */
    if((seq < 'a') || (seq > 'z'))
        panic();
    buf[length++] = seq;

    if(has_battery) /* battery */
    {
        if(voltage > 999)
            panic();
        buf[length++] = 'V';
        buf[length++] = '0' + voltage/100;
        buf[length++] = '.';
        buf[length++] = '0' + (voltage % 100)/10;
        buf[length++] = '0' + voltage % 10;
    }

    if(has_temp) /* temperature */
    {
        if((temp < -999) || (temp > 999))
            panic();

        uint16_t utemp;
        buf[length++] = 'T';
        if(temp < 0)
        {
            buf[length++] = '-';
            utemp = (uint16_t)(0 - temp);
        }
        else
            utemp = (uint16_t)temp;
        buf[length++] = '0' + utemp / 100;
        buf[length++] = '0' + (utemp % 100) / 10;
        buf[length++] = '.';
        buf[length++] = '0' + utemp % 10;
    }

    if(has_hum)
    {
        if(hum > 99)
            panic();
        buf[length++] = 'H';
        buf[length++] = '0' + hum / 10;
        buf[length++] = '0' + hum % 10;
    }

    if(has_press)
    {
        if(press > 999999)
            panic();
        buf[length++] = 'P';
        buf[length++] = '0' + press / 100000;
        buf[length++] = '0' + (press % 100000) / 10000;
        buf[length++] = '0' + (press % 10000) / 1000;
        buf[length++] = '0' + (press % 1000) / 100;
        buf[length++] = '0' + (press % 100) / 10;
        buf[length++] = '0' + press % 10;
    }

    if(has_light)
    {
        buf[length++] = 'S';
        buf[length++] = '0' + light / 100;
        buf[length++] = '0' + (light % 100) / 10;
        buf[length++] = '0' + light % 10;
    }

    if(!has_battery && !has_temp && !has_hum && !has_press && !has_light)
    {
        /* Current legacy parser does not handle packets with no numeric values
         * So add a blank custom field */
        buf[length++] = 'X';
        buf[length++] = '0';
    }

    /* Finally, node label */
    buf[length++] = '[';
    for(uint8_t i=0; label[i] != '\0'; i++)
        buf[length++] = label[i];
    buf[length++] = ']';

    if(length > buf_len)
        panic();

    return length;
}

