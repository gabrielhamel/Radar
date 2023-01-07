#include <stdlib.h>

#include "engine/ecs/component.h"

component_t *component_create(component_type_t type, void *data, void (*destroy_handle)(struct component_s *))
{
    component_t *component = malloc(sizeof(component_t));

    component->type = type;
    component->data = data;
    component->destroy_handle = destroy_handle;
    return component;
}

void component_destroy(component_t *component)
{
    if (component->destroy_handle) {
        component->destroy_handle(component);
    }
    free(component);
}
