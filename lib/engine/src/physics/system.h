#ifndef _ENGINE_PHYSICS_SYSTEM_H
#define _ENGINE_PHYSICS_SYSTEM_H

#include <limits.h>

#include "../ecs/system.h"

#define PHYSICS_SYSTEM_TYPE INT_MAX - 1

system_t *physics_system_create(void);

#endif // _ENGINE_PHYSICS_SYSTEM_H
