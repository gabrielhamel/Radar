#ifndef RADAR_HITBOX_COMPONENT_H
#define RADAR_HITBOX_COMPONENT_H

#include <SFML/System.h>
#include "engine/ecs/component.h"

#define HITBOX_COMPONENT_TYPE 5

typedef enum {
    RECT,
    CIRCLE
} hitbox_type_t;

typedef struct {
    hitbox_type_t type;
    void *csfml_object;
} hitbox_component_t;

component_t *hitbox_circle_component_create(sfVector2f initial_pos, float radius);
component_t *hitbox_rect_component_create(sfVector2f initial_pos);
void hitbox_component_destroy(component_t *component);

#endif // RADAR_HITBOX_COMPONENT_H