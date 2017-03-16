#include "b64.h"

static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789+/";

void b64encode(const uint8_t* data, size_t n, char* out)
{
    size_t i;
    uint32_t x;

    /* Encode all whole groups of 3 input bytes */
    for(i=0; i<n/3; i++) {
        x = data[i*3+0]<<16 | data[i*3+1]<<8 | data[i*3+2];
        out[i*4+0] = b64chars[x>>18 & 0x3F];
        out[i*4+1] = b64chars[x>>12 & 0x3F];
        out[i*4+2] = b64chars[x>> 6 & 0x3F];
        out[i*4+3] = b64chars[x>> 0 & 0x3F];
    }

    /* Encode final 1 or 2 bytes and finish with a null terminator */
    if(n%3 == 1) {
        x = data[n-1]<<16;
        out[i*4+0] = b64chars[x>>18 & 0x3F];
        out[i*4+1] = b64chars[x>>12 & 0x3F];
        out[i*4+2] = out[i*4+3] = '=';
        out[i*4+4] = 0;
    } else if(n%3 == 2) {
        x = data[n-2]<<16 | data[n-1]<<8;
        out[i*4+0] = b64chars[x>>18 & 0x3F];
        out[i*4+1] = b64chars[x>>12 & 0x3F];
        out[i*4+2] = b64chars[x>> 6 & 0x3F];
        out[i*4+3] = '=';
        out[i*4+4] = 0;
    } else {
        out[i*4+0] = 0;
    }
}

void b64decode(const char* data, size_t n, uint8_t* out)
{
    size_t i, j;

    /* Decode every group of 4 characters */
    for(i=0; i<n/4; i++) {
        uint32_t x = 0;
        for(j=0; j<4; j++) {
            char y = data[i*4+j];

            if(y >= 'A' && y <= 'Z') {
                y = y - 'A';
            } else if(y >= 'a' && y <= 'z') {
                y = y - 'a' + 26;
            } else if(y >= '0' && y <= '9') {
                y = y - '0' + 26 + 26;
            } else if(y == '+' || y == '-') {
                y = 26 + 26 + 10;
            } else if(y == '/' || y == '_') {
                y = 26 + 26 + 10 + 1;
            }

            x |= y << ((3-j)*6);
        }

        out[i*3+0] = (x >> 16) & 0xFF;
        out[i*3+1] = (x >>  8) & 0xFF;
        out[i*3+2] = (x >>  0) & 0xFF;
    }
}
