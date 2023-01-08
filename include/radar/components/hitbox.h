#ifndef RADAR_HITBOX_COMPONENT_H
#define RADAR_HITBOX_COMPONENT_H

#include <SFML/System.h>
#include "engine/ecs/component.h"

#define HITBOX_COMPONENT_TYPE 5

typedef enum {
    RECT,
    CIRCLE,
    CUSTOM
} hitbox_type_t;

typedef struct {
    hitbox_type_t type;
    void *csfml_object;
} hitbox_component_t;

component_t *hitbox_circle_component_create(sfVector2f initial_pos, float radius);
component_t *hitbox_rect_component_create(sfVector2f initial_pos);
component_t *hitbox_custom_component_create(sfVector2f initial_pos, sfVector2f *points, size_t count);

#endif // RADAR_HITBOX_COMPONENT_H