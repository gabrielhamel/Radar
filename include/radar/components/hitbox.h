#ifndef RADAR_HITBOX_COMPONENT_H
#define RADAR_HITBOX_COMPONENT_H

#include <engine/ecs/component.h>

#define HITBOX_COMPONENT_TYPE 5

typedef enum {
    RECT,
    CIRCLE,
    CUSTOM
} hitbox_type_t;

typedef struct {
    hitbox_type_t type;
    sfVector2f *points;
    size_t point_count;
    float radius;
} hitbox_component_t;

component_t *hitbox_circle_component_create(float radius);
component_t *hitbox_rect_component_create(void);
component_t *hitbox_custom_component_create(sfVector2f *points, size_t count);

#endif // RADAR_HITBOX_COMPONENT_H