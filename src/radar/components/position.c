#include <stdlib.h>

#include <engine/ecs/component.h>

#include <radar/components/position.h>

static void position_component_destroy(component_t *component)
{
    void *data = component_get_raw_data(component);
    free(data);
}

component_t *position_component_create(sfVector2f position)
{
    position_component_t *data = malloc(sizeof(position_component_t));

    data->position = position;
    return component_create(POSITION_COMPONENT_TYPE, data, position_component_destroy);
}
