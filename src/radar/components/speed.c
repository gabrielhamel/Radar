#include <stdlib.h>

#include "radar/components/speed.h"
#include "engine/ecs/component.h"

static void speed_component_destroy(component_t *component)
{
    free(component->data);
}

component_t *speed_component_create(sfVector2f speed)
{
    speed_component_t *data = malloc(sizeof(speed_component_t));

    data->speed = speed;
    return component_create(SPEED_COMPONENT_TYPE, data, speed_component_destroy);
}
