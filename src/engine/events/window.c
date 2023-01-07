#include <stdlib.h>

#include "engine/events.h"

void eh_bind_window_closed(events_handler_t *handler, void (*callback)(void *), void *context)
{
    eh_window_event_bind_t *bind = malloc(sizeof(eh_window_event_bind_t));

    bind->callback = callback;
    bind->context = context;
    handler->window_closed = bind;
}

void eh_exec_window_closed(events_handler_t *handler, sfEvent *event)
{
    if (handler->window_closed == NULL) {
        return;
    }
    handler->window_closed->callback(handler->window_closed->context);
}
