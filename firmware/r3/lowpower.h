#ifndef LOWPOWER_H
#define LOWPOWER_H

#include <stdint.h>
#include <stdbool.h>

#include "ch.h"

/* Set up RTC wakeup timer in seconds */
void lowpower_set_wakeup_timer(uint32_t interval);

/* Go into standby */
void lowpower_do_standby(void);

/* Are we booting from standby, as opposed to from cold? */
bool lowpower_woken_from_standby(void);

/* Store sequence character in backup register*/
void lowpower_set_sequence(char seq);

/* Retrieve sequence character from backup register */
char lowpower_get_sequence(void);

#endif
