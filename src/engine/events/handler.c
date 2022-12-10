#include <stdlib.h>

#include "engine/events.h"

events_handler_t *eh_create(void)
{
    events_handler_t *handler = malloc(sizeof(events_handler_t));

    LIST_INIT(&handler->key_pressed_binds);
    LIST_INIT(&handler->key_released_binds);
    return handler;
}

void eh_handle_event(events_handler_t *handler, sfEvent *event)
{
    struct eh_bind_s *it = NULL;

    switch (event->type) {
        case sfEvtKeyPressed:
            LIST_FOREACH(it, &handler->key_pressed_binds, entry) {
                if (event->key.code == it->key) {
                    it->callback(it->context);
                }
            }
            break;
        case sfEvtKeyReleased:
            LIST_FOREACH(it, &handler->key_released_binds, entry) {
                if (event->key.code == it->key) {
                    it->callback(it->context);
                }
            }
            break;
    }
}