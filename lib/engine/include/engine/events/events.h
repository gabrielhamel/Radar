#ifndef ENGINE_EVENTS_EVENTS_H
#define ENGINE_EVENTS_EVENTS_H

#include <SFML/Window/Event.h>

typedef struct events_handler_t events_handler_t;

events_handler_t *eh_create(void);
void eh_destroy(events_handler_t *handler);
void eh_bind_key_pressed(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_key_released(events_handler_t *handler, sfKeyCode key, void (*callback)(void *), void *context);
void eh_bind_mouse_pressed(events_handler_t *handler, sfMouseButton button,
                           void (*callback)(sfVector2i, void *), void *context);
void eh_bind_mouse_released(events_handler_t *handler, sfMouseButton button,
                            void (*callback)(sfVector2i, void *), void *context);
void eh_bind_window_closed(events_handler_t *handler, void (*callback)(void *), void *context);
void eh_unbind_window_closed(events_handler_t *handler);
void eh_unbind_mouse_pressed(events_handler_t *handler);
void eh_unbind_mouse_released(events_handler_t *handler);
void eh_unbind_key_pressed(events_handler_t *handler);
void eh_unbind_key_released(events_handler_t *handler);

#endif // ENGINE_EVENTS_EVENTS_H