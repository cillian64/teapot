#include "ch.h"
#include "hal.h"

#include "util.h"


/* If something goes wrong, turn on the ERR (error) LED and hang here.  In
 * debugging this makes it clear that something went wrong.  In production the
 * watchdog will catch us and reset (eventually).
 */
void panic(void)
{
    palSetLine(LINE_LED_YELLOW);
    while(true);
}

