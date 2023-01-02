#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Graphics.h>

#include "engine/queue.h"
#include "engine/events.h"

typedef struct eh_key_bind_s {
    LIST_ENTRY(eh_key_bind_s) entry;
    sfKeyCode key;
    void *context;
    void (*callback)(void *);
} eh_key_bind_t;

typedef struct eh_mouse_bind_s {
    LIST_ENTRY(eh_mouse_bind_s) entry;
    sfMouseButton button;
    void *context;
    void (*callback)(sfVector2i, void *);
} eh_mouse_bind_t;

typedef struct events_handler_s {
    LIST_ENTRY(events_handler_s) entry;
    LIST_HEAD(, eh_key_bind_s) key_pressed_binds;
    LIST_HEAD(, eh_key_bind_s) key_released_binds;
    LIST_HEAD(, eh_mouse_bind_s) mouse_pressed_binds;
    LIST_HEAD(, eh_mouse_bind_s) mouse_released_binds;
} events_handler_t;

events_handler_t *eh_create(void);
void eh_handle_event(events_handler_t *handler, sfEvent *event);
void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_mouse_pressed(events_handler_t *handler, sfMouseButton button,
                           void (*callback)(sfVector2i, void *), void *context);
void eh_bind_mouse_released(events_handler_t *handler, sfMouseButton button,
                            void (*callback)(sfVector2i, void *), void *context);

#endif // EVENTS_H