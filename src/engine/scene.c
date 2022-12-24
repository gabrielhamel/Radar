#include <stdlib.h>

#include "engine/events.h"
#include "engine/engine.h"

void scene_handle_event(scene_t *scene, sfEvent *event)
{
    struct events_handler_s *it = NULL;

    LIST_FOREACH(it, &scene->events_handlers, entry) {
        eh_handle_event(it, event);
    }
}

void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler)
{
    LIST_INSERT_HEAD(&scene->events_handlers, handler, entry);
}

scene_t *scene_create(void)
{
    scene_t *scene = malloc(sizeof(scene_t));
    sfVector2u window_size = sfRenderWindow_getSize(engine_get()->window);

    LIST_INIT(&scene->events_handlers);
    LIST_INIT(&scene->entities);
    scene->ui_element_root = ui_element_create((sfIntRect){0, 0, window_size.x, window_size.y});
    scene->update_context = NULL;
    scene->update_delegate = NULL;
    return scene;
}

void scene_render_ui(scene_t *scene, sfRenderWindow *window)
{
    struct ui_element_s *it = NULL;

    LIST_FOREACH(it, &scene->ui_element_root->children, entry) {
        ui_element_render(it, scene->ui_element_root->render_target);
    }
    sfRenderTexture_display(scene->ui_element_root->render_target);
    sfRenderWindow_drawSprite(window, scene->ui_element_root->render_sprite, NULL);
}

ui_element_t *scene_get_ui_root(scene_t *scene)
{
    return scene->ui_element_root;
}

void scene_update(scene_t *scene, sfTime *elapsed_time)
{
    struct entity_s *it = NULL;

    if (scene->update_delegate) {
        scene->update_delegate(scene->update_context, elapsed_time);
    }
    LIST_FOREACH(it, &scene->entities, entry) {
        entity_update(it, elapsed_time);
    }
}

void scene_render(scene_t *scene, sfRenderWindow *window)
{
    struct entity_s *it = NULL;

    LIST_FOREACH(it, &scene->entities, entry) {
        entity_render(it, window);
    }
}

void scene_append_entity(scene_t *scene, entity_t *entity)
{
    LIST_INSERT_HEAD(&scene->entities, entity, entry);
}

void scene_set_update_delegate(scene_t *scene, void (*callback)(void *, sfTime *), void *context)
{
    scene->update_delegate = callback;
    scene->update_context = context;
}