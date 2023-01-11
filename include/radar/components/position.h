#ifndef RADAR_POSITION_COMPONENT_H
#define RADAR_POSITION_COMPONENT_H

#include <SFML/System/Vector2.h>

#include <engine/ecs/component.h>

#define POSITION_COMPONENT_TYPE 1

typedef struct {
    sfVector2f position;
} position_component_t;

component_t *position_component_create(sfVector2f position);

#endif // RADAR_POSITION_COMPONENT_H