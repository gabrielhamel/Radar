#include <stdlib.h>
#include <SFML/Graphics.h>

#include "radar/components/hitbox.h"

static void hitbox_component_destroy(component_t *component)
{
    hitbox_component_t *data = COMPONENT_DATA(component, hitbox_component_t);

    if (data->type == RECT) {
        sfRectangleShape_destroy(data->csfml_object);
    } else if (data->type == CIRCLE) {
        sfCircleShape_destroy(data->csfml_object);
    } else if (data->type == CUSTOM) {
        sfTexture *texture = (sfTexture *)sfConvexShape_getTexture(data->csfml_object);
        sfConvexShape_destroy(data->csfml_object);
        sfTexture_destroy(texture);
    }
    if (data->points) {
        free(data->points);
    }
    free(data);
}

component_t *hitbox_circle_component_create(sfVector2f initial_pos, float radius)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = CIRCLE;
    data->csfml_object = sfCircleShape_create();
    sfCircleShape_setPosition(data->csfml_object, initial_pos);
    sfCircleShape_setOutlineColor(data->csfml_object, sfBlue);
    sfCircleShape_setFillColor(data->csfml_object, sfTransparent);
    sfCircleShape_setOutlineThickness(data->csfml_object, 2);
    sfCircleShape_setRadius(data->csfml_object, radius);
    sfCircleShape_setPointCount(data->csfml_object, 40);
    sfCircleShape_setOrigin(data->csfml_object, (sfVector2f){
        radius,
        radius
    });
    data->points = NULL;
    data->point_count = 0;
    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}

component_t *hitbox_rect_component_create(sfVector2f initial_pos)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = RECT;
    data->csfml_object = sfRectangleShape_create();
    sfRectangleShape_setPosition(data->csfml_object, initial_pos);
    sfRectangleShape_setOutlineColor(data->csfml_object, sfGreen);
    sfRectangleShape_setFillColor(data->csfml_object, sfTransparent);
    sfRectangleShape_setOutlineThickness(data->csfml_object, 2);
    sfRectangleShape_setSize(data->csfml_object, (sfVector2f){
        20,
        20
    });
    sfRectangleShape_setOrigin(data->csfml_object, (sfVector2f){
        10,
        10
    });
    data->points = NULL;
    data->point_count = 0;
    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}

component_t *hitbox_custom_component_create(sfVector2f initial_pos, sfVector2f *points, size_t count)
{
    hitbox_component_t *data = malloc(sizeof(hitbox_component_t));

    data->type = CUSTOM;
    data->csfml_object = sfConvexShape_create();

    sfConvexShape_setPointCount(data->csfml_object, count);
    for (size_t idx = 0; idx < count; idx++) {
        sfConvexShape_setPoint(data->csfml_object, idx, points[idx]);
    }

    sfTexture *texture = sfTexture_createFromFile("assets/storm.png", NULL);
    sfTexture_setRepeated(texture, sfTrue);
    sfConvexShape_setTexture(data->csfml_object, texture, sfTrue);
    sfConvexShape_setTextureRect(data->csfml_object, (sfIntRect){0, 0, 4800, 3200});

    sfConvexShape_setPosition(data->csfml_object, initial_pos);
    sfConvexShape_setOutlineColor(data->csfml_object, sfRed);
    sfConvexShape_setOutlineThickness(data->csfml_object, 2);

    data->points = points;
    data->point_count = count;

    return component_create(HITBOX_COMPONENT_TYPE, data, hitbox_component_destroy);
}