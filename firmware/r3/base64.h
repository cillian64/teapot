#ifndef B64_H
#define B64_H

#include <stdint.h>
#include <stddef.h>

/* Base64 encode n bytes of data, writing 4*ceil(n/3) characters to out. */
void b64encode(const uint8_t* data, size_t n, char* out);

/* Base64 decode n characters, writing (n/4)*3 bytes to out. */
void b64decode(const char* data, size_t n, uint8_t* out);

#endif
