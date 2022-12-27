#include <stdlib.h>

#include "engine/ecs/component.h"

component_t *component_create(component_type_t type, void *data)
{
    component_t *component = malloc(sizeof(component_t));

    component->type = type;
    component->data = data;
    return component;
}

void component_destroy(component_t *component)
{
    // TODO
    // Delete handler
    free(component);
}