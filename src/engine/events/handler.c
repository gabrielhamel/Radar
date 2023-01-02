#include <stdlib.h>

#include "engine/events.h"

events_handler_t *eh_create(void)
{
    events_handler_t *handler = malloc(sizeof(events_handler_t));

    LIST_INIT(&handler->key_pressed_binds);
    LIST_INIT(&handler->key_released_binds);
    LIST_INIT(&handler->mouse_pressed_binds);
    LIST_INIT(&handler->mouse_released_binds);
    return handler;
}

void eh_handle_event(events_handler_t *handler, sfEvent *event)
{
    struct eh_key_bind_s *it_key = NULL;
    struct eh_mouse_bind_s *it_mouse = NULL;

    switch (event->type) {
        case sfEvtKeyPressed:
            LIST_FOREACH(it_key, &handler->key_pressed_binds, entry) {
                if (event->key.code == it_key->key) {
                    it_key->callback(it_key->context);
                }
            }
            break;
        case sfEvtKeyReleased:
            LIST_FOREACH(it_key, &handler->key_released_binds, entry) {
                if (event->key.code == it_key->key) {
                    it_key->callback(it_key->context);
                }
            }
            break;
        case sfEvtMouseButtonPressed:
            LIST_FOREACH(it_mouse, &handler->mouse_pressed_binds, entry) {
                if (event->mouseButton.button == it_mouse->button) {
                    it_mouse->callback((sfVector2i){
                        event->mouseButton.x,
                        event->mouseButton.y
                    }, it_mouse->context);
                }
            }
            break;
        case sfEvtMouseButtonReleased:
            LIST_FOREACH(it_mouse, &handler->mouse_released_binds, entry) {
                if (event->mouseButton.button == it_mouse->button) {
                    it_mouse->callback((sfVector2i){
                            event->mouseButton.x,
                            event->mouseButton.y
                    }, it_mouse->context);
                }
            }
            break;
    }
}