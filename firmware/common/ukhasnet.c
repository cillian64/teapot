#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ukhasnet.h"
#include "util.h"
#include "rfm69.h"

/* Setup the RFM69 for UKHASnet operation */
void ukhasnet_radio_init(void)
{
    rfm69_init();

    /* Fstep = Fxosc / 2^19 = 32e6 / 2^19
     * FRF = freq / (32e6 / 2^19)
           = 869.5 / 32 * 2^19 = 14245888 */
    rfm69_setfreq(14245888);

    rfm69_setpower(2); /* Transmit power, in dBm */

    /* Shift: 24kHz.  fdev = 24e3/fstep = 24e3/61/2 = 197
     * 2000-baud: bitrate = fxosc / 2000 = 32e6/2000 = 16000 */
    rfm69_physetup(197, 16000);

    /* 3-byte preamble of 0xAA, 0xAA, 0xAA
     * 2-byte sync of 0x2D, 0xAA */
    uint8_t syncvalue[2] = {0x2d, 0xaa};
    rfm69_packetsetup(true, 3, 2, syncvalue, false, false, true);
}


/* Generate a ukhasnet packet in buf, with maximum length buf_len.
 * Return the length of the packet generated */
uint8_t makepacket(uint8_t *buf, uint8_t buf_len,
                   char *seq, char* label, /* Seq count, node label */
                   uint8_t hops,
                   bool has_battery, uint16_t voltage,  /* voltage V*100 */
                   bool has_temp, int16_t temp,         /* temperature, C*10 */
                   bool has_hum, uint8_t hum,           /* rel humidity, % */
                   bool has_press, uint32_t press,      /* Pressure, pascal */
                   bool has_light, uint8_t light,       /* Light sensor */
                   char *comment)
{
    uint8_t length = 0;

    // Check the packet will fit.
    length += 2; // TTL, sequence, []
    if(has_battery)             length += 5;
    if(has_temp)                length += 6;
    if(has_hum)                 length += 3;
    if(has_press)               length += 7;
    if(has_light)               length += 4;
    if(strlen(comment) != 0)    length += 1;
    length += strlen(comment);
    length += strlen(label);
    if(length >= buf_len)
        panic("makepacket: packet will be >64 bytes");

    length = 0;

    /* Number of hops */
    if(hops > 9)
        panic("makepacket: Number of hops must be 0-9 inclusive");
    buf[length++] = '0' + hops;

    /* Sequence counter */
    if((*seq < 'a') || (*seq > 'z'))
        panic("makepacket: Sequence counter must be a-z inclusive");
    buf[length++] = *seq;
    if(*seq < 'z')
        *seq += 1;
    else
        *seq = 'b';

    if(has_battery) /* battery */
    {
        if(voltage > 999)
            panic("makepacket: Voltage must be <999 (9.99V)");
        buf[length++] = 'V';
        buf[length++] = '0' + voltage/100;
        buf[length++] = '.';
        buf[length++] = '0' + (voltage % 100)/10;
        buf[length++] = '0' + voltage % 10;
    }

    if(has_temp) /* temperature */
    {
        if((temp < -999) || (temp > 999))
            panic("makepacket: Temperature must be -99.9C to 99.9C");

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
            panic("makepacket: Humidity must be 0-99% inclusive");
        buf[length++] = 'H';
        buf[length++] = '0' + hum / 10;
        buf[length++] = '0' + hum % 10;
    }

    if(has_press)
    {
        if(press > 999999)
            panic("makepacket: Pressure must be 0-999999 pascal");
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

    /* Now, comment */
    size_t comment_len = strlen(comment);
    if(comment_len != 0)
    {
        buf[length++] = ':';
        memcpy(buf + length, comment, comment_len);
        length += comment_len;
    }

    /* Finally, node label */
    buf[length++] = '[';
    memcpy(buf + length, label, strlen(label));
    length += strlen(label);
    buf[length++] = ']';

    if(length > buf_len)
        panic("makepacket: packet was too long");

    return length;
}

/* Add a hop to the hops field of a packet.
 * packet_len is the old length of the packet, including the terminating ']'
 * We return the new length of the packet, including the terminating ']'.
 * If the extended packet won't fit in the buffer length, buf_len, we panic.
 * node_name should be a null-terminated string. */
uint8_t ukhasnet_addhop(uint8_t *buf, uint8_t packet_len, char *node_name,
                        uint8_t buf_len)
{
    uint8_t new_packet_len = packet_len + strlen(node_name);
    if(new_packet_len > buf_len)
        panic("addhop: new packet will be too long");

    /* The end of the packet will look like [node1,node2]
     * We overwrite the final ] with a ',' then append node_name and a ]
     */
    if(buf[packet_len - 1] != ']')
        panic("Last character of packet is not ]");
    buf[packet_len - 1] = ',';

    /* Append the node_name.  Use memcpy not strcpy because the buf is
     * not necessarily very string-like */
    memcpy(buf + packet_len, node_name, strlen(node_name));

    /* Now append the final closing ']' */
    buf[new_packet_len - 1] = ']';

    return new_packet_len;
}
