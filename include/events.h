#ifndef EVENTS_H
#define EVENTS_H

#include <SFML/Graphics.h>

#include "scene.h"

typedef struct eh_bind_s {
    LIST_ENTRY(eh_bind_s) entry;
    sfKeyCode key;
    void (*callback)(void *);
} eh_bind_t;

events_handler_t *eh_create(void);
void eh_handle_event(events_handler_t *handler, sfEvent *event, void *scene);
void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *));
void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *));

#endif // EVENTS_H