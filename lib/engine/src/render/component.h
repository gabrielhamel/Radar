#ifndef _ENGINE_RENDER_COMPONENT_H
#define _ENGINE_RENDER_COMPONENT_H

#include <limits.h>
#include <stdbool.h>
#include <SFML/Graphics.h>

#include "../ecs/component.h"
#include "../queue.h"

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(*x))

#define RENDER_COMPONENT_TYPE INT_MAX

typedef void (*draw_callback_t)(sfRenderWindow *window, void *, void *);
typedef void (*destroy_callback_t)(void *);
typedef void (*set_position_callback_t)(void *, sfVector2f);
typedef sfVector2f (*get_position_callback_t)(void *);
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

typedef struct render_object_s {
    TAILQ_ENTRY(render_object_s) entry;
    void *csfml_object;
    csfml_type_t type;
    render_objet_id_t id;
} render_object_t;

typedef struct {
    TAILQ_HEAD(, render_object_s) objects;
} render_resources_t;

typedef struct {
    csfml_type_t type;
    draw_callback_t draw_callback;
    destroy_callback_t destroy_callback;
    set_position_callback_t set_position_callback;
    get_position_callback_t get_position_callback;
} render_object_functions_t;

component_t *render_component_create(void);
bool render_component_append_object(component_t *component, csfml_type_t type, void *csfml_object, render_objet_id_t object_id);
void *render_component_get_raw_csfml_object(component_t *component, render_objet_id_t id);

void render_component_draw(component_t *component, sfRenderWindow *window);
void render_component_set_position(component_t *component, sfVector2f position);

// Custom destroy
void sprite_destroy(sfSprite *sprite);
void convex_shape_destroy(sfConvexShape *shape);

#endif // _ENGINE_RENDER_COMPONENT_H
