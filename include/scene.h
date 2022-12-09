#ifndef SCENE_H
#define SCENE_H

#include "queue.h"

typedef struct {
    LIST_HEAD(, eh_bind_s) key_pressed_binds;
    LIST_HEAD(, eh_bind_s) key_released_binds;
} events_handler_t;

typedef struct {
    events_handler_t *events_handler;
} scene_t;

scene_t *create_main_scene(void);

#endif // SCENE_H