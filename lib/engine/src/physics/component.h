#ifndef _ENGINE_PHYSICS_COMPONENT_H
#define _ENGINE_PHYSICS_COMPONENT_H

#include <limits.h>
#include <SFML/System.h>

#include "../ecs/component.h"

#define PHYSICS_COMPONENT_TYPE INT_MAX - 1

typedef struct {
    sfVector2f position;
    sfVector2f speed;
} physics_component_t;

component_t *physics_component_create(physics_component_t params);

#endif // _ENGINE_PHYSICS_COMPONENT_H
