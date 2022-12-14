#include <stdlib.h>

#include "engine/ui/events.h"

hover_event_t *ui_hover_event_create(void (*enter)(void *context), void (*leave)(void *context), void *context)
{
    hover_event_t *event = malloc(sizeof(hover_event_t));

    event->context = context;
    event->enter = enter;
    event->leave = leave;
    return event;
}