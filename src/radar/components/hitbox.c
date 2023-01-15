#include <engine/render/component.h>

#include <stdlib.h>
#include <radar/components/hitbox.h>

static void hitbox_component_destroy(component_t *component)
{
    hitbox_component_t *data = component_get_data(component, hitbox_component_t);

    if (data->points) {
        free(data->points);
    }
    free(data);
}

component_t *hitbox_circle_component_create(float radius)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = CIRCLE;
    data->points = NULL;
    data->point_count = 0;
    data->radius = radius;
    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}

component_t *hitbox_rect_component_create(void)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = RECT;
    data->points = NULL;
    data->point_count = 0;
    data->radius = 0;
    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}

component_t *hitbox_custom_component_create(sfVector2f *points, size_t count)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = CUSTOM;
    data->points = points;
    data->point_count = count;
    data->radius = 0;
    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}