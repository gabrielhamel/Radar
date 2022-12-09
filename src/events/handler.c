#include <stdlib.h>

#include "events.h"

events_handler_t *eh_create(void)
{
    events_handler_t *handler = malloc(sizeof(events_handler_t));

    LIST_INIT(&handler->key_pressed_binds);
    LIST_INIT(&handler->key_released_binds);
    return handler;
}

void eh_handle_event(events_handler_t *handler, sfEvent *event, void *scene)
{
    struct eh_bind_s *it = NULL;

    if (event->type == sfEvtKeyPressed) {
        LIST_FOREACH(it, &handler->key_pressed_binds, entry) {
            if (event->key.code == it->key) {
                it->callback(scene);
            }
        }
    } else if (event->type == sfEvtKeyReleased) {
        LIST_FOREACH(it, &handler->key_released_binds, entry) {
            if (event->key.code == it->key) {
                it->callback(scene);
            }
        }
    }
}