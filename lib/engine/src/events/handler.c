#include <stdlib.h>

#include "events.h"

events_handler_t *eh_create(void)
{
    events_handler_t *handler = malloc(sizeof(events_handler_t));

    TAILQ_INIT(&handler->key_pressed_binds);
    TAILQ_INIT(&handler->key_released_binds);
    TAILQ_INIT(&handler->mouse_pressed_binds);
    TAILQ_INIT(&handler->mouse_released_binds);
    handler->window_closed = NULL;
    return handler;
}

void eh_destroy(events_handler_t *handler)
{
    eh_unbind_key_pressed(handler);
    eh_unbind_key_released(handler);
    eh_unbind_mouse_pressed(handler);
    eh_unbind_mouse_released(handler);
    eh_unbind_window_closed(handler);
    free(handler);
}

void eh_handle_event(events_handler_t *handler, sfEvent *event)
{
    switch (event->type) {
        case sfEvtKeyPressed:
            eh_exec_key_pressed(handler, event);
            break;
        case sfEvtKeyReleased:
            eh_exec_key_released(handler, event);
            break;
        case sfEvtMouseButtonPressed:
            eh_exec_mouse_pressed(handler, event);
            break;
        case sfEvtMouseButtonReleased:
            eh_exec_mouse_released(handler, event);
            break;
        case sfEvtClosed:
            eh_exec_window_closed(handler, event);
        default:
            return;
    }
}