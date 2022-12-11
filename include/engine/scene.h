#ifndef SCENE_H
#define SCENE_H

#include "queue.h"
#include "ui.h"

typedef struct events_handler_s {
    LIST_ENTRY(events_handler_s) entry;
    LIST_HEAD(, eh_bind_s) key_pressed_binds;
    LIST_HEAD(, eh_bind_s) key_released_binds;
} events_handler_t;

typedef struct {
    LIST_HEAD(, events_handler_s) events_handlers;
    ui_element_t *ui_element_root;
} scene_t;

scene_t *scene_create(void);
void scene_handle_event(scene_t *scene, sfEvent *event);
void scene_subscribe_event_handler(scene_t *scene, events_handler_t *handler);
void scene_render_ui(scene_t *scene, sfRenderWindow *window);

#endif // SCENE_H