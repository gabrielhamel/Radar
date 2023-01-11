#ifndef RADAR_HITBOX_SYSTEM_H
#define RADAR_HITBOX_SYSTEM_H

#include "engine/ecs/system.h"
#include <engine/tools/lists.h>

#define HITBOX_SYSTEM_TYPE 4

typedef struct {
    bool render_enabled;
    entity_set_t *crashed_aircrafts;
} hitbox_system_t;

system_t *hitbox_system_create(void);

#endif // RADAR_HITBOX_SYSTEM_H