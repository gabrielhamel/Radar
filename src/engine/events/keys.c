#include <stdlib.h>

#include "engine/events.h"

void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context)
{
    struct eh_key_bind_s *bind = malloc(sizeof(eh_key_bind_t));

    bind->key = key;
    bind->callback = callback;
    bind->context = context;
    TAILQ_INSERT_HEAD(&handler->key_pressed_binds, bind, entry);
}

void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context)
{
    struct eh_key_bind_s *bind = malloc(sizeof(eh_key_bind_t));

    bind->key = key;
    bind->callback = callback;
    bind->context = context;
    TAILQ_INSERT_HEAD(&handler->key_released_binds, bind, entry);
}

void eh_exec_key_pressed(events_handler_t *handler, sfEvent *event)
{
    struct eh_key_bind_s *it = NULL;
    TAILQ_FOREACH(it, &handler->key_pressed_binds, entry) {
        if (event->key.code == it->key) {
            it->callback(it->context);
        }
    }
}

void eh_exec_key_released(events_handler_t *handler, sfEvent *event)
{
    struct eh_key_bind_s *it = NULL;
    TAILQ_FOREACH(it, &handler->key_released_binds, entry) {
        if (event->key.code == it->key) {
            it->callback(it->context);
        }
    }
}

void eh_unbind_key_pressed(events_handler_t *handler)
{
    eh_key_bind_t *it = NULL;
    eh_key_bind_t *tmp = NULL;
    TAILQ_FOREACH_SAFE(it, &handler->key_pressed_binds, entry, tmp) {
        TAILQ_REMOVE(&handler->key_pressed_binds, it, entry);
        free(it);
    }
}

void eh_unbind_key_released(events_handler_t *handler)
{
    eh_key_bind_t *it = NULL;
    eh_key_bind_t *tmp = NULL;
    TAILQ_FOREACH_SAFE(it, &handler->key_released_binds, entry, tmp) {
        TAILQ_REMOVE(&handler->key_released_binds, it, entry);
        free(it);
    }
}