#include <stdlib.h>

#include "engine/events.h"

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

    LIST_INIT(&scene->events_handlers);
    return scene;
}