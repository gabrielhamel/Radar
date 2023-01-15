#include <stdlib.h>

#include "component.h"

static render_object_functions_t functions[] = {
    {SPRITE,(draw_callback_t)sfRenderWindow_drawSprite, (destroy_callback_t)sprite_destroy, (set_position_callback_t)sfSprite_setPosition, (get_position_callback_t)sfSprite_getPosition},
    {TEXT,(draw_callback_t)sfRenderWindow_drawText, (destroy_callback_t)sfText_destroy, (set_position_callback_t)sfText_setPosition, (get_position_callback_t)sfText_getPosition},
    {SHAPE,(draw_callback_t)sfRenderWindow_drawShape, (destroy_callback_t)sfShape_destroy, (set_position_callback_t)sfShape_setPosition, (get_position_callback_t)sfShape_getPosition},
    {CIRCLE_SHAPE,(draw_callback_t)sfRenderWindow_drawCircleShape, (destroy_callback_t)sfCircleShape_destroy, (set_position_callback_t)sfCircleShape_setPosition, (get_position_callback_t)sfCircleShape_getPosition},
    {CONVEX_SHAPE,(draw_callback_t)sfRenderWindow_drawConvexShape, (destroy_callback_t)convex_shape_destroy, (set_position_callback_t)sfConvexShape_setPosition, (get_position_callback_t)sfConvexShape_getPosition},
    {RECTANGLE_SHAPE,(draw_callback_t)sfRenderWindow_drawRectangleShape, (destroy_callback_t)sfRectangleShape_destroy, (set_position_callback_t)sfRectangleShape_setPosition, (get_position_callback_t)sfRectangleShape_getPosition},
    {VERTEX_ARRAY,(draw_callback_t)sfRenderWindow_drawVertexArray, (destroy_callback_t)sfVertexArray_destroy, NULL, NULL},
    {VERTEX_BUFFER,(draw_callback_t)sfRenderWindow_drawVertexBuffer, (destroy_callback_t)sfVertexBuffer_destroy, NULL, NULL},
};

static render_object_functions_t *render_object_functions_find(csfml_type_t type)
{
    for (size_t i = 0; i < ARRAY_LENGTH(functions); i++) {
        if (functions[i].type == type) {
            return &functions[i];
        }
    }
    return NULL;
}

static void render_component_destroy(component_t *component)
{
    render_resources_t *resources = component_get_data(component, render_resources_t);

    render_object_t *it = NULL;
    render_object_t *tmp = NULL;
    TAILQ_FOREACH_SAFE(it, &resources->objects, entry, tmp) {
        TAILQ_REMOVE(&resources->objects, it, entry);
        render_object_functions_find(it->type)->destroy_callback(it->csfml_object);
        free(it);
    }
    free(resources);
}

void render_component_draw(component_t *component, sfRenderWindow *window)
{
    render_resources_t *resources = component_get_data(component, render_resources_t);

    render_object_t *it = NULL;
    TAILQ_FOREACH(it, &resources->objects, entry) {
        render_object_functions_find(it->type)->draw_callback(window, it->csfml_object, NULL);
    }
}

void *render_component_get_raw_csfml_object(component_t *component, render_objet_id_t id)
{
    render_resources_t *resources = component_get_data(component, render_resources_t);

    render_object_t *it = NULL;
    TAILQ_FOREACH(it, &resources->objects, entry) {
        if (it->id == id) {
            return it->csfml_object;
        }
    }
    return NULL;
}

void render_component_set_position(component_t *component, sfVector2f position)
{
    render_resources_t *resources = component_get_data(component, render_resources_t);

    render_object_t *it = NULL;
    TAILQ_FOREACH(it, &resources->objects, entry) {
        render_object_functions_t *function = render_object_functions_find(it->type);
        if (function->set_position_callback) {
            function->set_position_callback(it->csfml_object, position);
        }
    }
}

component_t *render_component_create(void)
{
    render_resources_t *data = malloc(sizeof(render_resources_t));
    TAILQ_INIT(&data->objects);
    return component_create(RENDER_COMPONENT_TYPE, data, render_component_destroy);
}

bool render_component_append_object(component_t *component, csfml_type_t type, void *csfml_object, render_objet_id_t object_id)
{
    render_resources_t *resources = component_get_data(component, render_resources_t);

    render_object_t *it = NULL;
    TAILQ_FOREACH(it, &resources->objects, entry) {
        if (it->id == object_id) {
            return false;
        }
    }

    render_object_t *obj = malloc(sizeof(render_object_t));
    obj->id = object_id;
    obj->type = type;
    obj->csfml_object = csfml_object;

    TAILQ_INSERT_TAIL(&resources->objects, obj, entry);
    return true;
}