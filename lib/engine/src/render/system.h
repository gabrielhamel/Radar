#ifndef _ENGINE_RENDER_SYSTEM_H
#define _ENGINE_RENDER_SYSTEM_H

#include <limits.h>

#include "../ecs/system.h"

#define RENDER_SYSTEM_TYPE INT_MAX

system_t *render_system_create(void);

#endif // _ENGINE_RENDER_SYSTEM_H
