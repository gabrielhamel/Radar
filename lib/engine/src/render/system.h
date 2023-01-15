#ifndef ENGINE_RENDER_SYSTEM_H
#define ENGINE_RENDER_SYSTEM_H

#include <limits.h>

#include "../ecs/system.h"

#define RENDER_SYSTEM_TYPE INT_MAX

system_t *render_system_create(void);

#endif // ENGINE_RENDER_SYSTEM_H
