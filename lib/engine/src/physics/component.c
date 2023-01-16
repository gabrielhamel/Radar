#include <stdlib.h>

#include "component.h"

static void physics_component_destroy(component_t *component)
{
    physics_component_t *physics = component_get_data(component, physics_component_t);
    free(physics);
}

component_t *physics_component_create(physics_component_t params)
{
    physics_component_t *physics = malloc(sizeof(physics_component_t));
    physics->position = params.position;
    physics->speed = params.speed;
    return component_create(PHYSICS_COMPONENT_TYPE, physics, physics_component_destroy);
}