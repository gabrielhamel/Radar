#include <stdlib.h>

#include "engine/ecs/component.h"
#include "radar/components/ttl.h"

component_t *ttl_component_create(float remaining_time)
{
    float *ttl = malloc(sizeof(float));
    *ttl = remaining_time;
    return component_create(TTL_COMPONENT_TYPE, ttl);
}

void ttl_component_destroy(component_t *component)
{
    free(component->data);
    component_destroy(component);
}