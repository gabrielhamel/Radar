#ifndef RADAR_TIMER_SYSTEM_H
#define RADAR_TIMER_SYSTEM_H

#include "engine/ecs/system.h"

#define TIMER_SYSTEM_TYPE 3

system_t *timer_system_create(void);

#endif // RADAR_TIMER_SYSTEM_H