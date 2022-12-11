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
    scene->ui_element_root = ui_element_create((sfIntRect){0, 0, window_size.x, window_size.y});
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
