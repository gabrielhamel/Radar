#include <stdlib.h>

#include "engine/ui/events.h"

state_event_t *ui_state_event_create(void (*enter)(void *context), void (*leave)(void *context), void *context)
{
    state_event_t *event = malloc(sizeof(state_event_t));

    event->context = context;
    event->enter = enter;
    event->leave = leave;
    return event;
}