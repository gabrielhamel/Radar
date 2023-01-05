#include <stdlib.h>

#include "engine/events.h"

void eh_bind_mouse_pressed(events_handler_t *handler, sfMouseButton button,
                           void (*callback)(sfVector2i, void *), void *context)
{
    struct eh_mouse_bind_s *bind = malloc(sizeof(eh_key_bind_t));

    bind->button = button;
    bind->callback = callback;
    bind->context = context;
    TAILQ_INSERT_TAIL(&handler->mouse_pressed_binds, bind, entry);
}

void eh_bind_mouse_released(events_handler_t *handler, sfMouseButton button,
                           void (*callback)(sfVector2i, void *), void *context)
{
    struct eh_mouse_bind_s *bind = malloc(sizeof(eh_key_bind_t));

    bind->button = button;
    bind->callback = callback;
    bind->context = context;
    TAILQ_INSERT_TAIL(&handler->mouse_released_binds, bind, entry);
}