#ifndef RADAR_SPEED_COMPONENT_H
#define RADAR_SPEED_COMPONENT_H

#include <SFML/System/Vector2.h>

#include "engine/ecs/component.h"

#define SPEED_COMPONENT_TYPE 2

typedef struct {
    sfVector2f speed;
} speed_component_t;

component_t *speed_component_create(sfVector2f speed);
void speed_component_destroy(component_t *component);

#endif // RADAR_SPEED_COMPONENT_H