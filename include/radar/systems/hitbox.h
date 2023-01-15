#ifndef RADAR_HITBOX_SYSTEM_H
#define RADAR_HITBOX_SYSTEM_H

#include <engine/ecs/system.h>

#include <radar/components/hitbox.h>

#define HITBOX_SYSTEM_TYPE 4

typedef struct {
    bool render_enabled;
    entity_set_t *crashed_aircrafts;
} hitbox_system_t;

system_t *hitbox_system_create(void);
bool custom_intersect_custom(entity_t *a, entity_t *b);
bool rect_intersect_rect(entity_t *a, entity_t *b);
bool point_intersect_circle(entity_t *circle, sfVector2f point);
bool rect_intersect_circle(entity_t *rect, entity_t *circle);

#endif // RADAR_HITBOX_SYSTEM_H