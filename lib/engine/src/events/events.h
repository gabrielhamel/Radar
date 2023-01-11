#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Graphics.h>

#include "../queue.h"

typedef struct eh_key_bind_s {
    TAILQ_ENTRY(eh_key_bind_s) entry;
    sfKeyCode key;
    void *context;
    void (*callback)(void *);
} eh_key_bind_t;

typedef struct {
    void *context;
    void (*callback)(void *);
} eh_window_event_bind_t;

typedef struct eh_mouse_bind_s {
    TAILQ_ENTRY(eh_mouse_bind_s) entry;
    sfMouseButton button;
    void *context;
    void (*callback)(sfVector2i, void *);
} eh_mouse_bind_t;

typedef struct events_handler_s {
    TAILQ_ENTRY(events_handler_s) entry;
    eh_window_event_bind_t *window_closed;
    TAILQ_HEAD(, eh_key_bind_s) key_pressed_binds;
    TAILQ_HEAD(, eh_key_bind_s) key_released_binds;
    TAILQ_HEAD(, eh_mouse_bind_s) mouse_pressed_binds;
    TAILQ_HEAD(, eh_mouse_bind_s) mouse_released_binds;
} events_handler_t;

events_handler_t *eh_create(void);
void eh_destroy(events_handler_t *handler);
void eh_handle_event(events_handler_t *handler, sfEvent *event);
void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_mouse_pressed(events_handler_t *handler, sfMouseButton button,
                           void (*callback)(sfVector2i, void *), void *context);
void eh_bind_mouse_released(events_handler_t *handler, sfMouseButton button,
                            void (*callback)(sfVector2i, void *), void *context);
void eh_bind_window_closed(events_handler_t *handler, void (*callback)(void *), void *context);
void eh_exec_mouse_pressed(events_handler_t *handler, sfEvent *event);
void eh_exec_mouse_released(events_handler_t *handler, sfEvent *event);
void eh_exec_key_pressed(events_handler_t *handler, sfEvent *event);
void eh_exec_key_released(events_handler_t *handler, sfEvent *event);
void eh_exec_window_closed(events_handler_t *handler, sfEvent *event);
void eh_unbind_window_closed(events_handler_t *handler);
void eh_unbind_mouse_pressed(events_handler_t *handler);
void eh_unbind_mouse_released(events_handler_t *handler);
void eh_unbind_key_pressed(events_handler_t *handler);
void eh_unbind_key_released(events_handler_t *handler);

#endif // EVENTS_H