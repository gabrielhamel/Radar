#ifndef ENGINE_RENDER_COMPONENT_H
#define ENGINE_RENDER_COMPONENT_H

#include <limits.h>
#include <stdbool.h>
#include <SFML/System/Vector2.h>
#include <engine/ecs/component.h>

#define RENDER_COMPONENT_TYPE INT_MAX

typedef int render_objet_id_t;

typedef enum {
    SPRITE,
    TEXT,
    SHAPE,
    CIRCLE_SHAPE,
    CONVEX_SHAPE,
    RECTANGLE_SHAPE,
    VERTEX_ARRAY,
    VERTEX_BUFFER
} csfml_type_t;

component_t *render_component_create(void);
bool render_component_append_object(component_t *component, csfml_type_t type, void *csfml_object, render_objet_id_t object_id);
void *render_component_get_raw_csfml_object(component_t *component, render_objet_id_t id);
void render_component_set_position(component_t *component, sfVector2f position);

#endif // ENGINE_RENDER_COMPONENT_H
