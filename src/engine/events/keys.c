#include <stdlib.h>

#include "engine/events.h"

void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context)
{
    struct eh_bind_s *bind = malloc(sizeof(eh_bind_t));

    bind->key = key;
    bind->callback = callback;
    bind->context = context;
    LIST_INSERT_HEAD(&handler->key_pressed_binds, bind, entry);
}

void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context)
{
    struct eh_bind_s *bind = malloc(sizeof(eh_bind_t));

    bind->key = key;
    bind->callback = callback;
    bind->context = context;
    LIST_INSERT_HEAD(&handler->key_released_binds, bind, entry);
}