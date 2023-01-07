#ifndef RADAR_HITBOX_SYSTEM_H
#define RADAR_HITBOX_SYSTEM_H

#include "engine/ecs/system.h"

#define HITBOX_SYSTEM_TYPE 4

typedef struct {
    bool render_enabled;
    TAILQ_HEAD(, entity_link_s) plane_to_delete;
} hitbox_system_t;

system_t *hitbox_system_create(void);

#endif // RADAR_HITBOX_SYSTEM_H