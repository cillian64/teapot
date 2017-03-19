#include "ch.h"
#include "hal.h"

#include "util.h"


/* If something goes wrong, turn on the ERR (error) LED and call chSysHalt */
void panic(const char *reason)
{
    palSetLine(LINE_LED_YELLOW);
    chSysHalt(reason);
}

