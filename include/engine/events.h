#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Graphics.h>

#include "engine/queue.h"
#include "engine/events.h"

typedef struct eh_bind_s {
    LIST_ENTRY(eh_bind_s) entry;
    sfKeyCode key;
    void *context;
    void (*callback)(void *);
} eh_bind_t;

typedef struct events_handler_s {
    LIST_ENTRY(events_handler_s) entry;
    LIST_HEAD(, eh_bind_s) key_pressed_binds;
    LIST_HEAD(, eh_bind_s) key_released_binds;
} events_handler_t;

events_handler_t *eh_create(void);
void eh_handle_event(events_handler_t *handler, sfEvent *event);
void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);

#endif // EVENTS_H